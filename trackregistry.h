#ifndef TRACKREGISTRY_H
#define TRACKREGISTRY_H

#include <QObject>
#include <QMap>
#include <QGeoCoordinate>

#include "track.h"

class BeamSimulator;
class PointsReceiver;
class SamRegistry;

class TrackRegistry : public QObject
{
    Q_OBJECT
public:
    explicit TrackRegistry(QObject *parent = nullptr);

    void setBeamSimulator(BeamSimulator *beamSimulator);
    void setPointsReceiver(PointsReceiver *pointsReceiver);
    void setSamRegistry(SamRegistry *samRegistry) { mSamRegistry = samRegistry; }

signals:
    void trackChanged(int id, QVariant geoPoint, qreal azimuth);
    void clearTrack(int id);
    void clearAll();

private:
    void notifyTrackChange(int id, const Track &track);
    void triggerExtrapolation(int id, Track &track);
    QPointF toPlaneCoordinate(qreal distance, qreal azimuth);
    QGeoCoordinate toGeoCoordinate(const QPointF &point);
    int freeTrackId();

private:
    QMap<int, Track> mTracks;
    BeamSimulator *mBeamSimulator;
    PointsReceiver *mPointsReceiver;
    SamRegistry *mSamRegistry;

    static constexpr int mWaitTime = 500;
};

#endif // TRACKREGISTRY_H
