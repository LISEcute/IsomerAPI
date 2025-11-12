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
    graphicsView(const QVector<Level>& levels, const QVector<Transition>& transitions,QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;  // required
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    QVector<Level> L_Levels;
    QVector<Transition> L_Transitions;
};

#endif // PAINTGRAPHICSVIEW_H

