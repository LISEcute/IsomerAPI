#ifndef LEVELSCHEMEWINDOW_H
#define LEVELSCHEMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <QHash>


#include "w_graphicsView.h"
#include "L_vectorStruct.h"


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

    LevelScheme(const QHash<QPair<int,int>,Isotope>& isotopeMap,
                QWidget *parent=nullptr);

    ~LevelScheme();

private:

    QVector<Level> m_levels;
    QVector<Transition> m_transitions;

    QString _filterQuery;
    QString _path;
    Ui::LevelScheme *ui;

    void saveImage();
    // void paintEvent(QPaintEvent *event) override;
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
#endif // LEVELSCHEMEWINDOW_H
