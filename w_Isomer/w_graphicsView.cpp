#include "w_graphicsView.h"
//#include "vectorstructures.h"

#include <QPainter>
#include <QPen>
#include <QPolygon>

#include <sstream>
#include <iomanip>
#include <string>


//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

graphicsView::graphicsView(const QVector<Level>& levels,
                           const QVector<Transition>& transitions,
                           QGraphicsItem *parent)
    :
    QGraphicsItem(parent),
    L_Levels(levels),
    L_Transitions(transitions)
{
    maxEnergy = 0;

    for (const Level& lvl : L_Levels) {
        maxEnergy = std::max(maxEnergy, lvl.lvlEnergy);
    }
    scale = 1.;

    drawHeight = 600;
    scale = drawHeight/maxEnergy;

    qDebug() << "[CONSTRUCT] drawheight, maxEnergy" << drawHeight << maxEnergy << drawHeight/maxEnergy;
    // if (maxEnergy > drawHeight) {
    //     scale = drawHeight/maxEnergy;
    // } else scale = 1.;

}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void graphicsView::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *,
                              QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    extern QRect OutTextOleg(QPainter *painter, int x, int y, const char *s, int loc, int clip=0,
                             const QRectF* PlotRect=nullptr);


    int trHOffset = 20;

    int lineLeft = 0;
    int trCount = L_Transitions.size();
    qDebug() << "[graphicsView: transition count]: "<< trCount;
    int lineRight = trCount*trHOffset + 25;
    qDebug() << "[graphicsView: line left/right]" << lineLeft << lineRight;
    int indentation = 25;




    int titleOffset = 20;
    int spinOffset = -40;
    int infoHOffset = 10;
    int textVOffset = -5;
    int arrowHeadSize = 6;

    QColor lineColor(0,0,0);
    QColor levelTextColor(0,0,0);
    QColor transitionColor(34, 139, 34);

    double yBase = drawHeight;

    for (const Level &lvl : L_Levels)
      {
        int y = static_cast<int>(yBase - lvl.lvlEnergy*scale);
        painter->setPen(QPen(lineColor, 2));
        painter->drawLine(lineLeft, y, lineRight, y);
        painter->setPen(levelTextColor);
        painter->drawText(spinOffset, y + textVOffset, lvl.spin);
        QString text = QString("%1 keV    %2 us")
                           .arg(lvl.lvlEnergy, 0, 'f', 0)
                           .arg(lvl.halfLife);

        painter->drawText(lineRight + infoHOffset, y + textVOffset, text);

        // ~~~~ ATTEMPT AT OUTOLEGTEXT STR FOR SUB
        // std::ostringstream oss;
        // oss << std::fixed << std::setprecision(0)
        //     << lvl.lvlEnergy << " keV, T~1/2~ = "
        //     << lvl.halfLife.toStdString() << u8" \u03BCs";
        // std::string text = std::ostringstream("{:.0f} keV, T~1/2~ = {} \u03BCs",
        //                        lvl.lvlEnergy,
        //                        lvl.halfLife);
        // std::string text = oss.str();
        // qDebug() << "[CHECK OUTOLEG]" << text;
        // OutTextOleg(painter, lineRight + infoHOffset, y + textVOffset, text.toUtf8().constData(), 0);
        // qDebug() << text.toUtf8().constData();

    }
    // OutTextOleg(painter, 0,0,"This is a $test, up $1 and down ~1",1);
    //  draw title
    painter->drawText((lineLeft+lineRight)/2,yBase + titleOffset,QString("##El"));

    painter->setPen(QPen(transitionColor, 2));
    painter->setBrush(transitionColor);

    int xOffset = 0;
    for (const Transition &tr : L_Transitions)
      {
        int y1 = static_cast<int>(yBase - tr.level*scale);
        int y2 = static_cast<int>(yBase - tr.emission*scale);

        int x = lineLeft + indentation + xOffset;

        painter->drawLine(x, y1, x, y2);

        QPolygon arrowHead;
        arrowHead << QPoint(x - arrowHeadSize, y2 - arrowHeadSize)
                  << QPoint(x + arrowHeadSize, y2 - arrowHeadSize)
                  << QPoint(x, y2);
        painter->drawPolygon(arrowHead);

        painter->setPen(transitionColor);

        painter->drawText(x + 8, (y1 + y2) / 2, tr.label);
        painter->setPen(QPen(transitionColor, 2));

        xOffset += 20;
    }
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QRectF graphicsView::boundingRect() const
{
    // return QRectF(-105-50, 0, 500, 600);
    int trHOffset = 20;
    int lineRight = L_Transitions.size() * trHOffset + 25;

    int infoPadding = 150;


    // return QRectF(-150, 0, lineRight + infoPadding + 200, drawHeight);
    return QRectF(-150, -50, lineRight + infoPadding + 200, drawHeight + 100);
    // return QRectF(-105-50, 0, 500, 600);
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
