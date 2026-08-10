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

    LevelScheme(const QMap<QPair<int,int>,Isotope>& isotopeMap,
                QWidget *parent=nullptr);
    ~LevelScheme();

    QHash<QPair<int,int>, QGraphicsItem*> graphicStore;

    void makeActions();
    void openNNDC(QString A_Sym);

private:


    QString _filterQuery;
    QString _path;
    Ui::LevelScheme *ui;
    QToolBar *toolbar;

    QGraphicsItem *currentItem = nullptr;
    QGraphicsScene *scene = new QGraphicsScene(this);


    QAction *act_openNNDC, *act_saveImage;

    // QHash<QPair<int,int>, QGraphicsItem*> graphicStore;


    void saveImage();
    // void paintEvent(QPaintEvent *event) override;
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
#endif // LEVELSCHEMEWINDOW_H
