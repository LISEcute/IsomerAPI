#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "d_Download.h"
#include "d_Drawing.h"
#include "d_Columns.h"
#include "L_levelProxyModel.h"

#include "w_levelScheme.h"
#include "w_about.h"
#include "L_isomerAPI_version.h"
#include "L_element.h"
#include "L_gammaProxyModel.h"
#include "L_richTextHeader.h"
#include "d_Transmission.h"

#include <QSqlError>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>
#include <QShortcut>

#include "L_Init/declare_IsomerAPI.h"

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
IsomerAPI::IsomerAPI(QWidget *parent)
  :
    QMainWindow(parent),
    ui(new Ui::IsomerAPI),
    modelFull(nullptr),
    levelProxy(nullptr),
    gammaProxy(nullptr)
{
  ui->setupUi(this);

  this->setFocusPolicy(Qt::ClickFocus);

  setMinimumSize(800, 650);
  resize(1200,650);
    // table config
  // ui->tableView_Full->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  /// Database initialization
  // dbPath = QCoreApplication::applicationDirPath() + "/lisecfg/others/IsomerDB_Split.sqlite";
  dbPath = QCoreApplication::applicationDirPath() + "/lisecfg/nndc_DB_fullScan.sqlite"; // Full scan of original IsomerDB.sqlite file (all old isotopes with updated entries)

  qDebug() << "[cpp_isomerapi BUILD PATH:]" << QDir::currentPath() << dbPath << QFile::exists(dbPath);

  dbIsomLevel = QSqlDatabase::addDatabase("QSQLITE","IsomDB");
  // point to external IsomDb in LISE
  dbIsomLevel.setDatabaseName(dbPath);
  // dbIsomLevel.open();

  if(!dbIsomLevel.open()){
      qCritical() << "Failted to open DB:" << dbIsomLevel.lastError().text();
  } else if(dbIsomLevel.isOpen()) {
      qDebug() << "DB Opened";
  }

  qDebug() << "[cpp_isomerapi DBPATH:] " << dbPath;
  modelFull = new QSqlTableModel(this, dbIsomLevel);

  /// ----- DEPRECATED WITH PROXY MODEL
  // modelIsomers = new QSqlTableModel(this, dbIsomLevel);
  // modelGammas = new QSqlTableModel(this, dbIsomLevel);

  // modelIsomers->setTable("isomerLevels");
  // modelIsomers->select();

  // modelGammas->setTable("gammaEmissions");
  // modelGammas->select();

  // modelsVector = {modelIsomers, modelGammas, modelFull};
  /// -----


  modelFull->setTable("Isomers");
  modelFull->select();

  levelProxy = new LevelProxyModel(this);
  levelProxy->setSourceModel(modelFull);
  levelProxy->setT12Column(modelFull->fieldIndex("T12"));
  levelProxy->setLEVEL_IDColumn(modelFull->fieldIndex("LEVEL_ID"));
  levelProxy->setLEVELColumn(modelFull->fieldIndex("LEVEL"));

  // cacheLevel = new // cacheLevelProxy(this);
  // cacheLevel->setSourceModel(modelFull);
  // cacheLevel->setT12Column(modelFull->fieldIndex("T12"));
  // cacheLevel->setLEVEL_IDColumn(modelFull->fieldIndex("LEVEL_ID"));

  // cacheLevel->rebuild// cache();
  // // cacheLevel->setLEVELColumn(modelFull->fieldIndex("LEVEL"));

  gammaProxy = new GammaProxyModel(this);
  gammaProxy->setSourceModel(modelFull);
  gammaProxy->setGAMMAColumn(modelFull->fieldIndex("E_GAMMA"));

  ui->tableView_IsomerSolo->setModel(levelProxy);
  ui->tableView_Isomer->setModel(levelProxy);

  ui->tableView_GammaSolo->setModel(gammaProxy);
  ui->tableView_Gammas->setModel(gammaProxy);

  QStringList lvlColumns ={
          "A_IT", "Z_IT",
          "LEVEL","D_LEVEL","JPI",
          "T12","D_T12","IT_RATIO",
          "SOURCE", "LEVEL_ID"};

  for (int col = 0; col < levelProxy->columnCount(); ++col) {
      QString name = modelFull->headerData(col, Qt::Horizontal).toString();
      ui->tableView_IsomerSolo->setColumnHidden(col, !lvlColumns.contains(name));
      ui->tableView_Isomer->setColumnHidden(col, !lvlColumns.contains(name));

  }

  QStringList gamColumns = {
       "A_IT", "Z_IT",
       "LEVEL","D_LEVEL","JPI",
       "E_GAMMA","D_EG","I_GAMMA","D_IG", "M_GAMMA",
       "SOURCE", "GAMMA_ID"};

  for (int col = 0; col < gammaProxy->columnCount(); ++col) {
      QString name = modelFull->headerData(col, Qt::Horizontal).toString();
      ui->tableView_GammaSolo->setColumnHidden(col, !gamColumns.contains(name));
      ui->tableView_Gammas->setColumnHidden(col, !gamColumns.contains(name));
  }

  modelTuples.push_back(std::make_tuple(modelFull, ui->tableView_Dev));
  modelTuples.push_back(std::make_tuple(levelProxy, ui->tableView_Isomer));

  // modelTuples.push_back(std::make_tuple(// cacheLevel, ui->tableView_Isomer));

  modelTuples.push_back(std::make_tuple(levelProxy, ui->tableView_IsomerSolo));
  modelTuples.push_back(std::make_tuple(gammaProxy, ui->tableView_Gammas));
  modelTuples.push_back(std::make_tuple(gammaProxy, ui->tableView_GammaSolo));

  QMap<QString, QString> headerMap = {
      {"INDEX_IT", "\u03B3-ID"}, {"A_IT","A"}, {"Z_IT","Z"},
      {"E_GAMMA","E\u1D67 (keV)"}, {"D_EG","\u03B4E\u1D67 (keV)"},
      {"T12","T\u2081\u2082 (\u03BCs)"}, {"D_T12","\u03B4T\u2081\u2082 (\u03BCs)"},
      {"LEVEL","E\u02E1\u1D5B\u02E1 (keV)"}, {"D_LEVEL","\u03B4E\u02E1\u1D5B\u02E1 (keV)"},
      {"JPI","J\u03C0"}, {"IT_RATIO","I\u1D63"}, {"D_IT_RATIO","\u03B4I\u1D63"},
      {"I_GAMMA","I\u1D67"}, {"D_IG","\u03B4I\u1D67"},
      {"M_GAMMA","M\u1D67"}, {"M_RATIO","M_RATIO"}, {"D_MRATIO","D_MRATIO"},
      {"SOURCE","SOURCE"}, {"ROW","ROW"}, {"NAME","NAME"}
  };

  // subscript lvl (bad): \u2097\u1D65\u2097

  QMap<QString, QString> headerMapOFF = {
      {"INDEX_IT",   "γ-ID"},
      {"A_IT",       "A"},
      {"Z_IT",       "Z"},
      {"E_GAMMA",    "E<sub>γ</sub> (keV)"},
      {"D_EG",       "δE<sub>γ</sub> (keV)"},
      {"T12",        "T<sub>1/2</sub> (μs)"},
      {"D_T12",      "δT<sub>1/2</sub> (μs)"},
      {"LEVEL",      "E<sub>lvl</sub> (keV)"},
      {"D_LEVEL",    "δE<sub>lvl</sub> (keV)"},
      {"JPI",        "J<sup>π</sup>"},
      {"IT_RATIO",   "I<sub>r</sub>"},
      {"D_IT_RATIO", "δI<sub>r</sub>"},
      {"I_GAMMA",    "I<sub>γ</sub>"},
      {"D_IG",       "δI<sub>γ</sub>"},
      {"M_GAMMA",    "M<sub>γ</sub>"},
      {"M_RATIO",    "M_RATIO"},
      {"D_MRATIO",   "D_MRATIO"},
      {"SOURCE",     "SOURCE"},
      {"ROW",        "ROW"},
      {"NAME",       "NAME"}
  };

  // auto headerNames = {"\u03B3-ID", "A", "Z", "E\u1D67 (keV)", "dE\u1D67 (keV)",
  //                     "I\u1D1B", "dI\u1D1B", "T\u2081\u2082 (\u03BCs)","dT\u2081\u2082 (\u03BCs)",
  //                     "E(level) (keV)", "dE(level) (keV)", "J\u03C0",
  //                     "I\u1D67", "dI\u1D67", "M\u1D67"};

  /// Set up model views

  QFont headerFont = ui->tableView_Isomer->font();
  headerFont.setPointSize(14);

  for (auto &tuple : modelTuples) {
      auto [model, uiView] = tuple;
      // qDebug() << "[IsomerAPI model initialization] model, table, view" << model << tableName << uiView;

      uiView->setModel(model);
      uiView->horizontalHeader()->moveSection(0,20);
      uiView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

      // uiView->horizontalHeader()->setFont(headerFont);
      // uiView->horizontalHeader()->setStyleSheet(
      //     "QHeaderView::section {"
      //     "    padding-top: 2px;"
      //     "    padding-bottom: 4px;"
      //     "    min-height: 18px;"
      //     "    font-size: 14px; "
      //     "}"
      //     );

      // RichTextHeaderView *richHeader = new RichTextHeaderView(Qt::Horizontal, this);
      // uiView->setHorizontalHeader(richHeader);


      uiView->setSelectionMode(QAbstractItemView::ExtendedSelection);
      uiView->setSelectionBehavior(QAbstractItemView::SelectRows);

      uiView->setSortingEnabled(true);

      // int headerIndex = 0;
      for (int i = 0; i <= model->columnCount(); i++) {
          QString headerKey = model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
          // qDebug() << "[IsomerAPI header check]" << headerKey << headerMap.value(headerKey);
          if (headerMap.contains(headerKey)) {
              // qDebug() << "[IsomerAPI Header check: replace header triggered]";
              // qDebug() << "[IsomerAPI Header check: header values]" << headerMap.value(headerKey);
              model->setHeaderData(i, Qt::Horizontal, headerMap.value(headerKey));
              uiView->horizontalHeader()->viewport()->update();
          }

      };
      // for (QString headerKey : headerMap.keys()) {
      //     qDebug() << "[IsomerAPI header check]" << headerKey << headerMap.value(headerKey);
      //     model->setHeaderData(headerIndex, Qt::Horizontal, headerMap.value(headerKey));
      //     headerIndex++;
      // }

      connect(uiView->selectionModel(), &QItemSelectionModel::selectionChanged,
              this, [this, uiView](const QItemSelection &selected, const QItemSelection &deselected) {
                  onRowSelected(uiView);
                  // qDebug() << "[SELECTION MODEL: what is &selected]" << selected << "\n[FIN]";
              });
  }


  /// Column view formatting

  ui->tableView_Dev->hideColumn(modelFull->fieldIndex("M_RATIO"));
  ui->tableView_Dev->hideColumn(modelFull->fieldIndex("D_MRATIO"));
  ui->tableView_Dev->hideColumn(modelFull->fieldIndex("CONV"));
  ui->tableView_Dev->hideColumn(modelFull->fieldIndex("D_CONV"));
  ui->tableView_Dev->hideColumn(modelFull->fieldIndex("D_IT_RATIO"));


  ui->tableView_Isomer->horizontalHeader()->moveSection(9,4);
  ui->tableView_Isomer->horizontalHeader()->moveSection(9,4);

  ui->tableView_IsomerSolo->horizontalHeader()->moveSection(9,4);
  ui->tableView_IsomerSolo->horizontalHeader()->moveSection(9,4);

  /// Contained utility/attribute declaration
  query = QSqlQuery(dbIsomLevel);
  filterBounds = ui->gb_tableFilters->findChildren<QLineEdit*>();

  /// Source combo box config
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
  filteredIsotopes = prepData();
  statRefresh();

  /// Establish connections

  connect(ui->pb_applyFilters, &QPushButton::clicked, this, &IsomerAPI::applyFilters);
  connect(ui->pb_clearFilters, &QPushButton::clicked, this, &IsomerAPI::clearFilters);
  connect(ui->pb_levelScheme, &QPushButton::clicked, this, &IsomerAPI::openDrawing);

  connect(ui->pb_gammas_view, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});
  connect(ui->pb_isomers_view, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
  connect(ui->pb_isomers_gammas_view, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(2);});

  // connect(ui->tableView_Dev->selectionModel(), &QItemSelectionModel::selectionChanged,
  //         this, [this](const QItemSelection &selected, const QItemSelection &deselected) {
  //             onRowSelected();
  //             // qDebug() << "[SELECTION MODEL: what is &selected]" << selected << "\n[FIN]";
  //         });
  /// Shortcut intialization
  QShortcut *enterShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
  connect(enterShortcut, &QShortcut::activated, ui->pb_applyFilters, &QPushButton::click);

  QShortcut *escapeShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
  connect(escapeShortcut, &QShortcut::activated, this, [this](){
      int page = ui->stackedWidget->currentIndex();
      clearSelection(page);
  });

  QShortcut *dShortcut = new QShortcut(QKeySequence(Qt::Key_D), this);
  connect(dShortcut, &QShortcut::activated, this, &IsomerAPI::openDrawing);

  QShortcut *cShortcut = new QShortcut(QKeySequence(Qt::Key_C), this);
  connect(cShortcut, &QShortcut::activated, this, &IsomerAPI::clearFilters);


  /// Stacked widget setup
  ui->stackedWidget->setCurrentIndex(2); // currently set for DEV VIEW

  ui->pb_isomers_gammas_view->setChecked(true);

  connect(ui->actionIsomer_Emission_Split,&QAction::triggered,this,[this](){ui->stackedWidget->setCurrentIndex(2);});
  connect(ui->actionIsomers,&QAction::triggered,this,[this](){ui->stackedWidget->setCurrentIndex(1);});
  connect(ui->actionGammas,&QAction::triggered,this,[this](){ui->stackedWidget->setCurrentIndex(0);});
  connect(ui->actionDevelopment_View,&QAction::triggered,this,[this](){ui->stackedWidget->setCurrentIndex(3);});

  connect(ui->actionClear_Selection,&QAction::triggered,this,[this](){
      int page = ui->stackedWidget->currentIndex();
      clearSelection(page);
  });

  // qDebug();
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
  delete levelProxy;
  delete gammaProxy;

  modelFull = nullptr;
  levelProxy = nullptr;
  gammaProxy = nullptr;

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
                                                        tr("Save CSV File"), "untitled_isomer_table",
                                                        tr("CSV Files (*.csv);;Text Files (*.txt);;All Files (*)"));
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
void IsomerAPI::on_actionCalc_Transmission_triggered(){
    qDebug() << "[tmssngDlg TRIGGERED]";
    transmissionDlg tmssnDlg(this);

    if (tmssnDlg.exec() == QDialog::Accepted) {
        qDebug() << "[tmssngDlg ACCEPTED]";

        // std::tie(A,Z) = tmssnDlg.getOptions();
        QPair selIsoKey = tmssnDlg.getOptions();
        writeDecayTXT(selIsoKey);
    }

}

void IsomerAPI::writeDecayTXT(QPair<int, int> isoKey){
    qDebug() << "[writeDecayTXT for A,Z]" << isoKey;
    Isotope iso = filteredIsotopes.value(isoKey);
    int Z;
    int A;
    std::tie(Z,A) = isoKey;
    QString symbol = atomicSymbol(Z);
    QString AStr = QString::number(A);

    qDebug() << "[writeDecayTXT: symbol]" << symbol << Z;
// #include <QFile>
// #include <QTextStream>
// #include <QDebug>

    // ------------------------------------------


    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Text File"), AStr + symbol + "_decay_data",
                                                    tr("Text Files (*.txt);;All Files (*)"));
    // 2. Check if the user didn't cancel
    if (!fileName.isEmpty()) {
        QFile textFile(fileName);
        if (textFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            QTextStream out(&textFile);
            out << "Isotope: " + AStr + symbol << "\n";
            for (Level &lvl : iso.levels) {
                out << "\nLevel:  " << lvl.lvlEnergy << " dLevel: " << lvl.dlvlEnergy <<
                    "   T12(us): " << lvl.halfLife << " JPI: " << lvl.spin << " Level-ID: " <<
                    "   %IT: " << lvl.IT << lvl.lvlID << "\n";
                for (Transition &tr : lvl.transitions) {
                    out << "    Gamma: " << tr.gamEnergy << "   dGamma: " << tr.dgamEnergy <<
                        "   IGamma: " << tr.IGam << "   Gamma-ID: " << tr.trID << "\n";
                }
            }
            textFile.close();
        }
    }


    // ------------------------------------------

    // for (Level &lvl : iso.levels) {
    //     qDebug() << "[calcTransmision: investigate levelIDs]" << lvl.lvlID;


    // }



}


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
    double tempdGammaE = 0.0;

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
        int A = rowData.value(modelFull->fieldIndex("A_IT")).toInt();
        int Z = rowData.value(modelFull->fieldIndex("Z_IT")).toInt();
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
                    bool gamString;
                    tempdLevelE = lvl.dlvlEnergy.toDouble(&gamString);
                    if (!gamString) {
                        tempdLevelE = 0.0;
                    }
                    qDebug() << "   Associated gammas:" << tr.gamEnergy << "dGam"<< tempdGammaE << tr.trID;
                    qDebug() << "     proposed final:" << lvl.lvlEnergy - tempdGammaE;


                }
            }
        }
    }


    qDebug();

}



void IsomerAPI::statRefresh()
{
  qDebug();

  queryStr = "SELECT COUNT(DISTINCT LEVEL_ID) FROM Isomers WHERE T12 >= 0.01 AND LEVEL != 0";

  QVariant isomCount = queryModel(queryStr);

  queryStr = "SELECT MIN(E_GAMMA) FROM Isomers";
  QVariant minGamma = queryModel(queryStr);

  queryStr = "SELECT MAX(E_GAMMA) FROM Isomers";
  QVariant maxGamma = queryModel(queryStr);

  queryStr = "SELECT MIN(T12) FROM Isomers WHERE LEVEL != 0 AND T12 >= 0.01";
  QVariant minT12 = queryModel(queryStr);

  queryStr = "SELECT MAX(T12) FROM Isomers WHERE LEVEL != 0 AND T12 >= 0.01";
  QVariant maxT12 = queryModel(queryStr);


  ui->le_isomerCounts->setText(isomCount.toString());
  ui->le_isotopeCounts->setText(QString::number(filteredIsotopes.size()));

  ui->le_lowGammaSum->setText(minGamma.toString());
  ui->le_highGammaSum->setText(maxGamma.toString());

  ui->le_lowT12Sum->setText(QString::number(minT12.toFloat(), 'g', 4));
  ui->le_highT12Sum->setText(QString::number(maxT12.toFloat(), 'g', 4));

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QVariant IsomerAPI::queryModel(const QString &queryRequest)
{
  QString fullQuery = queryRequest;
  QString filter = modelFull->filter(); // ``` model full attempt
  // qDebug() << "[queryModel FILTER VALUE]" << filter;
  if (!filter.isEmpty()) {
      if (fullQuery.contains("WHERE", Qt::CaseInsensitive))
          fullQuery += " AND " + filter;
      else
          fullQuery += " WHERE " + filter;
      // qDebug() << "[queryModel: TRIGGERED empty query]";
    }
  if (query.exec(fullQuery) && query.next()) {
      // qDebug() << "[queryModel: exec, fullQuery value]" << fullQuery;
      // qDebug() << "[queryModel -- query value]" << query.value(0);
      return {query.value(0)};
  } else {
      qDebug() << "[queryModel: NO EXECUTION]" << query.lastError().text();
      qDebug() << "[queryModel: BROKEN REQUEST]" << fullQuery << "\n";
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

  if (reqSources.contains("All Sources")) {
      modelFull -> setFilter("");
      qDebug() << "[sourceFilter: All sources triggered - clear filters]";
  } else if (!validSearch) {
      QMessageBox::critical(this,"Error!","Check the source entry is a possible source!");
      qDebug() << "[sourceFilter: INVALID SEARCH]" << reqSources;
  } else {
      QStringList quoted;
      for (const QString &src : reqSources) {
          quoted.append("'" + src + "'");

      }
      modelFull->setFilter(QString("SOURCE IN (%1)").arg(quoted.join(',')));
      qDebug() << "[sourceFilter l77: NO ALL SOURCES]: " << quoted;
      qDebug() << "[sourceFilter l78: Check format for SQL]: " << quoted.join(',');
  }

  /// DEPRECATED WITH PROXY MODEL METHOD
  // for (auto &model : modelsVector) {

  //     if (reqSources.contains("All Sources")) {
  //         model -> setFilter("");
  //         qDebug() << "[sourceFilter: All sources triggered - clear filters]";
  //     } else if (!validSearch) {
  //         QMessageBox::critical(this,"Error!","Check the source entry is a possible source!");
  //         qDebug() << "[sourceFilter: INVALID SEARCH]" << reqSources;
  //     } else {
  //         QStringList quoted;
  //         for (const QString &src : reqSources) {
  //             quoted.append("'" + src + "'");

  //         }
  //         model->setFilter(QString("SOURCE IN (%1)").arg(quoted.join(',')));
  //         qDebug() << "[sourceFilter l77: NO ALL SOURCES]: " << quoted;
  //         qDebug() << "[sourceFilter l78: Check format for SQL]: " << quoted.join(',');
  //     }

  // }
  qDebug() << "\n";

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::applyFilters()
{
    // cacheLevel->rebuild// cache();
    // bool rowSelected = ui->tableView_Dev->selectionModel()->hasSelection();
    // qDebug() << "[applyFilters: OLD FILTER VALUE?]" << modelFull->filter();
    // if (rowSelected){
    //   qDebug() << "[applyFilters: SELECTION DETECTED]" << rowSelected;
    // } else {qDebug() << "[applyFilters: SELECTION SKIPPED]" << rowSelected;}

  sourceFilter();

  // qDebug() << "[sourceFILTER PATH CHECK]" << QDir::current() << QDir::currentPath();
  // qDebug() << "[applyFilters: OLD FILTER VALUE?]" << modelFull->filter();

  QMap<QString, QString> filterMap = {
    {"le_T12", "T12"},
    {"le_GE", "E_GAMMA"},
    {"le_FINE", "LEVEL"},
    {"le_numA", "A_IT"},
    {"le_numZ", "Z_IT"}
  };

  QString ZFilter;
  QString AFilter;

  QString filterExpr = modelFull->filter(); // ~~~ treat modelFull first -- cut on T12, Egam later
  QStringList baseNameExceptions = {"le_GE", "le_FINE", "le_T12"};

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
          QString textValue = le->text();
          QString finalValue;
          qDebug() << "[applyFilters: check col assignment]" << col;
          if (baseName != "le_numZ") {
              finalValue = textValue;

          }

          else if (baseName == "le_numZ") {
              bool isInt;
              textValue.toInt(&isInt);
              // qDebug() << "[applyFilters: le_num case, check isInt, testValue, symbol]" <<  isInt << textValue;

              if (isInt) {
                  // It's already a number (e.g., "6")
                  finalValue = textValue;
                  // qDebug() << "[applyFilters: le_num case, isInt==True check symbol]" << atomicSymbol(textValue);
              } else {
                  finalValue = QString::number(atomicSymbol(textValue));
                  qDebug() << "[applyFilters: le_num string entered, "
                              "check atomicSymobls output]" << atomicSymbol(textValue);
              }
              ZFilter = finalValue;
              qDebug() << "[applyFilters: le_numZ case, check finalValue]" << finalValue;

          }

          /// Construct condition
          QString condition;
          if (suffix != "0") {
              condition = (suffix == "1") ? QString("%1 >= %2").arg(col,finalValue)
                                          : QString("%1 <= %2").arg(col,finalValue);
              if (baseNameExceptions.contains(baseName)) {
                  condition = "(" + condition + " OR (E_GAMMA IS NULL))";
              }
          } else if (suffix == "0") {
              condition = QString("%1 IS %2").arg(col, finalValue);
          }



          if (!filterExpr.isEmpty()) {
              filterExpr += " AND ";
          }
          filterExpr += condition;
          // qDebug() << "[applyFilters: check ]"

          // qDebug() << "[applyFilters l139: col check]" << col;
          // qDebug() << "[applyFilters l140: value check]" << finalValue;
          qDebug() << "[applyFilters l141: conditional check]" << condition;

          qDebug() << "[applyFilters: check filterexpr]" << filterExpr;
        }
      qDebug();
    }

  // filterExpr = "(" + filterExpr + ") OR (E_GAMMA IS NULL)";
  modelFull->setFilter(filterExpr);
  modelFull->select();
  ui->tableView_Dev->setModel(modelFull);
  // qDebug() << "[applyFilters: Check filterExpr]:" << filterExpr << model->filter();

  filteredIsotopes = prepData();
  qDebug() << "[applyFilters: isotope count]" << filteredIsotopes.count() << filteredIsotopes.size();

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
    currentPage = ui->stackedWidget->currentIndex();

    bool rowSelected = checkSelection(currentPage);
    int drawSelection = 3;
    if (rowSelected){
        qDebug() << "[openDrawing: SELECTION DETECTED]" << rowSelected;
        drawingChoiceDlg drawDlg(this);
        if (drawDlg.exec() == QDialog::Accepted) {
            drawSelection = drawDlg.getDrawChoice();
            qDebug() << "[openDrawing: DIALOG ACCEPT] code"<< drawSelection;
        }

        if (drawSelection == 1) {
            auto *levelScheme = new LevelScheme(filteredIsotopes);
            levelScheme->show();
        } else if (drawSelection == 2) {
            qDebug() << "[openDrawing: select 1]";
        } else if (drawSelection == 3) {
            qDebug() << "[openDrawing: select 2]";
        }

    } else {
        auto *levelScheme = new LevelScheme(filteredIsotopes);
        levelScheme->show();
    }

  // auto *levelScheme = new LevelScheme(filteredIsotopes);
  // levelScheme->show();
  // levelScheme->activateWindow();
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QMap<QPair<int,int>,Isotope> IsomerAPI::prepData()
{

  // qDebug() << "[prepData: BEGIN PREP]";
  QString fullQuery =
        "SELECT A_IT,Z_IT,E_GAMMA,D_EG,T12,D_T12,LEVEL,D_LEVEL,JPI,IT_RATIO,I_GAMMA,LEVEL_ID,GAMMA_ID FROM Isomers";

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
      QString tmpdLevelE = query.value("D_LEVEL").toString();

      double tmpGammaE = query.value("E_GAMMA").toDouble();
      QString tmpdGammaE = query.value("D_EG").toString();


      // double tmpFinal = tmpLevelE - tmpGammaE;
      // QString tmpEmission = QString("%1").arg(tmpGammaE);


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
          if (tmpLevelE != 0.0) {
              Level newLevel;
              newLevel.lvlEnergy = tmpLevelE;
              newLevel.dlvlEnergy = query.value("D_LEVEL").toString();
              newLevel.spin = query.value("JPI").toString();
              newLevel.halfLife = query.value("T12").toDouble();
              newLevel.lvlID = query.value("LEVEL_ID").toInt();

              newLevel.IT = query.value("IT_RATIO").toInt();

              // qDebug() << "[prepData: check level skipping]";

              iso.levels.append(newLevel);
              levelPtr = &iso.levels.last();
          } else if (tmpLevelE == 0) {
              Level groundState;
              groundState.lvlEnergy = tmpLevelE;
              groundState.dlvlEnergy = query.value("D_LEVEL").toString();
              groundState.spin = query.value("JPI").toString();
              groundState.halfLife = query.value("T12").toDouble();
              groundState.lvlID = query.value("LEVEL_ID").toInt();

              groundState.IT = query.value("IT_RATIO").toDouble();


              iso.groundState = groundState;

              levelPtr = &iso.groundState;

          }

      }


      // ~~~~~ add transitions
      Transition tr;

      tr.lvlEnergy = tmpLevelE;
      tr.dlvlEnergy = tmpdLevelE;
      tr.gamEnergy = tmpGammaE;
      tr.dgamEnergy = tmpdGammaE;
      tr.label = query.value("E_GAMMA").toString();
      tr.trID = query.value("GAMMA_ID").toInt();

      tr.IGam = query.value("I_GAMMA").toDouble();

      // ~~~~~ point to current level
      levelPtr -> transitions.append(tr);
      // qDebug() << "[prepData: isotope check]" << query.value("A_IT") << query.value("Z_IT");
    }

    qDebug() << "[prepData: check isotope count]" << isotopeMap.count();

    // for (Isotope &storedIso : isotopeMap) {
    //     qDebug() << "[prepData: check isotopes key]" << storedIso.A << storedIso.Z;
    //     qDebug() << "[prepData: check if isotope empty levels]" << storedIso.levels.isEmpty();
    //     qDebug();
    // }
    /// Clean entries with only ground level
    for (auto storedIso = isotopeMap.begin(); storedIso != isotopeMap.end(); )
    {
        if (storedIso->levels.isEmpty()) {
            storedIso = isotopeMap.erase(storedIso);
            qDebug() << "[prepData: isotope is empty]" << storedIso.key() << atomicSymbol(storedIso.key().first);
            qDebug() << "   gs:" << storedIso->groundState.lvlID;

        } else {
            ++storedIso;
        }
    }

    qDebug() << "[prepData: check isotope count]" << isotopeMap.count();

    return isotopeMap;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::clearSelection(int page){
    if (page == 0) {
        ui->tableView_GammaSolo->selectionModel()->clearSelection();
    } else if (page == 1) {
        ui->tableView_IsomerSolo->selectionModel()->clearSelection();
    } else if (page == 2) {
        ui->tableView_Isomer->selectionModel()->clearSelection();
        ui->tableView_Gammas->selectionModel()->clearSelection();
    } else if (page == 3) {
        ui->tableView_Dev->selectionModel()->clearSelection();
    }
}

bool IsomerAPI::checkSelection(int page){
    if (page == 0) {
        return ui->tableView_GammaSolo->selectionModel()->hasSelection();

    } else if (page == 1) {
        return ui->tableView_IsomerSolo->selectionModel()->hasSelection();
    } else if (page == 2) {
        return (ui->tableView_Isomer->selectionModel()->hasSelection() or
                ui->tableView_Gammas->selectionModel()->hasSelection());
    } else if (page == 3) {
        return(ui->tableView_Dev->selectionModel()->hasSelection());
    }
}

void IsomerAPI::on_actionExit_triggered()
{
  exit(2);
}
