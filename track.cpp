#include "track.h"

#include <QtMath>
#include <QDateTime>

#include <QDebug>

Track::Track(const QPointF &firstPoint)
{
    mPoints << firstPoint;
}

void Track::addPoint(const QPointF &point)
{
    mLastUpdateTime = QDateTime::currentMSecsSinceEpoch();

    if (mPoints.size() < MIN_POINT_COUNT) {
        mPoints << point;
        mPredictedPoint = point;
        return;
    }

    update(point);
}

bool Track::hasPoint(const QPointF &point)
{
    const auto &lastPoint = mPoints.last();
    return qAbs(point.x() - lastPoint.x()) < mStrobeRadius && qAbs(point.y() - lastPoint.y()) < mStrobeRadius;
}

bool Track::isOutdated(int cycleTyme) const
{
    return QDateTime::currentMSecsSinceEpoch() - mLastUpdateTime > cycleTyme;
}

void Track::update(const QPointF &point)
{
    int j = mMaxWindowSize;
    qreal vX = 0.0, vY = 0.0;
    for (int i = mPoints.size() - 1; i > 0 && j > 0; --i, --j) {
        const auto &point = mPoints.at(i);
        const auto &prevPoint = mPoints.at(i - 1);
        vX += (point.x() - prevPoint.x()) / mBeamCycle;
        vY += (point.y() - prevPoint.y()) / mBeamCycle;
    }

    const int windowSize = mMaxWindowSize - j;
    mPredictedPoint.rx() += vX / windowSize * mBeamCycle;
    mPredictedPoint.ry() += vY / windowSize * mBeamCycle;

    const auto previousPoint = mPoints.last();
    if (point.isNull()) {
        mPoints << mPredictedPoint;
        mExtrapolationCount++;
    } else {
        mPoints << QPointF(mKalmanGain*point + (1 - mKalmanGain)*mPredictedPoint);
        mExtrapolationCount = 0;
    }
    mAzimuth = qAtan2(mPoints.last().x() - previousPoint.x(), mPoints.last().y() - previousPoint.y());
}
