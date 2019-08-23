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
    qreal azimuth() const { return mAzimuth; }
    bool isValid() const { return mPoints.size() > MIN_POINT_COUNT; }
    bool isOutdated(int cycleTyme) const;
    bool isFinished() { return mExtrapolationCount > mMaxWindowSize; }
    void update(const QPointF &point);

private:
    QList<QPointF> mPoints;
    QPointF mPredictedPoint;
    qreal mAzimuth = 0.0;
    qint64 mLastUpdateTime = 0;
    int mExtrapolationCount = 0;

    constexpr static int MIN_POINT_COUNT = 3;

    // Assume that Boeing-747 has maximum speed 920km/h
    // and we try to 3*distance per 10 sec beam cycle
    constexpr static qreal mBeamCycle = 10.0;
    constexpr static qreal mStrobeRadius = 3 * 255.5 * mBeamCycle;

    // Last 5 points are used for prediction
    constexpr static int mMaxWindowSize = 5;

    // For simplicity Kalman gain is 0.8
    constexpr static qreal mKalmanGain = 0.8;
};

#endif // TRACK_H
