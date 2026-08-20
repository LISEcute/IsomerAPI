#include "w_schemeWindow.h"
#include "ui_w_schemeWindow.h"
#include "L_isoStructs.h"
#include "L_IsomerElement.h"


#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsScene>
#include <QHash>
#include <QShortcut>
#include <QDesktopServices>
#include <QToolButton>

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///isotopeMap method deprecated by schemeMap methods
// LevelScheme::LevelScheme(const QMap<QPair<int,int>,Isotope>& isotopeMap,
//                          QWidget *parent)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LevelScheme::LevelScheme(const SchemeMap& schemeMap,
                         QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::LevelScheme)

{
    ui->setupUi(this);
    setMinimumSize(500, 600);
    resize(800,800);
    qDebug() << _filterQuery << _path;

    ui->graphicsView->setScene(scene);

    makeActions();

    ui->menuNNDC_Records->addAction(act_openNNDC_LVLS);
    ui->menuNNDC_Records->addAction(act_openNNDC_SCHEME);
    ui->menuNNDC_Records->addAction(act_openNNDC_betaSCHEME);




    QShortcut *escapeShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escapeShortcut, &QShortcut::activated, this, &QWidget::close);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///isotopeMap method deprecated by schemeMap methods
    // QPair<int,int> firstIso;
    // bool firstIt = true;
    // for (const Isotope &iso : isotopeMap) {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    SchemeKey firstKey;
    bool hasFirstScheme = false;

    for (auto it = schemeMap.cbegin(); it != schemeMap.cend(); ++it) {
        const SchemeKey &schemeKey = it.key();
        const Isotope &schemeIsotope = it.value();

        auto *item = new graphicsView(schemeIsotope);
        graphicStore.insert(schemeKey, item);

        QString label;
        QString isotopeName = QString("%1%2")
                                  .arg(schemeKey.A)
                                  .arg(atomicSymbol(schemeKey.Z));

        if (schemeKey.type == SchemeType::FilteredIsotope) {
            label = isotopeName;
        } else if (schemeKey.type == SchemeType::DecayFromLevel) {
            double rootEnergy = 0.0;

            for (const Level &level : schemeIsotope.levels) {
                if (level.lvlID == schemeKey.anchorId) {
                    rootEnergy = level.lvlEnergy;
                    break;
                }
            }

            label = QString("%1 - %2 keV Level")
                            .arg(isotopeName)
                            .arg(rootEnergy, 0, 'g', 10);
        } else if (schemeKey.type == SchemeType::GammaCoincidence) {
            double gammaEnergy = 0.0;

            for (const Level &level : schemeIsotope.levels) {
                for (const Transition &transition : level.transitions) {
                    if (transition.trID == schemeKey.anchorId) {
                        gammaEnergy = transition.gamEnergy;
                        break;
                    }
                }
                if (gammaEnergy != 0.0) {
                    break;
                }
            }

            label = QString("%1 - %2 keV Coincidence")
                        .arg(isotopeName)
                        .arg(gammaEnergy, 0, 'g', 10);
        }

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ///isotopeMap method deprecated by schemeMap methods
        // if (firstIt){
        //     firstIso = schemeKey;
        //     QString firstIsoName = QString("%1%2")
        //                        .arg(iso.A).arg(atomicSymbol(iso.Z));
        //     this->setWindowTitle("Level Scheme - " + firstIsoName);
        //     firstIt = false;
        // }

        // for (const Level &lvl : iso.levels) {
        //     if (lvl.lvlEnergy <= 400 && lvl.lvlEnergy > 600) {

        //     }
        // }

        // QAction *act_isotopeSelect = new QAction(QString("%1%2")
        //                                              .arg(iso.A).arg(atomicSymbol(iso.Z)),this);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        QAction *act_isotopeSelect = new QAction(label, this);


        ui->menu_other_isotopes->addAction(act_isotopeSelect);


        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ///isotopeMap method deprecated by schemeMap methods
        // connect(act_isotopeSelect, &QAction::triggered,
        //         this, [this, act_isotopeSelect, gphcKey]() {
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        connect (act_isotopeSelect, &QAction::triggered, this, [this, schemeKey, act_isotopeSelect, label](){
            for (QAction *act : ui->menu_other_isotopes->actions()) {

                QFont f = act->font();
                f.setBold(false);
                act->setFont(f);

                QString txt = act->text();
                if (txt.startsWith("> ")) {
                    act->setText(txt.mid(2));
                }
            }

            if (currentItem) {
                scene->removeItem(currentItem);
            }
            currentItem = graphicStore.value(schemeKey, nullptr);

            if (currentItem) {
                scene->addItem(currentItem);
            }

            QFont f = act_isotopeSelect->font();
            f.setBold(true);
            act_isotopeSelect->setFont(f);
            act_isotopeSelect->setText("> " + label);
            setWindowTitle("Level Scheme - " + label);

            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            ///isotopeMap method deprecated by schemeMap methods
            // QString titleTxt = act_isotopeSelect->text();
            // this->setWindowTitle("Level Scheme - " + titleTxt);
            // f.setBold(true);
            // act_isotopeSelect->setFont(f);
            // act_isotopeSelect->setText("> " + titleTxt);
            // if (currentItem)
            //     scene->removeItem(currentItem);

            // currentItem = graphicStore.value(gphcKey, nullptr);

            // if (currentItem)
            //     scene->addItem(currentItem);
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        });

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ///isotopeMap method deprecated by schemeMap methods
        // if (gphcKey == firstIso) {
        //     QFont fFirst = act_isotopeSelect->font();
        //     fFirst.setBold(true);
        //     act_isotopeSelect->setFont(fFirst);
        //     act_isotopeSelect->setText("> " + act_isotopeSelect->text());
        // }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        if (!hasFirstScheme) {
            firstKey = schemeKey;
            hasFirstScheme = true;
        }

    }

    if (hasFirstScheme) {
        currentItem = graphicStore.value(firstKey, nullptr);

        if (currentItem) {
            scene->addItem(currentItem);
        }

        QAction *firstAction = ui->menu_other_isotopes->actions().first();
        QString firstLabel = firstAction->text();
        setWindowTitle("Level Scheme - " + firstLabel);

        QFont font = firstAction->font();
        font.setBold(true);
        firstAction->setFont(font);
        firstAction->setText("> " + firstLabel);
    }

    /*QGraphicsScene *scene = new QGraphicsScene(this);
    auto *item = new graphicsView(levels, transitions);
    scene->addItem(item);
    ui->graphicsView->setScene(scene);

    // display policies
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QAction *action_savePic2 = new QAction("TEST SAVE", this);
    ui->toolBar->addAction(action_savePic2);
    connect(ui->action_savePic, &QAction::triggered,this,&LevelScheme::saveImage);
*/
}

void LevelScheme::saveImage()
{
    qDebug() << "[saveImage: triggered]";
    QPixmap pixMap = ui->graphicsView->viewport()->grab(ui->graphicsView->sceneRect().toRect());
    pixMap.save("lvlSchemeTest.png");

    // QRectF sceneRect(ui->graphicsView->scene()->sceneRect());
    // QImage image(sceneRect.size().toSize(), QImage::Format_ARGB32);
    // image.fill(Qt::white);
    // QPainter painter(&image);
    // painter.setRenderHint(QPainter::Antialiasing);
    // QGraphicsScene currScene = ui->graphicsView->scene();
    // currScene.render(&painter);
    // image.save("lvlSchemeTest.png");
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void LevelScheme::makeActions(){
    // CmPrintWholeAction = new QAction(tr("CmPrintWholeAction"),this);
    // toolbar->addAction(CmPrintWholeAction);
    // connect(CmPrintWholeAction, SIGNAL(triggered()),this, SLOT(CmPrintWhole()));
    // CmPrintWholeAction->setIcon(QIcon(":/plottool/print10.gif"));
    // CmPrintWholeAction->setToolTip("Print whole page, portrait");

    act_openNNDC_LVLS = new QAction(tr("act_openNNDC_LVLS"),this);
    // toolbar->addAction(act_openNNDC_LVLS);
    connect(act_openNNDC_LVLS, &QAction::triggered,this,[this](){
        QStringList sepTitle = this->windowTitle().split(" ");
        QString isoName = sepTitle.last();
        openNNDC(isoName, "LVLS");
    });
    act_openNNDC_LVLS->setText("Open NNDC Records");
    act_openNNDC_LVLS->setToolTip("Open NNDC Data for Current Isotope");

    act_openNNDC_SCHEME = new QAction(tr("act_openNNDC_SCHEME"),this);
    // toolbar->addAction(act_openNNDC_LVLS);
    connect(act_openNNDC_SCHEME, &QAction::triggered,this,[this](){
        QStringList sepTitle = this->windowTitle().split(" ");
        QString isoName = sepTitle.last();
        openNNDC(isoName, "SCHEME");
    });
    act_openNNDC_SCHEME->setText("Open NNDC Scheme");
    act_openNNDC_SCHEME->setToolTip("Open NNDC Scheme for Current Isotope");


    act_openNNDC_betaSCHEME = new QAction(tr("act_openNNDC_betaSCHEME"),this);
    // toolbar->addAction(act_openNNDC_LVLS);
    connect(act_openNNDC_betaSCHEME, &QAction::triggered,this,[this](){
        QStringList sepTitle = this->windowTitle().split(" ");
        QString isoName = sepTitle.last();
        openNNDC(isoName, "betaSCHEME");
    });
    act_openNNDC_betaSCHEME->setText("Open NNDC Scheme (beta)");
    act_openNNDC_betaSCHEME->setToolTip("Open NNDC Scheme (beta) for Current Isotope");




}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void LevelScheme::openNNDC(QString A_Sym, QString choice){
    qDebug() << "[openNNDC: opening for]" << A_Sym;
    QString ss;
    if (choice == "LVLS") {ss = "https://www.nndc.bnl.gov/nudat3/getdataset.jsp?nucleus=" + A_Sym;}
    else if (choice == "SCHEME") {ss = "https://www.nndc.bnl.gov/nudat3/NuDatBandPlotServlet?nucleus=" + A_Sym + "&unc=NDS";}
    else if (choice == "betaSCHEME") {ss = "https://www.nndc.bnl.gov/nudat3/levelscheme/?nucleus=" + A_Sym;}
    QDesktopServices::openUrl(QUrl(ss));
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

LevelScheme::~LevelScheme()
{
    delete ui;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww


// here lays the old static painter
// void LevelScheme::paintEvent(QPaintEvent *)
// {
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     struct Level {
//         double energy;
//         QString spin;
//         QString halfLife;
//     };

//     QVector<Level> levels = {
//         {0,   "0+", "Stable"},
//         {100, "2+", "5 ns"},
//         {250, "4+", "1 µs"},
//         {500, "6+", "20 µs"}
//     };

//     int left = 150;
//     int right = 300;
//     int spinOffset = 90;
//     int infoOffset = 310;
//     int textVOffset = 5;
//     int arrowHeadSize = 6;
//     // QColor textColor(196, 196, 196);
//     // QColor lineColor(200, 200, 200);
//     QColor lineColor(0,0,0);
//     QColor textColor(0,0,0);
//     QColor arrowColor(34, 139, 34);


//     double yBase = height() - 50;

//     for (const Level &lvl : levels) {
//         int y = static_cast<int>(yBase - lvl.energy);
//         painter.setPen(QPen(lineColor, 2));
//         painter.drawLine(left, y, right, y);
//         painter.setPen(textColor);
//         painter.drawText(spinOffset, y + textVOffset, lvl.spin);
//         QString text = QString("%1 keV, t½ = %2")
//                            .arg(lvl.energy, 0, 'f', 0)
//                            .arg(lvl.halfLife);
//         painter.drawText(infoOffset, y + textVOffset, text);
//     }

//     struct Transition {
//         int fromIdx;
//         int toIdx;
//         QString label;
//         int xOffset;
//     };

//     QVector<Transition> transitions = {
//         {3, 2, "250 keV", 0},
//         {2, 1, "150 keV", -20},
//         {1, 0, "100 keV", 20},
//         {3, 1, "400 keV", 40}
//     };

//     painter.setPen(QPen(arrowColor, 2));
//     painter.setBrush(arrowColor);

//     for (const Transition &tr : transitions) {
//         int y1 = static_cast<int>(yBase - levels[tr.fromIdx].energy);
//         int y2 = static_cast<int>(yBase - levels[tr.toIdx].energy);
//         int x = (left + right) / 2 + tr.xOffset;

//         painter.drawLine(x, y1, x, y2);

//         QPolygon arrowHead;
//         arrowHead << QPoint(x - arrowHeadSize, y2 - arrowHeadSize)
//                   << QPoint(x + arrowHeadSize, y2 - arrowHeadSize)
//                   << QPoint(x, y2);
//         painter.drawPolygon(arrowHead);

//         painter.setPen(textColor);
//         painter.drawText(x + 8, (y1 + y2) / 2, tr.label);

//         painter.setPen(QPen(arrowColor, 2));
//     }
// }
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
