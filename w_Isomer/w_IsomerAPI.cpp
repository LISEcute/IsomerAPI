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
  // ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter | (Qt::Alignment)Qt::TextWordWrap);


  headerNames = {"\u03B3-ID", "A", "Z", "E\u1D67 (keV)", "dE\u1D67 (keV)",
                 "I\u1D1B", "dI\u1D1B", "T\u00BD (\u03BCs)","dT\u2081\u2082 (\u03BCs)",
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
  ui->cb_sourceFilter->addItems(entrySources);

  // Scientif notation

  // sumStatRefresh();
  connect(ui->pb_clearFilters, &QPushButton::clicked, this, &IsomerAPI::clearFilters);
  connect(ui->pb_applyFilters, &QPushButton::clicked, this, &IsomerAPI::applyFilters);
  connect(ui->pb_levelScheme, &QPushButton::clicked, this, &IsomerAPI::openDrawing);
  // connect(ui->tableView, &QAbstractItemView::scrollToBottom,this,&IsomerAPI::sumStatRefresh);
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

IsomerAPI::~IsomerAPI()
{
  dbIsomLevel.close();
  delete ui;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::sumStatRefresh()
{
  // ui -> le_entryCounts->setText(QString::number(model->rowCount()));

  QString queryStr = "SELECT MAX(E_GAMMA) FROM Isomers";
  QVariant val = queryModel(queryStr);

  qDebug() << "[IN sumStatRefresh(): val is] " << val;
  // hellish bug breaks my table refresh
  // ui -> le_maxGAMMA->setText(val.toString());
  // dbIsomLevel.close();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QVariant IsomerAPI::queryModel(const QString &queryRequest)
{
  QString fullQuery = queryRequest;
  QString filter = model->filter();
  if (!filter.isEmpty()) {
      fullQuery += " WHERE " + filter;
    }
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
  sumStatRefresh();
  qDebug() << "[sourceFILTER PATH CHECK]" << QDir::current() << QDir::currentPath();


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


      qDebug() << "[applyFilters l133: name parse check]" << objName << baseName << suffix;
      qDebug() << "[applyFilters l134: check filterExpr]" << filterExpr;

      if (filterMap.contains(baseName)) {
          QString col = filterMap[baseName];
          QString value = le->text();
          QString condition = (suffix == "1") ? QString("%1 > %2").arg(col,value)
                                              : QString("%1 < %2").arg(col,value);
          qDebug() << "[applyFilters l139: col check]" << col;
          qDebug() << "[applyFilters l140: value check]" << value;
          qDebug() << "[applyFilters l141: conditional check]" << condition;

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
          qDebug() << "[applyFilters l160: col check]" << col;
          qDebug() << "[applyFilters l161: value check]" << le->text();
        }
      qDebug() << "[applyFilters l151: Check filterExpr]:" << filterExpr;
      qDebug() << "\n";
    }

  model->setFilter(filterExpr);
  model->select();
  ui->tableView->setModel(model);
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::clearFilters()
{
  for (QLineEdit* le : std::as_const(filterBounds)) {
      QString objName = le->objectName();
      qDebug() << "[clearFilters l170: Check object name]" << objName;
      if (le->objectName() != "") {
          le->setText("");
        }
    }
  applyFilters();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::openDrawing()
{
  qDebug() << "[openDrawing: BEGIN]";
  auto selectedIsotopes = prepData();

  auto *mw = new LevelScheme(selectedIsotopes, this);

  // mw->setAttribute(Qt::WA_DeleteOnClose, true);
  mw->show();
  // mw->raise();
  mw->activateWindow();
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
  qDebug() << "[prepData: QUERY DRAFT]";


// ~~~~~ QPair<int,int> acts as isotope key with A,Z number
  QHash<QPair<int,int>,Isotope> isotopeMap;

  qDebug() << "[prepData: MAP INIT]";
  // QVector<Level> prepLevel;
  // QVector<Transition> prepTransition;

  query.exec(fullQuery);
  qDebug() << "[prepData: QUERY EXEC]";

  // prepLevel.push_back({0,"",""});

  while (query.next())
    {
      int A = query.value("A_IT").toInt();
      int Z = query.value("Z_IT").toInt();

      // ~~~~~ isotope key established
      QPair<int,int> key(A,Z);
      qDebug() << "[prepData: KEY INIT]";

      double tmpLevelE = query.value("LEVEL").toDouble();
      double tmpGammaE = query.value("E_GAMMA").toDouble();

      // double tmpFinal = tmpLevelE - tmpGammaE;
      QString tmpEmission = QString("%1 keV").arg(tmpGammaE);

      qDebug() << "[prepData: VALUES READ]";

      Isotope& iso = isotopeMap[key];
      iso.A = A;
      iso.Z = Z;
      qDebug() << "[prepData: ISO KEYING BEGIN]";

      Level* levelPtr = nullptr;
      qDebug() << "[prepData: levelPtr INIT]";

      // ~~~~~ check for level nearness -- later include customization of plots based on diff
      for (Level& lvl : iso.levels) {
          if (qFuzzyCompare(lvl.lvlEnergy + 1.0, tmpLevelE + 1.0)) {
              qDebug() << "[prepData: FUZZY COMPARING]";
              levelPtr = &lvl;
              break;
          }
      }

      // ~~~~~ if no near levels, make new entry -- watch for level skipping!!
      if (!levelPtr) {
          qDebug() << "[prepData: NO PARENTS]";
          Level newLevel;
          newLevel.lvlEnergy = tmpLevelE;
          newLevel.spin = query.value("JPI").toString();
          newLevel.halfLife = query.value("T12").toString();

          // qDebug() << "[prepData: check level skipping]";

          iso.levels.append(newLevel);
          levelPtr = &iso.levels.last();
          qDebug() << "[prepData: LEVEL APPENDED]";
      }


      // ~~~~~ add transitions
      Transition tr;

      tr.lvlEnergy = tmpLevelE;
      tr.emission = tmpGammaE;
      tr.label = tmpEmission;

      // ~~~~~ point to current level
      levelPtr -> transitions.append(tr);


      // qDebug() << "[prepData: isotope check]" << query.value("A_IT") << query.value("Z_IT");
      // prepTransition.push_back({tmpLevel, tmpFinal, tmpEmission});
      // prepLevel.push_back({tmpLevel,query.value("JPI").toString(),query.value("T12").toString()});

      // std::unordered_map<std::pair<int,int>,std::pair<QVector<Level>,QVector<Transition>>> hashPrepData;

    }

    qDebug() << "[prepData: check isotope count]" << isotopeMap.count();



    for (Isotope &storedIso : isotopeMap) {
        qDebug() << "[prepData: check isotopes key]" << storedIso.A << storedIso.Z;
        for (Level &lvl : storedIso.levels) {
            qDebug() << "[prepData: check isotope levels]" << lvl.lvlEnergy;
            for (Transition &tr : lvl.transitions) {
                qDebug() << "[prepData: check level transitions]" << tr.label;

            }
        }
        qDebug();

    }

    return isotopeMap;


  // for (const Transition &tr : prepTransition) {
  //     qDebug() << "[prepData: transition check]" << tr.lvlEnergy << tr.emission << tr.label;
  //     // qDebug() << "[prepData: isotope check]" << query.value;
  //   }
  // qDebug();
  // for (const Level &lvl : prepLevel) {
  //     qDebug() << "[prepData: level check]" << lvl.lvlEnergy << lvl.spin << lvl.halfLife;
  //   }

  // return std::make_tuple(prepLevel, prepTransition);
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
