#include "beampositionitem.h"

#include <QtMath>

BeamPositionItem::BeamPositionItem(QQuickPaintedItem *parent)
    : QQuickPaintedItem (parent)
{

}

void BeamPositionItem::paint(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->setRenderHints(QPainter::Antialiasing, true);

    painter->drawLine(mStartPoint, mEndPoint);
}

void BeamPositionItem::setStartPoint(const QPointF &startPoint)
{
    if (startPoint != mStartPoint) {
        mStartPoint = startPoint;
        emit startPointChanged();
        update();
    }
}

void BeamPositionItem::setEndPoint(const QPointF &endPoint)
{
    if (endPoint != mEndPoint) {
        mEndPoint = endPoint;
        emit endPointChanged();
        update();
    }
}
