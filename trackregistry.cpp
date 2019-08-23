#include "trackregistry.h"

#include "beamsimulator.h"
#include "pointsreceiver.h"
#include "samregistry.h"

#include <QDebug>
#include <QtMath>
#include <QPointF>
#include <QTimer>

TrackRegistry::TrackRegistry(QObject *parent)
    : QObject(parent)
{

}

void TrackRegistry::setBeamSimulator(BeamSimulator *beamSimulator)
{
    mBeamSimulator = beamSimulator;

    connect(mBeamSimulator, &BeamSimulator::isActiveChanged, [this]{
        if (!mBeamSimulator->isActive()) {
            mTracks.clear();
            emit clearAll();
        }
    });
}

void TrackRegistry::setPointsReceiver(PointsReceiver *pointsReceiver)
{
    mPointsReceiver = pointsReceiver;

    connect(mPointsReceiver, &PointsReceiver::pointReceived,
            [this](qreal distance, qreal azimuth){

        const auto point = toPlaneCoordinate(distance, azimuth);
        auto it = mTracks.begin();
        while (it != mTracks.end()) {
            if (it->hasPoint(point)) {

                it->addPoint(point);
                if (it->isValid()) {
                    notifyTrackChange(it.key(), *it);
                }
                triggerExtrapolation(it.key(), *it);
                return;
            }
            ++it;
        }
        mTracks[freeTrackId()] = Track(point);
    });
}

void TrackRegistry::notifyTrackChange(int id, const Track &track)
{
    const auto position = toGeoCoordinate(track.points().last());
    const auto azimuth = qRadiansToDegrees(track.azimuth());
    emit trackChanged(id, QVariant::fromValue(position), azimuth);
}

void TrackRegistry::triggerExtrapolation(int id, Track &track)
{
    // We wait some time for data and extrapolate based on prediction
    const auto cycleTime = mBeamSimulator->cycleTime();
    QTimer::singleShot(cycleTime + mWaitTime, this, [this, id, &track, cycleTime]{
        if (track.isValid() && track.isOutdated(cycleTime)) {
            track.update(QPointF{ });
            notifyTrackChange(id, track);

            if (track.isFinished()) {
                mTracks.remove(id);
                emit clearTrack(id);
                return;
            }
            triggerExtrapolation(id, track);
        }
    });
}

QPointF TrackRegistry::toPlaneCoordinate(qreal distance, qreal azimuth)
{
    const auto azimuthRadians = qDegreesToRadians(azimuth);
    return QPointF(distance * qSin(azimuthRadians), distance * qCos(azimuthRadians));
}

QGeoCoordinate TrackRegistry::toGeoCoordinate(const QPointF &point)
{
    auto distance = qSqrt(point.x()*point.x() + point.y()*point.y());
    auto radianAngle = qAtan2(point.x(), point.y());
    auto azimuth = qRadiansToDegrees(radianAngle < 0 ? radianAngle + 2*M_PI : radianAngle);

    return mSamRegistry->samPosition().atDistanceAndAzimuth(distance, azimuth);
}

int TrackRegistry::freeTrackId()
{
    // Keys in map are sorted, first absent index is free ID
    const auto &keys = mTracks.keys();
    for (int index = 0; index < keys.size(); ++index) {
        if (keys[index] != index) {
            return index;
        }
    }

    // If list does not contain free ones, take the biggest
    return keys.size();
}
