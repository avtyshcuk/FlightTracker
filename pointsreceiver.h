#ifndef POINTSRECEIVER_H
#define POINTSRECEIVER_H

#include <QUdpSocket>
#include <QGeoCoordinate>

class PointsReceiver : public QUdpSocket
{
    Q_OBJECT
public:
    explicit PointsReceiver(QObject *parent = nullptr);

signals:
    void pointReceived(const QGeoCoordinate &point);

};

#endif // POINTSRECEIVER_H
