#ifndef LEVELSCHEMEWINDOW_H
#define LEVELSCHEMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <QHash>
#include <QGraphicsScene>
#include <QMap>
#include <QToolBar>


#include "w_schemeGraphic.h"
#include "L_isoStructs.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class LevelScheme;
}
QT_END_NAMESPACE

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

class LevelScheme : public QMainWindow
{
    Q_OBJECT

public:

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///isotopeMap method deprecated by schemeMap methods
    // LevelScheme(const QMap<QPair<int,int>,Isotope>& isotopeMap,
    //             QWidget *parent=nullptr);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    LevelScheme(const SchemeMap& schemeMap,
                QWidget *parent=nullptr);
    ~LevelScheme();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///isotopeMap method deprecated by schemeMap methods
    // QHash<QPair<int,int>, QGraphicsItem*> graphicStore;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    QMap<SchemeKey, QGraphicsItem*> graphicStore;


    void makeActions();
    void openNNDC(QString A_Sym, QString choice);

private:


    QString _filterQuery;
    QString _path;
    Ui::LevelScheme *ui;
    QToolBar *toolbar;

    QGraphicsItem *currentItem = nullptr;
    QGraphicsScene *scene = new QGraphicsScene(this);


    QAction *act_openNNDC_LVLS, *act_openNNDC_SCHEME, *act_openNNDC_betaSCHEME, *act_saveImage;

    void saveImage();
    // void paintEvent(QPaintEvent *event) override;
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
#endif // LEVELSCHEMEWINDOW_H
