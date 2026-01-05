#ifndef PAINTGRAPHICSVIEW_H
#define PAINTGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QVector>
#include <QString>


#include "L_vectorStruct.h"

//------------------------------------------------------

class graphicsView : public QGraphicsItem
{
public:
    graphicsView(const Isotope& iso,
                 QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;  // required
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    Isotope L_isotope;

    int trCount;
    // QVector<Level> L_Levels;
    // QVector<Transition> L_Transitions;

    double maxEnergy;
    double scale;
    int drawHeight;

};

#endif // PAINTGRAPHICSVIEW_H
