#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "d_Download.h"
#include "w_levelScheme.h"
#include "w_about.h"
#include "L_isomerAPIversion.h"
#include "L_element.h"

#include <QSqlError>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>

#include "L_Init/declare_IsomerAPI.h"

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

  setMinimumSize(800, 650);
  resize(1200,650);
    // table config
  // ui->tableView_Full->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  /// Database initialization

        // dbPath = QCoreApplication::applicationDirPath() + "/lisecfg/IsomerDB_Split.sqlite";

  dbPath = QCoreApplication::applicationDirPath() + "/lisecfg/nndc_DB.sqlite";

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
      {"E_GAMMA","E\u1D67 (keV)"}, {"D_EG","\u03B4E\u1D67 (keV)"},
      {"IT_RATIO","I\u1D63"}, {"D_IT_RATIO","\u03B4I\u1D63"},
      {"T12","T\u2081\u2082 (\u03BCs)"}, {"D_T12","\u03B4T\u2081\u2082 (\u03BCs)"},
      {"LEVEL","E(level) (keV)"}, {"D_LEVEL","\u03B4E(level) (keV)"},
      {"JPI","J\u03C0"}, {"I_GAMMA","I\u1D67"}, {"D_IG","\u03B4I\u1D67"},
      {"M_GAMMA","M\u1D67"}, {"M_RATIO","M_RATIO"}, {"D_MRATIO","D_MRATIO"},
      {"SOURCE","SOURCE"}, {"ROW","ROW"}, {"NAME","NAME"}
  };

  // auto headerNames = {"\u03B3-ID", "A", "Z", "E\u1D67 (keV)", "dE\u1D67 (keV)",
  //                     "I\u1D1B", "dI\u1D1B", "T\u2081\u2082 (\u03BCs)","dT\u2081\u2082 (\u03BCs)",
  //                     "E(level) (keV)", "dE(level) (keV)", "J\u03C0",
  //                     "I\u1D67", "dI\u1D67", "M\u1D67"};


  for (auto &tuple : modelTuples) {
      auto [model, tableName, uiView] = tuple;
      // qDebug() << "[IsomerAPI model initialization] model, table, view" << model << tableName << uiView;

      uiView->setModel(model);
      uiView->horizontalHeader()->moveSection(0,20);
      uiView->hideColumn(model->fieldIndex("M_RATIO"));
      uiView->hideColumn(model->fieldIndex("D_MRATIO"));
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

  connect(ui->pb_gammas_view, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});
  connect(ui->pb_isomers_view, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
  connect(ui->pb_isomers_gammas_view, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(2);});

  // stacked widget setup
  // temporary we call Development
  ui->stackedWidget->setCurrentIndex(3);
  ui->pb_isomers_gammas_view->setChecked(true);

  connect(ui->actionIsomer_Emission_Split,&QAction::triggered,this,[this](){
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
  query.finish();
  query.clear();

  ui->tableView_Dev->setModel(nullptr);
  ui->tableView_Isomer->setModel(nullptr);
  ui->tableView_Gammas->setModel(nullptr);
  ui->tableView_IsomerSolo->setModel(nullptr);
  ui->tableView_GammaSolo->setModel(nullptr);

  delete modelFull;
  delete modelIsomers;
  delete modelGammas;

  modelFull = nullptr;
  modelIsomers = nullptr;
  modelGammas = nullptr;

  dbIsomLevel.close();

  delete ui;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::on_actionAbout_triggered()
{
    About *about_page = new About;
    about_page->setWindowFlags(Qt::CustomizeWindowHint |
                               Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    about_page->show();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::on_actionSave_As_triggered(){
    qDebug() << "[downloadCSV TRIGGERED]";
    DownloadDialog downloadDlg(this);
    // downlaodDlg->setWindowFlags(Qt::CustomizeWindowHint |
    //                            Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    // downlaodDlg->show();

    if (downloadDlg.exec() == QDialog::Accepted) {
        qDebug() << "[downloadDlg: dlg result]" << downloadDlg.getSelection();

        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save CSV File"), "untitled_isomer_table", tr("CSV Files (*.csv);;Text Files (*.txt);;All Files (*)"));
        QString textData = QString("this is the line i write");
        // 2. Check if the user didn't cancel
        if (!fileName.isEmpty()) {
            QFile csvFile(fileName);
            if (csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                QTextStream out(&csvFile);
                out << textData;
                csvFile.close();
            }
        }
    }
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww


void IsomerAPI::statRefresh()
{
  // qDebug() << "[IN sumStatRefresh(): val is] " << val;
  qDebug();
  // ~~~~
  queryStr = "SELECT COUNT(A_IT) FROM Isomers WHERE T12>0.001";
  // queryStr = "SELECT COUNT(A_IT) FROM Isomers";

  QVariant isomCount = queryModel(queryStr);
  qDebug() << "[statRefresh: check isomer query result, string]" << isomCount << queryStr;
  // ~~~~
  qDebug();
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
  qDebug() << "[queryModel FILTER VALUE]" << filter;
  if (!filter.isEmpty()) {
      if (fullQuery.contains("WHERE", Qt::CaseInsensitive))
          fullQuery += " AND " + filter;
      else
          fullQuery += " WHERE " + filter;
      qDebug() << "[queryModel: TRIGGERED empty query]";
    }
  if (query.exec(fullQuery) && query.next()) {
        qDebug() << "[queryModel: exec, fullQuery value]" << fullQuery;
      // qDebug() << "[queryModel -- query value]" << query.value(0);
      return {query.value(0)};
  } else {
      qDebug() << "[queryModel: NO EXECUTION]" << query.lastError().text();
  }
  return {};
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::sourceFilter()
{
  // empty entry safety net
  if (ui->cb_sourceFilter->currentText() == "") ui->cb_sourceFilter->setCurrentText("All Sources");

  QString text = ui->cb_sourceFilter->currentText();
  qDebug() << "[sourceFilter l70 TEXT]: " << text;
  QStringList reqSources = text.split(';', Qt::SkipEmptyParts);

  bool validSearch = std::any_of(reqSources.begin(), reqSources.end(), [&](QString item) {
      qDebug() << "[sourceFilter: check item]" << item;
      return entrySources.contains(item);
  });

  qDebug() << "[sourceFilter: available entrySources]" << entrySources;
  for (auto &model : modelsVector) {

      if (reqSources.contains("All Sources")) {
          model -> setFilter("");
          qDebug() << "[sourceFilter: All sources triggered - clear filters]";
      } else if (!validSearch) {
          QMessageBox::critical(this,"Error!","Check the source entry is a possible source!");
          qDebug() << "[sourceFilter: INVALID SEARCH]" << reqSources;
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
  qDebug() << "\n";

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
// ~~~~ OKAY i need to come back and fix the filtering methods for the new two stable split
// ~~~~ lord have mercy.
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


      qDebug() << "[applyFilters l133: name parse check]" << objName << baseName << suffix;
      // qDebug() << "[applyFilters l134: check filterExpr]" << filterExpr;

      if (filterMap.contains(baseName)) {
          QString col = filterMap[baseName];
          QString textValue = le->text();
          QString finalValue;

          bool isInt;
          textValue.toInt(&isInt);

          if (isInt) {
              finalValue = textValue;
          } else {
              qDebug() << "[applyFilters: le_num range, check atomicSymobls output]" << atomicSymbol(textValue);
              // qDebug() << "[applyFilters: le_num string entered, check Mg output]" << atomicSymbol("Mg") << atomicSymbol(12);
              finalValue = QString::number(atomicSymbol(textValue));
          }
          // construct error bars as iterating
          QString condition = (suffix == "1") ? QString("%1 >= %2").arg(col,finalValue)
                                              : QString("%1 <= %2").arg(col,finalValue);
          // qDebug() << "[applyFilters l139: col check]" << col;
          // qDebug() << "[applyFilters l140: value check]" << value;
          // qDebug() << "[applyFilters l141: conditional check]" << condition;

          if (!filterExpr.isEmpty()) {
              filterExpr += " AND ";
            }
          filterExpr += condition;
          qDebug() << "[applyFilters: check filterexpr]" << filterExpr;



        } else if (baseName == "le_num") {
            QString col = (suffix == "A") ? "A_IT" : "Z_IT";
            QString textValue = le->text();
            QString finalValue;

            bool isInt;
            textValue.toInt(&isInt);
            qDebug() << "[applyFilters: le_num case, check isInt, testValue, symbol]" <<  isInt << textValue;

            if (isInt) {
                // It's already a number (e.g., "6")
                finalValue = textValue;
                qDebug() << "[appltFilters: le_num case, isInt==True check symbol]" << atomicSymbol(textValue);
            } else {

                // It's a string (e.g., "C"), get the atomic number
                // Note: Ensure atomicSymbol() returns a QString or use QString::number()
                finalValue = QString::number(atomicSymbol(textValue));
                qDebug() << "[applyFilters: le_num string entered, check atomicSymobls output]" << atomicSymbol(textValue);
                qDebug() << "[applyFilters: le_num string entered, check Mg output]" << atomicSymbol("Mg") << atomicSymbol(12);

            }
            qDebug() << "[applyFilters: le_num case, check finalValue]" << finalValue;

            QString condition = QString("%1 IS %2").arg(col, finalValue);

            if (!filterExpr.isEmpty()) {
                filterExpr += " AND ";
            }
            filterExpr += condition;
        }
      qDebug() << "[applyFilters: check filterexpr]" << filterExpr;

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
  auto *levelScheme = new LevelScheme(selectedIsotopes);

  levelScheme->show();
  // levelScheme->activateWindow();
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

// ~~~~ this is doing nothing
void IsomerAPI::viewSelect()
{
    qDebug() << "[viewSelect: triggered]";
    ui->stackedWidget->currentIndex();
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QMap<QPair<int,int>,Isotope> IsomerAPI::prepData()
{

  // qDebug() << "[prepData: BEGIN PREP]";
  QString fullQuery =
        "SELECT A_IT,Z_IT,E_GAMMA,D_EG,T12,D_T12,LEVEL,D_LEVEL,JPI FROM Isomers";

  QString filter = modelFull->filter();
  if (!filter.isEmpty()) {
      fullQuery += " WHERE " + filter;
    }


// QPair<int,int> acts as isotope key with A,Z number
  QMap<QPair<int,int>,Isotope> isotopeMap;

  // QVector<Level> prepLevel;
  // QVector<Transition> prepTransition;

  query.exec(fullQuery);

  // prepLevel.push_back({0,"",""});

  while (query.next())
    {
      int A = query.value("A_IT").toInt();
      int Z = query.value("Z_IT").toInt();

      // ~~~~~ isotope key established
      QPair<int,int> key(Z,A);

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
          newLevel.halfLife = query.value("T12").toDouble();

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

// void IsomerAPI::raiseError

void IsomerAPI::on_actionExit_triggered()
{
  exit(2);
}

