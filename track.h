#ifndef TRACK_H
#define TRACK_H

#include <QPointF>
#include <QList>

class Track
{
public:
    explicit Track(const QPointF &firstPoint = QPointF{});

    void addPoint(const QPointF &point);
    bool hasPoint(const QPointF &point);

    QList<QPointF> points() const { return mPoints; }

private:
    QList<QPointF> mPoints;

    // Assume that Boeing-747 has maximum speed 920km/h
    // and we try to 2*distance per 10 sec beam cycle
    constexpr static qreal mStrobeRadius = 2 * 255.5 * 10.0;
};

#endif // TRACK_H
