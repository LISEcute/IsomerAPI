#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "d_DrawingOptions.h"
#include "w_schemeWindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QTableView>

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
void IsomerAPI::onRowSelected(QTableView *view)
{
    // QList<QModelIndex> indexList = ui->tableView_Dev->selectionModel()->selectedRows();
    // int columnCount = ui->tableView_Dev->model()->columnCount();
    QList<QModelIndex> indexList = view->selectionModel()->selectedRows();
    int columnCount = view->model()->columnCount();

    qDebug() << "\n[onRowSelected: start information]";
    // qDebug() << "[onRowSelected: Selected Rows]Selected Rows:" << indexList;
    QVector<int> IsomerIDList;
    double tempdLevelE;

    for (QModelIndex &index : indexList)  {
        QStringList rowData;
        // QVector<int> IsomerIDList;

        for (int col = 0; col < columnCount; ++col)
        {
            // Move horizontally across the same row to read each column
            QModelIndex cellIndex = index.siblingAtColumn(col);
            rowData.append(cellIndex.data().toString());
        }

        int IsomerID = rowData.value(modelFull->fieldIndex("LEVEL_ID")).toInt();
        IsomerIDList.append(IsomerID);

        qDebug() << "Index:" << index.row();
        qDebug() << "Row Data:" << rowData;
        qDebug() << "IsomerID:" << rowData.value(modelFull->fieldIndex("LEVEL_ID"));


        qDebug() << "Associated Gammas:" << "boo";


    }
    qDebug() << "[onRowSelected: number of rows]" << indexList.length();
    qDebug() << "[onRowSelected: check levels in selection]";
    for (auto &iso : filteredIsotopes.values()) {
        for (auto &lvl : iso.levels) {
            if (IsomerIDList.contains(lvl.lvlID)) {
                bool lvlString;
                tempdLevelE = lvl.dlvlEnergy.toDouble(&lvlString);
                if (!lvlString) {
                    tempdLevelE = 0.0;
                }
                qDebug() << "Selected Levels:" << lvl.lvlEnergy << "dLvl" << tempdLevelE;

                for (auto &tr : lvl.transitions) {
                    Q_UNUSED(tr);
                    bool gamString;
                    tempdLevelE = lvl.dlvlEnergy.toDouble(&gamString);
                    if (!gamString) {
                        tempdLevelE = 0.0;
                    }
                    // qDebug() << "   Associated gammas:" << tr.gamEnergy << "dGam"<< tempdGammaE << tr.trID;
                    // qDebug() << "     proposed final:" << lvl.lvlEnergy - tempdGammaE;


                }
            }
        }
    }
    qDebug() << "[onRowSelected: isotope, sel levels]" << IsomerIDList;


    qDebug();

}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww


QList<SchemeKey> IsomerAPI::selectedLevelKeys(QTableView *view) const
{
    QMap<SchemeKey, bool> uniqueKeys;

    if (!view || !view->selectionModel() || !view->model()) {
        return uniqueKeys.keys();
    }

    const int zColumn = modelFull->fieldIndex("Z_IT");
    const int aColumn = modelFull->fieldIndex("A_IT");
    const int levelIdColumn = modelFull->fieldIndex("LEVEL_ID");

    for (const QModelIndex &row : view->selectionModel()->selectedRows()) {
        SchemeKey key{
            row.siblingAtColumn(zColumn).data().toInt(),
            row.siblingAtColumn(aColumn).data().toInt(),
            SchemeType::DecayFromLevel,
            row.siblingAtColumn(levelIdColumn).data().toInt()
        };

        uniqueKeys.insert(key, true);
    }

    return uniqueKeys.keys();
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::openDrawing()
{
    currentPage = ui->stackedWidget->currentIndex();

    QString drawSelection = "";
    SchemeMap schemeMap;

    auto showLevelScheme = [this](const SchemeMap &schemes) {
        auto *levelScheme = new LevelScheme(schemes, this);
        levelScheme->setWindowFlag(Qt::Window, true);
        levelScheme->setAttribute(Qt::WA_DeleteOnClose);
        levelScheme->show();
    };

    drawingChoiceDlg drawDlg(this);
    if (drawDlg.exec() != QDialog::Accepted) {
        return;
    }

    drawSelection = drawDlg.getDrawChoice();
    qDebug() << "[openDrawing: DIALOG ACCEPT] code" << drawSelection;

    if (drawSelection == "filt") {
        for (const Isotope &iso : filteredIsotopes) {
            SchemeKey key{iso.Z, iso.A, SchemeType::FilteredIsotope, -1};
            schemeMap.insert(key, iso);
        }

        showLevelScheme(schemeMap);

    } else if (drawSelection == "lvl") {
        QTableView *selectedLevelView = getTableView(currentPage, SchemeType::DecayFromLevel);
        if (selectedLevelView == nullptr) {
            QMessageBox::warning(
                this,
                tr("Cannot plot decay from levels"),
                tr("Development view table selection not valid. "
                   "Please select a level from one of the Isomer tables in the other views."));
            return;
        }

        if (!selectedLevelView->selectionModel()->hasSelection()) {
            QMessageBox::warning(
                this,
                tr("Cannot plot decay from levels"),
                tr("No level selected in Isomer table on current page. "
                   "Please select a level from the Isomers table on the active page to plot decays from."));
            return;
        }

        for (const SchemeKey &selSchemeKey : selectedLevelKeys(selectedLevelView)) {
            Isotope selIso = filteredIsotopes[qMakePair(selSchemeKey.Z,selSchemeKey.A)];
            Level selLvl;

            QMap<int, Level> lvlMap;

            for (auto &lvl : selIso.levels) {
                lvlMap[lvl.lvlID] = lvl;
                // if (lvl.lvlID == selSchemeKey.anchorId) selLvl = lvl;
            }
            lvlMap.insert(selIso.groundState.lvlID, selIso.groundState);

            selLvl = lvlMap[selSchemeKey.anchorId];

            QVector<Level> decLvls = vecDecayAlgo(&selLvl, lvlMap, INFINITY, false);
            qDebug() << "[openDrawing: levels, check decays in scheme]" << decLvls.size();

            Isotope decayIso = {selSchemeKey.A, selSchemeKey.Z,
                                decLvls,
                                selIso.groundState};

            schemeMap.insert(selSchemeKey, decayIso);
        }

        showLevelScheme(schemeMap);
        qDebug() << "[openDrawing: select lvl]";

    } else if (drawSelection == "gam") {
        qDebug() << "[openDrawing: select gam]";
    }
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
