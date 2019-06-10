#include "samitem.h"

SamItem::SamItem(QQuickPaintedItem *parent)
    : QQuickPaintedItem (parent)
{

}

void SamItem::paint(QPainter *painter)
{
    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);

    painter->drawEllipse(QRect(1, 1, 33, 33));
    painter->drawLines(QVector<QLine>{QLine(QPoint(13, 13), QPoint(17, 5)),
                                      QLine(QPoint(17, 5), QPoint(21, 13)),
                                      QLine(QPoint(17, 5), QPoint(17, 25)),
                                      QLine(QPoint(9, 21), QPoint(9, 25)),
                                      QLine(QPoint(9, 25), QPoint(25, 25)),
                                      QLine(QPoint(25, 25), QPoint(25, 21))});
}
