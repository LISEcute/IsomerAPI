#include "w_graphicsView.h"
#include "L_element.h"

#include <QPainter>
#include <QPen>
#include <QPolygon>
#include <QStaticText>
#include <QTextDocument>


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
    // extern QRect OutTextOleg(QPainter *painter, int x, int y, const char *s, int loc, int clip=0,
    //                          const QRectF* PlotRect=nullptr);

    int trHOffset = 20;

    int lineLeft = 0;
    int lineRight = trCount*trHOffset + 25;
    int indentation = 25;
    // qDebug() << "[graphicsView: line left/right]" << lineLeft << lineRight;
    // qDebug() << "[graphicsView: transition count]: "<< trCount;


    int titleOffset = 20;
    int spinOffset = -45;
    int infoHOffset = 10;
    int halfLifeOffset = 80;
    // int textVOffset = -5;
    int arrowHeadSize = 5;
    int arrowPointiness = 5;

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


    // ~~~~ painter method with filled background!!!
    // QTextDocument doc;
    // // Use a span with a background-color style
    // doc.setHtml("<span style=\"background-color: yellow;\">Hello World</span>");
    // doc.setTextWidth(200); // Optional: define a fixed width for wrapping

    // painter->translate(50, 50); // Move painter to position
    // doc.drawContents(painter);
    // painter->translate(-50,-50);


    for (const Level &lvl : L_isotope.levels)
      {
        int y = static_cast<int>(yBase - lvl.lvlEnergy*scale);
        painter->setPen(QPen(lineColor, 2));
        painter->drawLine(lineLeft, y, lineRight, y);

        if (firstIt) {
            painter->drawLine(lineLeft,yBase,lineRight,yBase);

            painter->setPen(levelTextColor);
            painter->drawText(lineRight + infoHOffset, yBase, QString(""));
            firstIt = false;

        }

        QFont f = painter->font();
        f.setBold(true);
        painter->setFont(f);
        painter->setPen(levelTextColor);
        painter->drawText(spinOffset, y, lvl.spin);
        f.setBold(false);
        painter->setFont(f);

        QString levelText = QString("%1 keV")
                                .arg(lvl.lvlEnergy, 0, 'f', 0);


        QString halfLifeText = QString("%2 \u03BCs")
                                .arg(lvl.halfLife, 0, 'e',2);

        painter->drawText(lineRight + infoHOffset, y, levelText);
        if (lvl.halfLife != 0.0) {
            painter->drawText(lineRight + infoHOffset + halfLifeOffset, y, halfLifeText);
        }

        // else if (lvl.halfLife == 0.0) {
        //     painter->drawText(lineRight + infoHOffset, y, "STABLE");
        // }


        // ~~~~~ transition drawing
        painter->setPen(QPen(transitionColor, 2));
        painter->setBrush(transitionColor);



        for (const Transition &tr : lvl.transitions) {
            double Ei = tr.lvlEnergy;
            if (Ei == 0.) continue;
            double Ef = tr.lvlEnergy - tr.emission;

            double y1 = static_cast<int>(yBase - Ei*scale);
            double y2 = static_cast<int>(yBase - Ef*scale);

            int x = lineLeft + indentation + xOffset;

            painter->drawLine(x, y1, x, y2);

            QPolygon arrowHead;
            arrowHead << QPoint(x - arrowHeadSize, y2 - arrowHeadSize - arrowPointiness)
                      << QPoint(x + arrowHeadSize, y2 - arrowHeadSize - arrowPointiness)
                      << QPoint(x, y2);
            painter->drawPolygon(arrowHead);

            QFont pFont = painter->font();
            QFontMetrics metrics(pFont);
            int width = metrics.horizontalAdvance(tr.label);
            // qDebug() << "[graphicsView TRANS FONT]" << tr.label << ":" << width;

            painter->setPen(transitionColor);
            f.setBold(true);
            painter->setFont(f);
            // make labels vertical for transition lines
            painter->rotate(90);
            painter->drawText((y1+y2 - width)/2,-(x+5),tr.label);
            f.setBold(false);
            painter->setFont(f);
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

