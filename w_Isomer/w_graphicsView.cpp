#include "w_graphicsView.h"
#include "L_element.h"

#include <QPainter>
#include <QPen>
#include <QPolygon>
#include <QStaticText>


//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

graphicsView::graphicsView(const Isotope& iso,
                           QGraphicsItem *parent)
    :
    QGraphicsItem(parent),
    L_isotope(iso)

    // L_Levels(levels),
    // L_Transitions(transitions)
{
    maxEnergy = 0;
    trCount = 0;
    for (const Level& lvl : L_isotope.levels) {
        maxEnergy = std::max(maxEnergy, lvl.lvlEnergy);
        // qDebug() << "[GRAPHIC VIEW: check transitions counts]" << lvl.transitions.count();
        trCount += lvl.transitions.count();
    }
    scale = 1.;

    drawHeight = 600;
    scale = drawHeight/maxEnergy;

    // qDebug() << "[CONSTRUCT: transition count]" << trCount;

    // qDebug() << "[CONSTRUCT: drawheight, maxEnergy]" << drawHeight << maxEnergy << drawHeight/maxEnergy;

}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void graphicsView::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *,
                              QWidget *)
{
    // qDebug() << "[graphicsView: PAINTING]";
    painter->setRenderHint(QPainter::Antialiasing);
    extern QRect OutTextOleg(QPainter *painter, int x, int y, const char *s, int loc, int clip=0,
                             const QRectF* PlotRect=nullptr);

    int trHOffset = 20;

    int lineLeft = 0;
    int lineRight = trCount*trHOffset + 25;
    int indentation = 25;
    // qDebug() << "[graphicsView: line left/right]" << lineLeft << lineRight;
    // qDebug() << "[graphicsView: transition count]: "<< trCount;


    int titleOffset = 20;
    int spinOffset = -45;
    int infoHOffset = 10;
    // int textVOffset = -5;
    int arrowHeadSize = 6;

    QColor lineColor(0,0,0);
    QColor levelTextColor(0,0,0);
    QColor transitionColor(34, 139, 34);

    double yBase = drawHeight;

    int xOffset = 0;

    // QPainter painter(this);
    // QStaticText staticText("TESTTEST<sup>3</sup>");
    // painter->drawStaticText(10, 10, staticText);
    QString title = QString("<h1><b><sup>%1</sup>%2</b></h1>")
                        .arg(L_isotope.A)
                        .arg(atomicSymbol(L_isotope.Z));

    QStaticText staticText(title);

    painter->drawStaticText((lineLeft+lineRight)/2 - 25,yBase + titleOffset,staticText);
    bool firstIt = true;

    for (const Level &lvl : L_isotope.levels)
      {
        int y = static_cast<int>(yBase - lvl.lvlEnergy*scale);
        painter->setPen(QPen(lineColor, 2));
        painter->drawLine(lineLeft, y, lineRight, y);

        if (firstIt) {
            painter->drawLine(lineLeft,yBase,lineRight,yBase);

            painter->setPen(levelTextColor);
            painter->drawText(lineRight + infoHOffset, yBase, QString("0.0       Stable"));
            firstIt = false;

        }

        painter->setPen(levelTextColor);
        painter->drawText(spinOffset, y, lvl.spin);
        QString levelText = QString("%1        %2 \u03BCs")
                           .arg(lvl.lvlEnergy, 0, 'f', 0)
                           .arg(lvl.halfLife);

        painter->drawText(lineRight + infoHOffset, y, levelText);

        // ~~~~~ transition drawing
        painter->setPen(QPen(transitionColor, 2));
        painter->setBrush(transitionColor);

        for (const Transition &tr : lvl.transitions) {
            double Ei = tr.lvlEnergy;
            double Ef = tr.lvlEnergy - tr.emission;

            double y1 = static_cast<int>(yBase - Ei*scale);
            double y2 = static_cast<int>(yBase - Ef*scale);

            int x = lineLeft + indentation + xOffset;

            painter->drawLine(x, y1, x, y2);

            QPolygon arrowHead;
            arrowHead << QPoint(x - arrowHeadSize, y2 - arrowHeadSize)
                      << QPoint(x + arrowHeadSize, y2 - arrowHeadSize)
                      << QPoint(x, y2);
            painter->drawPolygon(arrowHead);

            QFont pFont = painter->font();
            QFontMetrics metrics(pFont);
            int width = metrics.horizontalAdvance(tr.label);
            qDebug() << "[graphicsView TRANS FONT]" << tr.label << ":" << width;

            painter->setPen(transitionColor);
            // make labels vertical for transition lines
            painter->rotate(90);
            painter->drawText((y1+y2 - width)/2,-(x+5),tr.label);
            painter->setPen(QPen(transitionColor, 2));
            painter->rotate(-90);

            xOffset += 20; // iterate xOffset for next transition line


        }

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

    // for (const Transition &tr : L_Transitions)
    //   {
    //     int y1 = static_cast<int>(yBase - tr.lvlEnergy*scale);
    //     int y2 = static_cast<int>(yBase - tr.emission*scale);

    //     int x = lineLeft + indentation + xOffset;

    //     painter->drawLine(x, y1, x, y2);

    //     QPolygon arrowHead;
    //     arrowHead << QPoint(x - arrowHeadSize, y2 - arrowHeadSize)
    //               << QPoint(x + arrowHeadSize, y2 - arrowHeadSize)
    //               << QPoint(x, y2);
    //     painter->drawPolygon(arrowHead);

    //     painter->setPen(transitionColor);

    //     painter->drawText(x + 8, (y1 + y2) / 2, tr.label);
    //     painter->setPen(QPen(transitionColor, 2));

    //     xOffset += 20;
    // }
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QRectF graphicsView::boundingRect() const
{
    // return QRectF(-105-50, 0, 500, 600);
    int trHOffset = 20;
    int lineRight = trCount * trHOffset + 25;

    int infoPadding = 150;


    // return QRectF(-150, 0, lineRight + infoPadding + 200, drawHeight);
    return QRectF(-150, -50, lineRight + infoPadding + 200, drawHeight + 100);
    // return QRectF(-105-50, 0, 500, 600);
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

