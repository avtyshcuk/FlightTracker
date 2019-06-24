#ifndef SAMREGISTRY_H
#define SAMREGISTRY_H

#include <QObject>
#include <QGeoCoordinate>

class SamRegistry : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isSamRegistered READ isSamRegistered NOTIFY isSamRegisteredChanged)

public:
    explicit SamRegistry(QObject *parent = nullptr);

    Q_INVOKABLE void registerSamPosition(const QGeoCoordinate &coordinate);
    Q_INVOKABLE void changeSamPosition(const QGeoCoordinate &coordinate);

    bool isSamRegistered() const { return mIsSamRegistered; }

signals:
    void isSamRegisteredChanged();
    void samAtMapCenterAdded();

private:
    bool mIsSamRegistered = false;
    QGeoCoordinate mSamPosition;
};

#endif // SAMREGISTRY_H
