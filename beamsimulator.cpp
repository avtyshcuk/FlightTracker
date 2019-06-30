#include "beamsimulator.h"

#include <QString>

#include "samregistry.h"

BeamSimulator::BeamSimulator(QObject *parent)
    : QObject(parent)
    , mUdpSocket(new QUdpSocket(parent))
{
    constexpr qreal beamSpeed = 360.0 / 10000.0;
    QObject::connect(&mTimer, &QTimer::timeout, [this]{

        if (mAngle < 360.0) {
            mAngle += mTimer.interval() * beamSpeed;
        } else {
            mAngle = 0.0;
        }
        emit angleChanged();

        mUdpSocket->writeDatagram(createDatagram(mAngle),
                                  QHostAddress::LocalHost,
                                  45454);
    });
}

void BeamSimulator::start()
{
    if (!mIsActive) {
        mTimer.start(50);
        mIsActive = true;
        emit isActiveChanged();
    }
}

void BeamSimulator::stop()
{
    if (mIsActive) {
        mTimer.stop();

        mAngle = 0.0;
        emit angleChanged();

        mIsActive = false;
        emit isActiveChanged();
    }
}

QByteArray BeamSimulator::createDatagram(qreal angle)
{
    auto position = mSamRegistry->samPosition();
    return QString("%1,%2,%3,%4")
            .arg(position.latitude())
            .arg(position.longitude())
            .arg(mDistance)
            .arg(angle)
            .toUtf8();
}
