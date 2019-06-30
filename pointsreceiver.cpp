#include "pointsreceiver.h"

#include <QNetworkDatagram>

PointsReceiver::PointsReceiver(QObject *parent)
    : QUdpSocket(parent)
{
    bind(45455, QUdpSocket::ShareAddress);
    QObject::connect(this, &QUdpSocket::readyRead, [this]{
        while (hasPendingDatagrams()) {
            auto datagram = receiveDatagram();
            auto dataString = QString::fromUtf8(datagram.data());
            auto dataList = dataString.split(',');
            auto latitude = dataList.at(0).toDouble();
            auto longitude = dataList.at(1).toDouble();

            emit pointReceived(QGeoCoordinate(latitude, longitude));
            qDebug() << datagram.data();
        }
    });
}
