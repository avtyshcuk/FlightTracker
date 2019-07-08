#include "trackregistry.h"

#include "beamsimulator.h"
#include "pointsreceiver.h"

#include <QDebug>
#include <QtMath>
#include <QPointF>

TrackRegistry::TrackRegistry(QObject *parent)
    : QObject(parent)
{

}

void TrackRegistry::setBeamSimulator(BeamSimulator *beamSimulator)
{
    mBeamSimulator = beamSimulator;

    connect(mBeamSimulator, &BeamSimulator::cycleStarted, [this]{
        qDebug() << "Cycle started";
        for (const auto &track : mTracks) {
            qDebug() << track.points();
        }
    });
}

void TrackRegistry::setPointsReceiver(PointsReceiver *pointsReceiver)
{
    mPointsReceiver = pointsReceiver;
    connect(mPointsReceiver, &PointsReceiver::pointReceived,
            [this](qreal distance, qreal azimuth){
        const auto point = toPlaneCoordinate(distance, azimuth);
        for (auto &track : mTracks) {
            if (track.hasPoint(point)) {
                track.addPoint(point);
                return;
            }
        }
        mTracks[freeTrackId()] = Track(point);
    });
}

QPointF TrackRegistry::toPlaneCoordinate(qreal distance, qreal azimuth)
{
    const auto azimuthRadians = qDegreesToRadians(azimuth);
    return QPointF(distance * qSin(azimuthRadians), distance * qCos(azimuthRadians));
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
