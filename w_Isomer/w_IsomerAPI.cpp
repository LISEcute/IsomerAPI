#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "w_levelScheme.h"
#include "L_isomerAPIversion.h"

#include <QSqlError>
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
    // table config
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


  // Database initialization

  // there is a smarter way to write this path with QDir() but I do not know how to escape the builder.

  dbPath = QCoreApplication::applicationDirPath() + "/lisecfg/Isomer_DB_WIDGET.sqlite";
  // dbPath = QDir::currentPath() + "/lisecfg/Isomer_DB_WIDGET.sqlite";
  qDebug() << "[cpp_isomerapi BUILD PATH:]" << QDir::currentPath() << dbPath << QFile::exists(dbPath);
  dbIsomLevel = QSqlDatabase::addDatabase("QSQLITE","IsomDB");
  // point to external IsomDb in LISE
  dbIsomLevel.setDatabaseName(dbPath);
  if(!dbIsomLevel.open()){
      qCritical() << "Failted to open DB:" << dbIsomLevel.lastError().text();
    }



  qDebug() << "[cpp_isomerapi DBPATH:] " << dbPath;
  model = new QSqlTableModel(this, dbIsomLevel);
  model->setTable("Isomers");
  model->select();

  ui->tableView->setModel(model);
  ui->tableView->horizontalHeader()->moveSection(0,20);
  ui->tableView->setSortingEnabled(true);
  // ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter | (Qt::Alignment)Qt::TextWordWrap);


  headerNames = {"\u03B3-ID", "A", "Z", "E\u1D67 (keV)", "dE\u1D67 (keV)",
                 "I\u1D1B", "dI\u1D1B", "T\u2081\u2082 (\u03BCs)","dT\u2081\u2082 (\u03BCs)",
                 "E(level) (keV)", "dE(level) (keV)", "J\u03C0",
                 "I\u1D67", "dI\u1D67", "M\u1D67"};

  int headerIndex = 0;
  for (QString header : headerNames) {
      model->setHeaderData(headerIndex, Qt::Horizontal, header);
      headerIndex++;
  }
  // QString("T\u2081\u2044\u2082");
  // QString("E\u1D62\u1D63\u1D62 (keV)", "dE\u1D62\u1D63\u1D62 (keV)")

  // Contained utility/attribute declaration
  query = QSqlQuery(dbIsomLevel);
  filterBounds = ui->gb_tableFilters->findChildren<QLineEdit*>();

  // Source combo box config
  ui->cb_sourceFilter->addItem("All Sources");
  ui->cb_sourceFilter->addItem("Semicolon;List;Sources");

  if(query.exec("SELECT DISTINCT SOURCE FROM Isomers"))
    {
      while (query.next()) {
          QString src = query.value(0).toString();
          entrySources.append(src);
        }
    }

  // qDebug() << "[Init l41: Entry source check]: " << entrySources;

//
  ui->cb_sourceFilter->addItems(entrySources);
  selectedIsotopes = prepData();
  statRefresh();

  // Scientif notation

  // sumStatRefresh();
  connect(ui->pb_clearFilters, &QPushButton::clicked, this, &IsomerAPI::clearFilters);
  connect(ui->pb_applyFilters, &QPushButton::clicked, this, &IsomerAPI::applyFilters);
  connect(ui->pb_levelScheme, &QPushButton::clicked, this, &IsomerAPI::openDrawing);
  // connect(ui->tableView, &QAbstractItemView::scrollToBottom,this,&IsomerAPI::sumStatRefresh);

  qDebug();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

IsomerAPI::~IsomerAPI()
{
  dbIsomLevel.close();
  delete ui;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::statRefresh()
{
  // qDebug() << "[IN sumStatRefresh(): val is] " << val;

  queryStr = "SELECT COUNT(A_IT) FROM Isomers";
  QVariant isomCount = queryModel(queryStr);

  queryStr = "SELECT MIN(E_GAMMA) FROM Isomers";
  QVariant minGamma = queryModel(queryStr);

  queryStr = "SELECT MAX(E_GAMMA) FROM Isomers";
  QVariant maxGamma = queryModel(queryStr);

  queryStr = "SELECT MIN(T12) FROM Isomers";
  QVariant minT12 = queryModel(queryStr);

  queryStr = "SELECT MAX(T12) FROM Isomers";
  QVariant maxT12 = queryModel(queryStr);


  ui->le_isomerCounts->setText(isomCount.toString());
  ui->le_isotopeCounts->setText(QString::number(selectedIsotopes.size()));

  // if(!selectedIsotopes.empty()){
  //   ui->le_isotopeCounts->setText(QString::number(selectedIsotopes.size()));
  // }

  ui->le_lowGammaSum->setText(minGamma.toString());
  ui->le_highGammaSum->setText(maxGamma.toString());

  ui->le_lowT12Sum->setText(minT12.toString());
  ui->le_highT12Sum->setText(maxT12.toString());



  // ui -> le_maxGAMMA->setText(val.toString());

  qDebug() << "[sumStatRefresh: GAMMAS, T12s] " << minGamma << maxGamma << minT12 << maxT12;
  // hellish bug breaks my table refresh
  // dbIsomLevel.close();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QVariant IsomerAPI::queryModel(const QString &queryRequest)
{
  QString fullQuery = queryRequest;
  QString filter = model->filter();
  // qDebug() << "[queryModel FILTER VALUE]" << filter;
  if (!filter.isEmpty()) {
      fullQuery += " WHERE " + filter;
    }
  if (query.exec(fullQuery) && query.next()) {
      // qDebug() << "[queryModel -- query value]" << query.value(0);
      return {query.value(0)};
    }
  return {};
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::sourceFilter()
{
  QString text = ui->cb_sourceFilter->currentText();
  qDebug() << "[sourceFilter l70 TEXT]: " << text;
  QStringList reqSources = text.split(';', Qt::SkipEmptyParts);

  if (reqSources.contains("All Sources")) {
      model -> setFilter("");
    } else {
      QStringList quoted;
      for (const QString &src : reqSources) {
          quoted.append("'" + src + "'");

        }
      model->setFilter(QString("SOURCE IN (%1)").arg(quoted.join(',')));
      qDebug() << "[sourceFilter l77: NO ALL SOURCES]: " << quoted;
      qDebug() << "[sourceFilter l78: Check format for SQL]: " << quoted.join(',');
    }
  qDebug() << "\n";

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::applyFilters()
{
  sourceFilter();

  qDebug() << "[sourceFILTER PATH CHECK]" << QDir::current() << QDir::currentPath();
  qDebug() << "[applyFilters: FILTER VALUE?]" << model->filter();

  QMap<QString, QString> filterMap = {
    {"le_T12", "T12"},
    {"le_GE", "E_GAMMA"},
    {"le_IGAM", "I_GAMMA"},
    {"le_FINE", "LEVEL"},
    {"le_numA", "A_IT"},
    {"le_numZ", "Z_IT"}
  };

  QString filterExpr = model->filter();
  for (QLineEdit* le : std::as_const(filterBounds)) {
      if (le->text().isEmpty()) {
          continue;
        }

      QString objName = le->objectName();
      QString baseName = objName.left(objName.length() - 1);
      QString suffix = objName.right(1);


      // qDebug() << "[applyFilters l133: name parse check]" << objName << baseName << suffix;
      // qDebug() << "[applyFilters l134: check filterExpr]" << filterExpr;

      if (filterMap.contains(baseName)) {
          QString col = filterMap[baseName];
          QString value = le->text();
          QString condition = (suffix == "1") ? QString("%1 > %2").arg(col,value)
                                              : QString("%1 < %2").arg(col,value);
          // qDebug() << "[applyFilters l139: col check]" << col;
          // qDebug() << "[applyFilters l140: value check]" << value;
          // qDebug() << "[applyFilters l141: conditional check]" << condition;

          if (!filterExpr.isEmpty()) {
              filterExpr += " AND ";
            }
          filterExpr += condition;



        } else if (baseName == "le_num") {
          QString col = (suffix == "A") ? "A_IT" : "Z_IT";
          QString condition = QString("%1 IS %2").arg(col, le->text());


          if (!filterExpr.isEmpty()) {
              filterExpr += " AND ";
            }
          filterExpr += condition;
          // qDebug() << "[applyFilters l160: col check]" << col;
          // qDebug() << "[applyFilters l161: value check]" << le->text();
        }
      qDebug();

    }

  model->setFilter(filterExpr);
  model->select();
  ui->tableView->setModel(model);
  qDebug() << "[applyFilters: Check filterExpr]:" << filterExpr << model->filter();

  selectedIsotopes = prepData();
  qDebug() << "[applyFilters: isotope count]" << selectedIsotopes.count() << selectedIsotopes.size();

  statRefresh();

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::clearFilters()
{
    // ~~~ Define sumamryStats groupbox lines for easy clearing
    summaryStats = ui->gb_summaryStats->findChildren<QLineEdit*>();

    // qDebug() << "[clearFilters: groupbox type?]" << std::as_const(filterBounds) + std::as_const(summaryStats);
    for (QLineEdit* le : std::as_const(filterBounds) + (std::as_const(summaryStats))) {
      QString objName = le->objectName();
      // qDebug() << "[clearFilters l170: Check object name]" << objName;
      if (le->objectName() != "") {
          le->setText("");
        }
    }

    applyFilters();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::openDrawing()
{
  // qDebug() << "[openDrawing: BEGIN]";

  auto *levelScheme = new LevelScheme(selectedIsotopes);

  // mw->setAttribute(Qt::WA_DeleteOnClose, true);
  levelScheme->show();
  // mw->raise();
  levelScheme->activateWindow();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

// std::tuple<QVector<Level>,QVector<Transition>> IsomerAPI::prepData()
// {

//   QString fullQuery = "SELECT A_IT,Z_IT,E_GAMMA,D_EG,T12,D_T12,LEVEL,D_LEVEL,JPI FROM Isomers";
//   QString filter = model->filter();
//   if (!filter.isEmpty()) {
//       fullQuery += " WHERE " + filter;
//     }

//   QVector<Level> prepLevel;
//   QVector<Transition> prepTransition;
//   query.exec(fullQuery);

//   prepLevel.push_back({0,"",""});

//   while (query.next())
//     {
//       double tmpLevel = query.value("LEVEL").toDouble();
//       double tmpGamma = query.value("E_GAMMA").toDouble();
//       double tmpFinal = tmpLevel - tmpGamma;
//       QString tmpEmission = QString("%1 keV").arg(tmpGamma);
//       qDebug() << "[prepData: isotope check]" << query.value("A_IT") << query.value("Z_IT");
//       prepTransition.push_back({tmpLevel, tmpFinal, tmpEmission});
//       prepLevel.push_back({tmpLevel,query.value("JPI").toString(),query.value("T12").toString()});

//       // std::unordered_map<std::pair<int,int>,std::pair<QVector<Level>,QVector<Transition>>> hashPrepData;

//     }

//   for (const Transition &tr : prepTransition) {
//       qDebug() << "[prepData: transition check]" << tr.lvlEnergy << tr.emission << tr.label;
//       // qDebug() << "[prepData: isotope check]" << query.value;
//     }
//   qDebug();
//   for (const Level &lvl : prepLevel) {
//       qDebug() << "[prepData: level check]" << lvl.lvlEnergy << lvl.spin << lvl.halfLife;
//     }

//   return std::make_tuple(prepLevel, prepTransition);
// }

QHash<QPair<int,int>,Isotope> IsomerAPI::prepData()
{

  qDebug() << "[prepData: BEGIN PREP]";
  QString fullQuery =
        "SELECT A_IT,Z_IT,E_GAMMA,D_EG,T12,D_T12,LEVEL,D_LEVEL,JPI FROM Isomers";

  QString filter = model->filter();
  if (!filter.isEmpty()) {
      fullQuery += " WHERE " + filter;
    }


// ~~~~~ QPair<int,int> acts as isotope key with A,Z number
  QHash<QPair<int,int>,Isotope> isotopeMap;

  // QVector<Level> prepLevel;
  // QVector<Transition> prepTransition;

  query.exec(fullQuery);

  // prepLevel.push_back({0,"",""});

  while (query.next())
    {
      int A = query.value("A_IT").toInt();
      int Z = query.value("Z_IT").toInt();

      // ~~~~~ isotope key established
      QPair<int,int> key(A,Z);

      double tmpLevelE = query.value("LEVEL").toDouble();
      double tmpGammaE = query.value("E_GAMMA").toDouble();

      // double tmpFinal = tmpLevelE - tmpGammaE;
      QString tmpEmission = QString("%1 keV").arg(tmpGammaE);

      Isotope& iso = isotopeMap[key];
      iso.A = A;
      iso.Z = Z;

      Level* levelPtr = nullptr;

      // ~~~~~ check for level nearness -- later include customization of plots based on diff
      for (Level& lvl : iso.levels) {
          if (qFuzzyCompare(lvl.lvlEnergy + 1.0, tmpLevelE + 1.0)) {
              levelPtr = &lvl;
              break;
          }
      }

      // ~~~~~ if no near levels, make new entry -- watch for level skipping!!
      if (!levelPtr) {
          Level newLevel;
          newLevel.lvlEnergy = tmpLevelE;
          newLevel.spin = query.value("JPI").toString();
          newLevel.halfLife = query.value("T12").toString();

          // qDebug() << "[prepData: check level skipping]";

          iso.levels.append(newLevel);
          levelPtr = &iso.levels.last();
      }


      // ~~~~~ add transitions
      Transition tr;

      tr.lvlEnergy = tmpLevelE;
      tr.emission = tmpGammaE;
      tr.label = tmpEmission;

      // ~~~~~ point to current level
      levelPtr -> transitions.append(tr);

      // qDebug() << "[prepData: isotope check]" << query.value("A_IT") << query.value("Z_IT");

    }

    qDebug() << "[prepData: check isotope count]" << isotopeMap.count();

    // for (Isotope &storedIso : isotopeMap) {
    //     qDebug() << "[prepData: check isotopes key]" << storedIso.A << storedIso.Z;
    //     for (Level &lvl : storedIso.levels) {
    //         qDebug() << "[prepData: check isotope levels]" << lvl.lvlEnergy;
    //         for (Transition &tr : lvl.transitions) {
    //             qDebug() << "[prepData: check level transitions]" << tr.label;

    //         }
    //     }
    //     qDebug();

    // }

    return isotopeMap;

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
