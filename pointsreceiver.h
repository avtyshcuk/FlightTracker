#ifndef POINTSRECEIVER_H
#define POINTSRECEIVER_H

#include <QUdpSocket>
#include <QGeoCoordinate>

class SamRegistry;

class PointsReceiver : public QUdpSocket
{
    Q_OBJECT
public:
    explicit PointsReceiver(QObject *parent = nullptr);

    void setSamRegistry(SamRegistry *samRegistry) { mSamRegistry = samRegistry; }

signals:
    void geoPointReceived(const QGeoCoordinate &point);
    void pointReceived(qreal distance, qreal azimuth);

private:
    SamRegistry *mSamRegistry;
};

#endif // POINTSRECEIVER_H
