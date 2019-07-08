#include "track.h"

#include <QtMath>

Track::Track(const QPointF &firstPoint)
{
    mPoints << firstPoint;
}

void Track::addPoint(const QPointF &point)
{
    mPoints << point;
}

bool Track::hasPoint(const QPointF &point)
{
    const auto &lastPoint = mPoints.last();
    return qAbs(point.x() - lastPoint.x()) < mStrobeRadius && qAbs(point.y() - lastPoint.y()) < mStrobeRadius;
}
