#ifndef BEAMSIMULATOR_H
#define BEAMSIMULATOR_H

#include <QObject>
#include <QTimer>

class BeamSimulator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isActive MEMBER mIsActive NOTIFY isActiveChanged)
    Q_PROPERTY(qreal angle MEMBER mAngle NOTIFY angleChanged)

public:
    explicit BeamSimulator(QObject *parent = nullptr);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    void isActiveChanged();
    void angleChanged();

private:
    bool mIsActive = false;
    qreal mAngle = 0.0;
    QTimer mTimer;
};

#endif // BEAMSIMULATOR_H
