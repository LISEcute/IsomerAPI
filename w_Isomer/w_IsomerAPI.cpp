#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "w_downloaddialog.h"
#include "w_levelScheme.h"
#include "L_isomerAPIversion.h"
#include "w_about.h"
#include "L_element.h"

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
    modelFull(nullptr),
    modelIsomers(nullptr),
    modelGammas(nullptr)


{
  ui->setupUi(this);

  setMinimumSize(800, 600);
  resize(1200,600);
    // table config
  // ui->tableView_Full->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  qDebug() << "Element Test: " << atomicSymbol(7) << atomicSymbol("N") << atomicSymbol("n") << atomicSymbol("mg");

  // Database initialization
  // there is a smarter way to write this path with QDir() but I do not know how to escape the builder.

  dbPath = QCoreApplication::applicationDirPath() + "/lisecfg/IsomerDB_Split.sqlite";
  // dbPath = QDir::currentPath() + "/lisecfg/Isomer_DB_WIDGET.sqlite";
  qDebug() << "[cpp_isomerapi BUILD PATH:]" << QDir::currentPath() << dbPath << QFile::exists(dbPath);

  dbIsomLevel = QSqlDatabase::addDatabase("QSQLITE","IsomDB");
  // point to external IsomDb in LISE
  dbIsomLevel.setDatabaseName(dbPath);
  if(!dbIsomLevel.open()){
      qCritical() << "Failted to open DB:" << dbIsomLevel.lastError().text();
    }

  // Initialize the three models we will use
  qDebug() << "[cpp_isomerapi DBPATH:] " << dbPath;
  modelFull = new QSqlTableModel(this, dbIsomLevel);
  modelIsomers = new QSqlTableModel(this, dbIsomLevel);
  modelGammas = new QSqlTableModel(this, dbIsomLevel);

  modelIsomers->setTable("isomerLevels");
  modelIsomers->select();

  modelGammas->setTable("gammaEmissions");
  modelGammas->select();
  // ~~~ Vectorize models?
  // modelsVector = {modelFull, modelIsomers, modelGammas};

  modelFull->setTable("Isomers");
  modelFull->select();

  modelsVector = {modelIsomers, modelGammas, modelFull};

  modelTuples.push_back(std::make_tuple(modelFull, "Isomers",ui->tableView_Dev));
  modelTuples.push_back(std::make_tuple(modelIsomers, "isomerLevels",ui->tableView_Isomer));
  modelTuples.push_back(std::make_tuple(modelGammas, "gammaEmissions",ui->tableView_Gammas));
  modelTuples.push_back(std::make_tuple(modelIsomers, "gammaEmissions",ui->tableView_IsomerSolo));
  modelTuples.push_back(std::make_tuple(modelGammas, "gammaEmissions",ui->tableView_GammaSolo));

  QMap<QString, QString> headerMap = {
      {"INDEX_IT", "\u03B3-ID"}, {"A_IT","A"}, {"Z_IT","Z"},
      {"E_GAMMA","E\u1D67 (keV)"}, {"D_EG","dE\u1D67 (keV)"},
      {"IT_RATIO","I\u1D1B"}, {"D_IT_RATIO","dI\u1D1B"},
      {"T12","T\u2081\u2082 (\u03BCs)"}, {"D_T12","dT\u2081\u2082 (\u03BCs)"},
      {"LEVEL","E(level) (keV)"}, {"D_LEVEL","dE(level) (keV)"},
      {"JPI","J\u03C0"}, {"I_GAMMA","I\u1D67"}, {"D_IG","dI\u1D67"},
      {"M_GAMMA","M\u1D67"}, {"M_RATIO","M_RATIO"}, {"D_MRATIO","D_MRATIO"},
      {"SOURCE","SOURCE"}, {"ROW","ROW"}, {"NAME","NAME"}
  };

  // auto headerNames = {"\u03B3-ID", "A", "Z", "E\u1D67 (keV)", "dE\u1D67 (keV)",
  //                     "I\u1D1B", "dI\u1D1B", "T\u2081\u2082 (\u03BCs)","dT\u2081\u2082 (\u03BCs)",
  //                     "E(level) (keV)", "dE(level) (keV)", "J\u03C0",
  //                     "I\u1D67", "dI\u1D67", "M\u1D67"};


  for (auto &tuple : modelTuples) {
      auto [model, tableName, uiView] = tuple;
      qDebug() << "[IsomerAPI model initialization] model, table, view" << model << tableName << uiView;

      uiView->setModel(model);
      uiView->horizontalHeader()->moveSection(0,20);
      uiView->hideColumn(model->fieldIndex("CONV"));
      uiView->hideColumn(model->fieldIndex("D_CONV"));
      uiView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

      uiView->setSortingEnabled(true);

      // int headerIndex = 0;
      for (int i = 0; i <= model->columnCount(); i++) {
          QString headerKey = model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
          // qDebug() << "[IsomerAPI header check]" << headerKey << headerMap.value(headerKey);
          if (headerMap.contains(headerKey)) {
              // qDebug() << "[IsomerAPI Header check] replace header triggered";
              model->setHeaderData(i, Qt::Horizontal, headerMap.value(headerKey));
          }

      };
      // for (QString headerKey : headerMap.keys()) {
      //     qDebug() << "[IsomerAPI header check]" << headerKey << headerMap.value(headerKey);
      //     model->setHeaderData(headerIndex, Qt::Horizontal, headerMap.value(headerKey));
      //     headerIndex++;
      // }

  }

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
  selectedIsotopes = prepData();
  statRefresh();

  // Scientif notation

  connect(ui->pb_clearFilters, &QPushButton::clicked, this, &IsomerAPI::clearFilters);
  connect(ui->pb_applyFilters, &QPushButton::clicked, this, &IsomerAPI::applyFilters);
  connect(ui->pb_levelScheme, &QPushButton::clicked, this, &IsomerAPI::openDrawing);

  // stacked widget setup
  ui->stackedWidget->setCurrentIndex(2);
  connect(ui->actionIsomer_Emission_Split,&QAction::triggered,this,[this](){
      qDebug() << "actionFullDataView Connected";
      ui->stackedWidget->setCurrentIndex(2);
  });

  connect(ui->actionIsomers,&QAction::triggered,this,[this](){
      ui->stackedWidget->setCurrentIndex(1);
  });

  connect(ui->actionGammas,&QAction::triggered,this,[this](){
      ui->stackedWidget->setCurrentIndex(0);
  });

  connect(ui->actionDevelopment_View,&QAction::triggered,this,[this](){
      ui->stackedWidget->setCurrentIndex(3);
  });

  qDebug();
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

IsomerAPI::~IsomerAPI()
{
  dbIsomLevel.close();
  delete ui;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::on_action_About_triggered(){
    About *about_page = new About;
    about_page->setWindowFlags(Qt::CustomizeWindowHint |
                               Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    about_page->show();
}

void IsomerAPI::on_pb_downloadCSV_clicked(){
    qDebug() << "[downloadCSV TRIGGERED]";
    DownloadDialog downlaodDlg(this);
    // downlaodDlg->setWindowFlags(Qt::CustomizeWindowHint |
    //                            Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    if (downlaodDlg.exec() != QDialog::Accepted)
        return;
    // downlaodDlg->show();
}


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

  ui->le_lowGammaSum->setText(minGamma.toString());
  ui->le_highGammaSum->setText(maxGamma.toString());

  ui->le_lowT12Sum->setText(minT12.toString());
  ui->le_highT12Sum->setText(maxT12.toString());


  // qDebug() << "[sumStatRefresh: GAMMAS, T12s] " << minGamma << maxGamma << minT12 << maxT12;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QVariant IsomerAPI::queryModel(const QString &queryRequest)
{
  QString fullQuery = queryRequest;
  QString filter = modelFull->filter(); // ``` model full attempt
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

  for (auto &model : modelsVector) {

      if (reqSources.contains("All Sources")) {
          model -> setFilter("");
          qDebug() << "[sourceFilter: All sources triggered - clear filters]";
      } else {
          QStringList quoted;
          for (const QString &src : reqSources) {
              quoted.append("'" + src + "'");

          }
          model->setFilter(QString("SOURCE IN (%1)").arg(quoted.join(',')));
          qDebug() << "[sourceFilter l77: NO ALL SOURCES]: " << quoted;
          qDebug() << "[sourceFilter l78: Check format for SQL]: " << quoted.join(',');
      }

  }
  // if (reqSources.contains("All Sources")) {
  //     model -> setFilter("");
  //   } else {
  //     QStringList quoted;
  //     for (const QString &src : reqSources) {
  //         quoted.append("'" + src + "'");

  //       }
  //     model->setFilter(QString("SOURCE IN (%1)").arg(quoted.join(',')));
  //     qDebug() << "[sourceFilter l77: NO ALL SOURCES]: " << quoted;
  //     qDebug() << "[sourceFilter l78: Check format for SQL]: " << quoted.join(',');
  //   }
  qDebug() << "\n";

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
// ```` OKAY i need to come back and fix the filtering methods for the new two stable split
// ```` lord have mercy.
void IsomerAPI::applyFilters()
{
  sourceFilter();

  // qDebug() << "[sourceFILTER PATH CHECK]" << QDir::current() << QDir::currentPath();
  qDebug() << "[applyFilters: FILTER VALUE?]" << modelFull->filter();

  QMap<QString, QString> filterMap = {
    {"le_T12", "T12"},
    {"le_GE", "E_GAMMA"},
    {"le_FINE", "LEVEL"},
    {"le_numA", "A_IT"},
    {"le_numZ", "Z_IT"}
  };

  QString filterExpr = modelFull->filter(); // ~~~ treat modelFull first -- cut on T12, Egam later

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
          qDebug() << "[applyFilters: check filterexpr]" << filterExpr;



        } else if (baseName == "le_num") {
          // QString col = (suffix == "A") ? "A_IT" : "Z_IT";
          // QString condition = QString("%1 IS %2").arg(col, le->text());
            QString col = (suffix == "A") ? "A_IT" : "Z_IT";
            QString textValue = le->text();
            QString finalValue;

            // ~~~~ .toInt ONLY CHECKS FIRST CHARACTER!!!!!
            bool isInt;
            textValue.toInt(&isInt);
            qDebug() << "[applyFilters: le_num case, check isInt, testValue]" <<  isInt << textValue;

            if (isInt) {
                // It's already a number (e.g., "6")
                finalValue = textValue;
            } else {

                // It's a string (e.g., "C"), get the atomic number
                // Note: Ensure atomicSymbol() returns a QString or use QString::number()
                finalValue = QString::number(atomicSymbol(textValue));
                qDebug() << "[applyFilters: le_num string entered, check atomicSymobls output]" << atomicSymbol(textValue);
            }
            qDebug() << "[applyFilters: le_num case, check finalValue]" << finalValue;

            QString condition = QString("%1 IS %2").arg(col, finalValue);

            if (!filterExpr.isEmpty()) {
                filterExpr += " AND ";
            }
            filterExpr += condition;
        }



          // if (!filterExpr.isEmpty()) {
          //     filterExpr += " AND ";
          //   }
          // filterExpr += condition;
          // qDebug() << "[applyFilters l160: col check]" << col;
          // qDebug() << "[applyFilters l161: value check]" << le->text();
        // }
      qDebug();

    }

  modelFull->setFilter(filterExpr);
  modelFull->select();
  ui->tableView_Dev->setModel(modelFull);
  // qDebug() << "[applyFilters: Check filterExpr]:" << filterExpr << model->filter();

  selectedIsotopes = prepData();
  qDebug() << "[applyFilters: isotope count]" << selectedIsotopes.count() << selectedIsotopes.size();

  statRefresh();

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::clearFilters()
{
    // ~~~ Define sumamryStats groupbox lines for easy clearing
    summaryStats = ui->gb_summaryStats->findChildren<QLineEdit*>();
    qDebug() << "[clearFilters CHECK FULL FILTER - before]" << modelFull->filter();

    // qDebug() << "[clearFilters: groupbox type?]" << std::as_const(filterBounds) + std::as_const(summaryStats);
    for (QLineEdit* le : std::as_const(filterBounds) + (std::as_const(summaryStats))) {
      QString objName = le->objectName();
      // qDebug() << "[clearFilters l170: Check object name]" << objName;
      if (le->objectName() != "") {
          le->setText("");
        }
    }

    applyFilters();
    qDebug() << "[clearFilters CHECK FULL FILTER - after]" << modelFull->filter();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::openDrawing()
{
  auto *levelScheme = new LevelScheme(selectedIsotopes, this);

  levelScheme->show();
  // levelScheme->activateWindow();
}


// ~~~~ this is doing nothing
void IsomerAPI::viewSelect()
{
    qDebug() << "[viewSelect: triggered]";
    ui->stackedWidget->currentIndex();
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QHash<QPair<int,int>,Isotope> IsomerAPI::prepData()
{

  qDebug() << "[prepData: BEGIN PREP]";
  QString fullQuery =
        "SELECT A_IT,Z_IT,E_GAMMA,D_EG,T12,D_T12,LEVEL,D_LEVEL,JPI FROM Isomers";

  QString filter = modelFull->filter();
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
      QString tmpEmission = QString("%1").arg(tmpGammaE);

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
