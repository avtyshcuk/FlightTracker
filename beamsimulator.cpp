#include "beamsimulator.h"

BeamSimulator::BeamSimulator(QObject *parent) : QObject(parent)
{
    constexpr qreal beamSpeed = 360.0 / 10000.0;
    QObject::connect(&mTimer, &QTimer::timeout, [this]{

        if (mAngle < 360.0) {
            mAngle += mTimer.interval() * beamSpeed;
        } else {
            mAngle = 0.0;
        }

        emit angleChanged();
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
