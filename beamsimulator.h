#ifndef BEAMSIMULATOR_H
#define BEAMSIMULATOR_H

#include <QTimer>
#include <QUdpSocket>
#include <QGeoCoordinate>

class SamRegistry;

class BeamSimulator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isActive MEMBER mIsActive NOTIFY isActiveChanged)
    Q_PROPERTY(qreal angle MEMBER mAngle NOTIFY angleChanged)
    Q_PROPERTY(qreal distance MEMBER mDistance CONSTANT)

public:
    explicit BeamSimulator(QObject *parent = nullptr);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    void setSamRegistry(SamRegistry *samRegistry) { mSamRegistry = samRegistry; }

signals:
    void isActiveChanged();
    void angleChanged();
    void cycleStarted();

private:
    QByteArray createDatagram(qreal angle);

private:
    bool mIsActive = false;
    qreal mAngle = 0.0;
    const qreal mDistance = 250000.0;
    SamRegistry *mSamRegistry;
    QTimer mTimer;
    QUdpSocket *mUdpSocket;
};

#endif // BEAMSIMULATOR_H
