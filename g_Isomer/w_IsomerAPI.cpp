#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "d_DownloadFiles.h"
#include "d_ColumnsOptions.h"
#include "L_levelProxyModel.h"

#include "w_aboutIsomerAPI.h"
#include "L_isomerAPI_version.h"
#include "L_IsomerElement.h"
#include "L_gammaProxyModel.h"
// #include "L_richTextHeader.h"

#include <QSqlError>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QShortcut>
#include <QTextStream>

// #include "L_Init/declare_IsomerAPI.h"
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
      {"E_GAMMA","E\u1D67 (keV)"}, {"D_EG","\u03B4E\u1D67"},
      {"T12","T\u2081\u2082 (\u03BCs)"}, {"D_T12","\u03B4T\u2081\u2082"},
      {"LEVEL","E\u2097\u1D65\u2097 (keV)"}, {"D_LEVEL","\u03B4E\u2097\u1D65\u2097"},
      {"JPI","J\u03C0"}, {"IT_RATIO","I\u1D63"}, {"D_IT_RATIO","\u03B4I\u1D63"},
      {"I_GAMMA","I\u1D67"}, {"D_IG","\u03B4I\u1D67"},
      {"M_GAMMA","M\u1D67"}, {"M_RATIO","M_RATIO"}, {"D_MRATIO","D_MRATIO"},
      {"GAMMA_ID", "\u03B3-ID"}, {"LEVEL_ID", "Lvl-ID"},
      {"SOURCE","source"}, {"ROW","ROW"}, {"NAME","NAME"}
  };

  QMap<QString, QString> headerMapOFF = {
      {"INDEX_IT",   "γ-ID"},
      {"A_IT",       "A"},
      {"Z_IT",       "Z"},
      {"E_GAMMA",    "E<sub>γ</sub> (keV)"},
      {"D_EG",       "δE<sub>γ</sub> (keV)"},
      {"T12",        "T<sub>1/2</sub> (μs)"},
      {"D_T12",      "δT<sub>1/2</sub> (μs)"},
      {"LEVEL",      "E<sub>level</sub> (keV)"},
      {"D_LEVEL",    "δE<sub>level</sub> (keV)"},
      {"JPI",        "J<sup>π</sup>"},
      {"IT_RATIO",   "I<sub>r</sub>"},
      {"D_IT_RATIO", "δI<sub>r</sub>"},
      {"I_GAMMA",    "I<sub>γ</sub>"},
      {"D_IG",       "δI<sub>γ</sub>"},
      {"M_GAMMA",    "M<sub>γ</sub>"},
      {"M_RATIO",    "M_RATIO"},
      {"D_MRATIO",   "D_MRATIO"},
      {"SOURCE",     "source"},
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
      uiView->verticalHeader()->setVisible(false);

      uiView->horizontalHeader()->setFont(headerFont);
      uiView->horizontalHeader()->setStyleSheet(
          "QHeaderView::section {"
          "    padding-top: 2px;"
          "    padding-bottom: 4px;"
          "    min-height: 18px;"
          "    font-size: 14px; "
          "}"
          );

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
                  Q_UNUSED(selected);
                  Q_UNUSED(deselected);
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
  setDefaultFilters();

  applyFilters();

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
  ui->stackedWidget->setCurrentIndex(1);

  ui->pb_isomers_view->setChecked(true);
  ui->pb_gammas_view->setChecked(false);
  ui->pb_isomers_gammas_view->setChecked(false);

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
void IsomerAPI::on_actionExit_triggered()
{
  exit(2);
}
