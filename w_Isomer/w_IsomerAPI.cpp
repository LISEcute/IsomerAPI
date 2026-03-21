#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "w_levelScheme.h"
#include "L_isomerAPIversion.h"

#include <QSqlError>
#include <QSqlQueryModel>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>


//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
IsomerAPI::IsomerAPI(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::IsomerAPI),
    model(nullptr)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // === Database initialization ======================================================
    QString appDir;
    const QStringList args = QCoreApplication::arguments();
    int dirArgIdx = args.indexOf("--appdir");
    if (dirArgIdx != -1 && dirArgIdx + 1 < args.size())
        appDir = args.at(dirArgIdx + 1);
    else
        appDir = QCoreApplication::applicationDirPath();

    dbPathLevels = appDir + "/lisecfg/Isomer_Levels.sqlite";
    dbPathGammas = appDir + "/lisecfg/Isomer_Gammas.sqlite";

    qDebug() << "[IsomerAPI LEVELS DB:]" << dbPathLevels << QFile::exists(dbPathLevels);
    qDebug() << "[IsomerAPI GAMMAS DB:]" << dbPathGammas << QFile::exists(dbPathGammas);

    dbLevels = QSqlDatabase::addDatabase("QSQLITE", "LevelsDB");
    dbLevels.setDatabaseName(dbPathLevels);
    if (!dbLevels.open())
        qCritical() << "Failed to open Levels DB:" << dbLevels.lastError().text();

    dbGammas = QSqlDatabase::addDatabase("QSQLITE", "GammasDB");
    dbGammas.setDatabaseName(dbPathGammas);
    if (!dbGammas.open())
        qCritical() << "Failed to open Gammas DB:" << dbGammas.lastError().text();

    QSqlQuery attachQuery(dbGammas);
    attachQuery.exec(QString("ATTACH DATABASE '%1' AS LevelsDB").arg(dbPathLevels));

    model = new QSqlQueryModel(this);
    query = QSqlQuery(dbGammas);
    refreshTableView();

    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);


    // Columns: A, Z, Eγ, dEγ, IT, dIT, T½, dT½, E(level), dE(level), Jπ,
    //          Iγ, dIγ, Mγ, M-Ratio, dM-Ratio, Conv, dConv, Source, Name, γ-ID, Row
    headerNames = {"A", "Z",
                   "E\u1D67 (keV)", "dE\u1D67 (keV)",
                   "I\u1D1B", "dI\u1D1B",
                   "T\u00BD (\u03BCs)", "dT\u2081\u2082 (\u03BCs)",
                   "E(level) (keV)", "dE(level) (keV)", "J\u03C0",
                   "I\u1D67", "dI\u1D67",
                   "M\u1D67", "M-Ratio", "dM-Ratio",
                   "Conv", "dConv",
                   "Source", "Name", "\u03B3-ID", "Row"};
    int headerIndex = 0;
    for (const QString &header : headerNames) {
        model->setHeaderData(headerIndex, Qt::Horizontal, header);
        headerIndex++;
    }

    // Contained utility/attribute declaration
    filterBounds = ui->gb_tableFilters->findChildren<QLineEdit*>();

    // Source combo box config
    ui->cb_sourceFilter->addItem("All Sources");
    ui->cb_sourceFilter->addItem("Semicolon;List;Sources");

    QSqlQuery srcQuery(dbGammas);
    if (srcQuery.exec("SELECT DISTINCT SOURCE FROM Gammas")) {
        while (srcQuery.next()) {
            QString src = srcQuery.value(0).toString();
            entrySources.append(src);
        }
    }
    ui->cb_sourceFilter->addItems(entrySources);

    connect(ui->pb_clearFilters,  &QPushButton::clicked, this, &IsomerAPI::clearFilters);
    connect(ui->pb_applyFilters,  &QPushButton::clicked, this, &IsomerAPI::applyFilters);
    connect(ui->pb_levelScheme,   &QPushButton::clicked, this, &IsomerAPI::openDrawing);
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

IsomerAPI::~IsomerAPI()
{
    dbLevels.close();
    dbGammas.close();
    delete ui;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::refreshTableView()
{
    // SQL column order must match headerNames exactly
    QString sql =
        "SELECT g.A_IT, g.Z_IT, "
        "g.E_GAMMA, g.D_EG, "
        "g.IT_RATIO, g.D_IT_RATIO, "
        "l.T12, l.D_T12, "
        "l.LEVEL, l.D_LEVEL, l.JPI, "
        "g.I_GAMMA, g.D_IG, "
        "g.M_GAMMA, g.M_RATIO, g.D_MRATIO, "
        "g.CONV, g.D_CONV, "
        "g.SOURCE, g.NAME, "
        "g.INDEX_IT, g.ROW "
        "FROM Gammas g "
        "LEFT JOIN LevelsDB.Levels l ON g.LEVEL_ID = l.LEVEL_ID";

    if (!activeFilter.isEmpty())
        sql += " WHERE " + activeFilter;

    model->setQuery(QSqlQuery(sql, dbGammas));

    if (model->lastError().isValid())
        qDebug() << "[refreshTableView ERROR]" << model->lastError().text();

    int headerIndex = 0;
    for (const QString &header : headerNames) {
        model->setHeaderData(headerIndex, Qt::Horizontal, header);
        headerIndex++;
    }
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::sumStatRefresh()
{
    QString queryStr = "SELECT MAX(E_GAMMA) FROM Gammas";
    QVariant val = queryModel(queryStr);
    qDebug() << "[sumStatRefresh(): max E_GAMMA]" << val;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QVariant IsomerAPI::queryModel(const QString &queryRequest)
{
    QString fullQuery = queryRequest;
    if (!activeFilter.isEmpty())
        fullQuery += " WHERE " + activeFilter;

    if (query.exec(fullQuery) && query.next()) {
        qDebug() << "[queryModel -- query value]" << query.value(0);
        return {query.value(0)};
    }
    return {};
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::sourceFilter()
{
    QString text = ui->cb_sourceFilter->currentText();
    qDebug() << "[sourceFilter TEXT]:" << text;
    QStringList reqSources = text.split(';', Qt::SkipEmptyParts);

    if (reqSources.contains("All Sources")) {
        activeFilter = "";
    } else {
        QStringList quoted;
        for (const QString &src : reqSources)
            quoted.append("'" + src + "'");
        activeFilter = QString("g.SOURCE IN (%1)").arg(quoted.join(','));
        qDebug() << "[sourceFilter: filter set]" << quoted.join(',');
    }
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::applyFilters()
{
    sourceFilter();
    sumStatRefresh();

    QMap<QString, QString> filterMap = {
        {"le_GE",   "g.E_GAMMA"},
        {"le_IGAM", "g.I_GAMMA"},
        {"le_numA", "g.A_IT"},
        {"le_numZ", "g.Z_IT"},
        {"le_T12",  "l.T12"},
        {"le_FINE", "l.LEVEL"}
    };

    QString filterExpr = activeFilter;

    for (QLineEdit *le : std::as_const(filterBounds)) {
        if (le->text().isEmpty()) continue;

        QString objName  = le->objectName();
        QString baseName = objName.left(objName.length() - 1);
        QString suffix   = objName.right(1);

        qDebug() << "[applyFilters: name parse]" << objName << baseName << suffix;

        if (filterMap.contains(baseName)) {
            QString col   = filterMap[baseName];
            QString value = le->text();
            QString condition;

            condition = (suffix == "1")
                            ? QString("%1 > %2").arg(col, value)
                            : QString("%1 < %2").arg(col, value);

            if (!filterExpr.isEmpty()) filterExpr += " AND ";
            filterExpr += condition;

        } else if (baseName == "le_num") {
            QString col = (suffix == "A") ? "g.A_IT" : "g.Z_IT";
            QString condition = QString("%1 IS %2").arg(col, le->text());
            if (!filterExpr.isEmpty()) filterExpr += " AND ";
            filterExpr += condition;
            qDebug() << "[applyFilters: A/Z filter]" << col << le->text();
        }

        qDebug() << "[applyFilters: filterExpr so far]" << filterExpr;
    }

    activeFilter = filterExpr;
    refreshTableView();
    ui->tableView->setModel(model);
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::clearFilters()
{
    for (QLineEdit *le : std::as_const(filterBounds)) {
        qDebug() << "[clearFilters: object]" << le->objectName();
        if (!le->objectName().isEmpty())
            le->setText("");
    }
    applyFilters();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::openDrawing()
{
    qDebug() << "[openDrawing: BEGIN]";
    auto selectedIsotopes = prepData();
    auto *mw = new LevelScheme(selectedIsotopes, this);
    mw->show();
    mw->activateWindow();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QHash<QPair<int,int>, Isotope> IsomerAPI::prepData()
{
    qDebug() << "[prepData: BEGIN]";

    QString gammaFilter = activeFilter;
    QHash<QPair<int,int>, Isotope> isotopeMap;

    // === collect INDEX_IT values ======================================================
    QString indexQuery =
        "SELECT DISTINCT g.INDEX_IT, g.A_IT, g.Z_IT, g.E_GAMMA "
        "FROM Gammas g "
        "LEFT JOIN LevelsDB.Levels l ON g.LEVEL_ID = l.LEVEL_ID";
    if (!gammaFilter.isEmpty())
        indexQuery += " WHERE " + gammaFilter;

    QSqlQuery gQuery(dbGammas);
    gQuery.exec(indexQuery);

    QStringList indexKeys;
    while (gQuery.next())
        indexKeys.append(gQuery.value("INDEX_IT").toString());

    if (indexKeys.isEmpty()) {
        qDebug() << "[prepData: no rows in current filter]";
        return isotopeMap;
    }

    // === get matching levels ======================================================
    QHash<qint64, Level> levelCache;
    QSqlQuery lQuery(dbLevels);
    lQuery.exec(QString(
                    "SELECT INDEX_IT, LEVEL, JPI, T12 "
                    "FROM Levels WHERE INDEX_IT IN (%1)"
                    ).arg(indexKeys.join(',')));

    while (lQuery.next()) {
        qint64 idx = lQuery.value("INDEX_IT").toLongLong();
        Level lvl;
        lvl.lvlEnergy = lQuery.value("LEVEL").toDouble();
        lvl.spin      = lQuery.value("JPI").toString();
        lvl.halfLife  = lQuery.value("T12").toString();
        levelCache.insert(idx, lvl);
    }

    // === full query ======================================================
    QString fullGammaQuery =
        "SELECT g.INDEX_IT, g.A_IT, g.Z_IT, g.E_GAMMA "
        "FROM Gammas g "
        "LEFT JOIN LevelsDB.Levels l ON g.LEVEL_ID = l.LEVEL_ID";
    if (!gammaFilter.isEmpty())
        fullGammaQuery += " WHERE " + gammaFilter;

    QSqlQuery fullGQuery(dbGammas);
    fullGQuery.exec(fullGammaQuery);

    while (fullGQuery.next()) {
        int    A      = fullGQuery.value("A_IT").toInt();
        int    Z      = fullGQuery.value("Z_IT").toInt();
        qint64 idx    = fullGQuery.value("INDEX_IT").toLongLong();
        double eGamma = fullGQuery.value("E_GAMMA").toDouble();

        QPair<int,int> key(A, Z);
        Isotope &iso = isotopeMap[key];
        iso.A = A;
        iso.Z = Z;

        Level *levelPtr = nullptr;
        for (Level &lvl : iso.levels) {
            if (qFuzzyCompare(lvl.lvlEnergy + 1.0, levelCache.value(idx).lvlEnergy + 1.0)) {
                levelPtr = &lvl;
                break;
            }
        }

        if (!levelPtr) {
            iso.levels.append(levelCache.value(idx));
            levelPtr = &iso.levels.last();
        }

        Transition tr;
        tr.lvlEnergy = levelPtr->lvlEnergy;
        tr.emission  = eGamma;
        tr.label     = QString("%1 keV").arg(eGamma);
        levelPtr->transitions.append(tr);
    }

    // qDebug() << "[prepData: isotope count]" << isotopeMap.count();
    // for (const Isotope &iso : isotopeMap) {
    //     qDebug() << "[prepData: isotope]" << iso.A << iso.Z
    //              << "levels:" << iso.levels.count();
    // }

    return isotopeMap;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
