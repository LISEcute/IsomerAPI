#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"
#include "ui_d_DatabaseRecords.h"
#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlError>
#include <QSqlRecord>
#include <cmath>

void IsomerAPI::editDatabaseRecords()
{
    QDialog dialog(this);
    Ui::DatabaseRecordsDialog recordUi;
    recordUi.setupUi(&dialog);
    auto status = recordUi.statusLabel;
    auto table = recordUi.recordsTable;
    auto fieldsWidget = recordUi.fieldsWidget;
    auto save = recordUi.saveButton;
    auto add = recordUi.addButton;
    auto insert = recordUi.insertButton;
    auto remove = recordUi.deleteButton;
    auto close = recordUi.closeButton;
    QSqlQueryModel records(&dialog);
    table->setModel(&records);
    // Bind Designer fields to the database columns; layout lives in the .ui file.
    const QMap<QString, QLineEdit *> fields = {
        {"INDEX_IT", recordUi.record_INDEX_IT},
        {"A_IT", recordUi.record_A_IT},
        {"Z_IT", recordUi.record_Z_IT},
        {"E_GAMMA", recordUi.record_E_GAMMA},
        {"D_EG", recordUi.record_D_EG},
        {"IT_RATIO", recordUi.record_IT_RATIO},
        {"D_IT_RATIO", recordUi.record_D_IT_RATIO},
        {"T12", recordUi.record_T12},
        {"D_T12", recordUi.record_D_T12},
        {"LEVEL", recordUi.record_LEVEL},
        {"D_LEVEL", recordUi.record_D_LEVEL},
        {"JPI", recordUi.record_JPI},
        {"I_GAMMA", recordUi.record_I_GAMMA},
        {"D_IG", recordUi.record_D_IG},
        {"M_GAMMA", recordUi.record_M_GAMMA},
        {"M_RATIO", recordUi.record_M_RATIO},
        {"D_MRATIO", recordUi.record_D_MRATIO},
        {"CONV", recordUi.record_CONV},
        {"D_CONV", recordUi.record_D_CONV},
        {"SOURCE", recordUi.record_SOURCE},
        {"NAME", recordUi.record_NAME},
        {"ROW", recordUi.record_ROW},
        {"LEVEL_ID", recordUi.record_LEVEL_ID},
        {"GAMMA_ID", recordUi.record_GAMMA_ID},
        {"FINAL_LEVEL_ID", recordUi.record_FINAL_LEVEL_ID}
    };
    qint64 rowId = -1;
    qint64 savedRowId = -1;
    bool dirty = false;
    bool loading = false;
    bool changed = false;
    QMap<QString, QVariant> original;
    auto error = [&](const QString &message) {
        const QString detail = message.contains("locked", Qt::CaseInsensitive)
            ? message + tr("\n\nAnother database reader or writer is still active. Close older IsomerAPI windows and retry. Your entries are still in this form.")
            : message;
        QMessageBox::warning(&dialog, tr("Database record"), detail);
    };
    auto discard = [&]() {
        return !dirty || QMessageBox::question(&dialog, tr("Unsaved record"),
            tr("Discard the unsaved changes?"), QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No) == QMessageBox::Yes;
    };
    auto refresh = [&]() {
        loading = true;
        QString sql = "SELECT rowid AS record_id, * FROM Isomers";
        if (!modelFull->filter().isEmpty())
            sql += " WHERE (" + modelFull->filter() + ") OR rowid=" + QString::number(savedRowId);
        sql += " ORDER BY (rowid=" + QString::number(savedRowId) + ") DESC, rowid";
        records.setQuery(sql, dbIsomLevel);
        // Exhaust the SQLite cursor: an unfinished SELECT keeps a read lock
        // alive while the editor is idle, including in another app instance.
        while (records.canFetchMore()) records.fetchMore();
        table->hideColumn(0);
        loading = false;
        if (records.lastError().isValid()) error(records.lastError().text());
    };
    for (auto edit : fields) connect(edit, &QLineEdit::textEdited, &dialog, [&]() { dirty = true; });
    connect(table, &QTableView::clicked, &dialog, [&](const QModelIndex &index) {
        if (loading || !discard()) return;
        const auto record = records.record(index.row());
        rowId = record.value(0).toLongLong();
        original.clear();
        for (auto it = fields.begin(); it != fields.end(); ++it) {
            original.insert(it.key(), record.value(it.key()));
            it.value()->setText(record.value(it.key()).toString());
        }
        dirty = false;
        save->setEnabled(true);
        add->setEnabled(true);
        insert->hide();
        fieldsWidget->setEnabled(true);
        remove->setEnabled(true);
        status->setText(tr("Editing an existing record. Save updates it; Delete removes it. Add Record starts a separate new entry."));
    });
    connect(add, &QPushButton::clicked, &dialog, [&]() {
        if (!discard()) return;
        rowId = -1;
        original.clear();
        for (auto edit : fields) edit->clear();
        fields["SOURCE"]->setText("manual");
        fields["LEVEL"]->setText("0");
        fields["T12"]->setText("0");
        QSqlQuery ids(dbIsomLevel);
        if (!ids.exec("SELECT COALESCE(MAX(LEVEL_ID),0)+1 FROM Isomers") || !ids.next()) {
            error(ids.lastError().text()); return;
        }
        fields["LEVEL_ID"]->setText(ids.value(0).toString());
        dirty = false;
        save->setEnabled(false);
        add->setEnabled(false);
        insert->show();
        fieldsWidget->setEnabled(true);
        remove->setEnabled(false);
        table->clearSelection();
        status->setText(tr("New record â€” enter values, then click Add to Database. Keep the suggested LEVEL_ID for a new level; leave FINAL_LEVEL_ID blank if unknown."));
        fields["A_IT"]->setFocus();
    });
    auto writeRecord = [&]() {
        QMap<QString, QVariant> values;
        const QStringList integers = {"A_IT", "Z_IT", "LEVEL_ID", "FINAL_LEVEL_ID"};
        const QStringList reals = {"E_GAMMA", "LEVEL", "T12"};
        for (auto it = fields.begin(); it != fields.end(); ++it) {
            const QString name = it.key(), text = it.value()->text().trimmed();
            if (it.value()->isReadOnly()) continue;
            QVariant value = text.isEmpty() ? QVariant() : QVariant(text);
            bool ok = true;
            if (!text.isEmpty() && integers.contains(name)) {
                value = text.toLongLong(&ok);
                ok = ok && value.toLongLong() >= 0 && value.toLongLong() <= 2147483647;
            } else if (!text.isEmpty() && reals.contains(name)) {
                value = text.toDouble(&ok);
                ok = ok && std::isfinite(value.toDouble()) && value.toDouble() >= 0;
            }
            if (!ok) { error(tr("Enter a valid non-negative number for %1.").arg(name)); return; }
            // Preserve SQL NULLs and original precision for untouched fields.
            if (rowId >= 0 && it.value()->text() == original.value(name).toString())
                value = original.value(name);
            values.insert(name, value);
        }
        if (values["A_IT"].toInt() < 1 || values["Z_IT"].isNull() ||
            values["Z_IT"].toInt() > values["A_IT"].toInt() ||
            values["LEVEL_ID"].toInt() < 1 || values["LEVEL"].isNull() ||
            values["T12"].isNull() || values["NAME"].toString().trimmed().isEmpty()) {
            error(tr("Enter A >= 1, 0 <= Z <= A, a positive LEVEL_ID, level energy, half-life, and your NAME.")); return;
        }
        if (!dbIsomLevel.transaction()) { error(dbIsomLevel.lastError().text()); return; }
        auto fail = [&](const QString &message) { dbIsomLevel.rollback(); error(message); };
        QSqlQuery check(dbIsomLevel);
        if (!values["FINAL_LEVEL_ID"].isNull()) {
            check.prepare("SELECT 1 FROM Isomers WHERE LEVEL_ID=? AND A_IT=? AND Z_IT=? LIMIT 1");
            check.addBindValue(values["FINAL_LEVEL_ID"]);
            check.addBindValue(values["A_IT"]); check.addBindValue(values["Z_IT"]);
            if (!check.exec()) { fail(check.lastError().text()); return; }
            if (!check.next()) { fail(tr("FINAL_LEVEL_ID must identify an existing level of this isotope.")); return; }
            check.finish();
        }
        if (rowId >= 0 && (values["LEVEL_ID"] != original["LEVEL_ID"] ||
            values["A_IT"] != original["A_IT"] || values["Z_IT"] != original["Z_IT"])) {
            fail(tr("The isotope and LEVEL_ID of an existing record cannot be changed. Add a new record instead.")); return;
        }
        if (rowId < 0) {
            check.prepare("SELECT A_IT, Z_IT, LEVEL, D_LEVEL, JPI, T12, D_T12, IT_RATIO, D_IT_RATIO FROM Isomers WHERE LEVEL_ID=? LIMIT 1");
            check.addBindValue(values["LEVEL_ID"]);
            if (!check.exec()) { fail(check.lastError().text()); return; }
            if (check.next()) {
                const QStringList shared = {"A_IT", "Z_IT", "LEVEL", "D_LEVEL", "JPI", "T12", "D_T12", "IT_RATIO", "D_IT_RATIO"};
                for (int i = 0; i < shared.size(); ++i) {
                    const QString name = shared[i];
                    const bool same = (integers.contains(name) || reals.contains(name))
                        ? check.value(i).toDouble() == values[name].toDouble()
                        : check.value(i).toString() == values[name].toString();
                    if (!same) {
                        fail(tr("For an existing LEVEL_ID, %1 must match that level. Use a new LEVEL_ID for a new level.").arg(name)); return;
                    }
                }
            }
            check.finish();
            if (!check.exec("SELECT COALESCE(MAX(GAMMA_ID),0)+1 FROM Isomers") || !check.next()) {
                fail(check.lastError().text()); return;
            }
            values["GAMMA_ID"] = check.value(0); check.finish();
        }
        values["INDEX_IT"] = (values["A_IT"].toLongLong()*100 + values["Z_IT"].toLongLong())*10000
            + qint64(values["E_GAMMA"].toDouble());
        QStringList columns, placeholders, assignments;
        for (auto it = values.begin(); it != values.end(); ++it) {
            columns << "[" + it.key() + "]"; placeholders << "?";
            assignments << "[" + it.key() + "]=?";
        }
        QSqlQuery write(dbIsomLevel);
        write.prepare(rowId < 0 ? QString("INSERT INTO Isomers (%1) VALUES (%2)").arg(columns.join(','), placeholders.join(','))
                               : QString("UPDATE Isomers SET %1 WHERE rowid=?").arg(assignments.join(',')));
        for (auto value : values) write.addBindValue(value);
        if (rowId >= 0) write.addBindValue(rowId);
        if (!write.exec()) { fail(write.lastError().text()); return; }
        if (write.numRowsAffected() != 1) { fail(tr("The record no longer exists. Reopen the editor.")); return; }
        // A level appears once per transition in this database. Keep its shared
        // attributes consistent so the level proxy cannot show stale values.
        QSqlQuery level(dbIsomLevel);
        level.prepare("UPDATE Isomers SET LEVEL=?, D_LEVEL=?, JPI=?, T12=?, D_T12=?, IT_RATIO=?, D_IT_RATIO=? WHERE LEVEL_ID=?");
        for (const QString &name : QStringList{"LEVEL", "D_LEVEL", "JPI", "T12", "D_T12", "IT_RATIO", "D_IT_RATIO", "LEVEL_ID"})
            level.addBindValue(values[name]);
        if (!level.exec()) { fail(level.lastError().text()); return; }
        if (!dbIsomLevel.commit()) { fail(dbIsomLevel.lastError().text()); return; }
        savedRowId = rowId < 0 ? write.lastInsertId().toLongLong() : rowId;
        dirty = false; changed = true;
        refresh();
        if (records.rowCount() > 0) {
            table->selectRow(0);
            table->scrollToTop();
            QMetaObject::invokeMethod(table, "clicked", Qt::DirectConnection,
                                      Q_ARG(QModelIndex, records.index(0, 0)));
        }
        status->setText(tr("Record saved and selected at the top of the list, even if it falls outside the main window's filters."));
    };
    connect(save, &QPushButton::clicked, &dialog, [&]() {
        if (rowId >= 0) writeRecord();
    });
    connect(insert, &QPushButton::clicked, &dialog, [&]() {
        if (rowId < 0) writeRecord();
    });
    connect(remove, &QPushButton::clicked, &dialog, [&]() {
        if (rowId < 0 || QMessageBox::question(&dialog, tr("Remove record"),
            tr("Permanently remove this record?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes) return;
        if (!dbIsomLevel.transaction()) { error(dbIsomLevel.lastError().text()); return; }
        QSqlQuery query(dbIsomLevel);
        query.prepare("DELETE FROM Isomers WHERE rowid=? AND ("
                      "EXISTS(SELECT 1 FROM Isomers other WHERE other.LEVEL_ID=Isomers.LEVEL_ID AND other.rowid<>Isomers.rowid) "
                      "OR NOT EXISTS(SELECT 1 FROM Isomers incoming WHERE incoming.FINAL_LEVEL_ID=Isomers.LEVEL_ID AND incoming.rowid<>Isomers.rowid))");
        query.addBindValue(rowId);
        if (!query.exec() || query.numRowsAffected() != 1) {
            const QString message = query.lastError().isValid() ? query.lastError().text()
                : tr("Cannot remove the last record for a level referenced by another transition, or the record no longer exists.");
            dbIsomLevel.rollback(); error(message); return;
        }
        if (!dbIsomLevel.commit()) { dbIsomLevel.rollback(); error(dbIsomLevel.lastError().text()); return; }
        dirty = false; changed = true; rowId = -1;
        for (auto edit : fields) edit->clear();
        save->setEnabled(false); remove->setEnabled(false); refresh();
        fieldsWidget->setEnabled(false);
        add->setEnabled(true);
        insert->hide();
        status->setText(tr("Record deleted. Select another record or click Add Record."));
    });
    // Handle Close, Escape, and the window close button through the same check.
    connect(close, &QPushButton::clicked, &dialog, &QDialog::reject);
    save->setEnabled(false); remove->setEnabled(false);
    add->setEnabled(dbIsomLevel.isOpen());
    insert->hide();
    fieldsWidget->setEnabled(false);
    status->setText(tr("Select a record to edit or delete, or click Add Record to enter a new one."));
    refresh();
    do { dialog.exec(); } while (!discard());
    if (changed) {
        const QString selectedSource = ui->cb_sourceFilter->currentText();
        entrySources.clear();
        QSqlQuery sources("SELECT DISTINCT SOURCE FROM Isomers ORDER BY SOURCE", dbIsomLevel);
        while (sources.next()) entrySources << sources.value(0).toString();
        ui->cb_sourceFilter->clear();
        ui->cb_sourceFilter->addItems(QStringList() << "All Sources" << "Semicolon;List;Sources");
        ui->cb_sourceFilter->addItems(entrySources);
        ui->cb_sourceFilter->setCurrentText(selectedSource);
        applyFilters();
    }
}
