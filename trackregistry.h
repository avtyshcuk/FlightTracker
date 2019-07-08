#ifndef TRACKREGISTRY_H
#define TRACKREGISTRY_H

#include <QObject>
#include <QMap>

#include "track.h"

class BeamSimulator;
class PointsReceiver;

class TrackRegistry : public QObject
{
    Q_OBJECT
public:
    explicit TrackRegistry(QObject *parent = nullptr);

    void setBeamSimulator(BeamSimulator *beamSimulator);
    void setPointsReceiver(PointsReceiver *pointsReceiver);

private:
    QPointF toPlaneCoordinate(qreal distance, qreal azimuth);
    int freeTrackId();

private:
    QMap<int, Track> mTracks;
    BeamSimulator *mBeamSimulator;
    PointsReceiver *mPointsReceiver;
};

#endif // TRACKREGISTRY_H
