#include "pointsreceiver.h"

#include <QNetworkDatagram>

#include "samregistry.h"

PointsReceiver::PointsReceiver(QObject *parent)
    : QUdpSocket(parent)
{
    bind(45455, QUdpSocket::ShareAddress);
    QObject::connect(this, &QUdpSocket::readyRead, [this]{
        while (hasPendingDatagrams()) {
            auto datagram = receiveDatagram();
            auto dataString = QString::fromUtf8(datagram.data());
            auto dataList = dataString.split(',');
            auto distance = dataList.at(0).toDouble();
            auto azimuth = dataList.at(1).toDouble();

            emit pointReceived(distance, azimuth);

            const QGeoCoordinate &samPosition = mSamRegistry->samPosition();
            const QGeoCoordinate point = samPosition.atDistanceAndAzimuth(distance, azimuth);

            emit geoPointReceived(point);
        }
    });
}
