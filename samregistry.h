#ifndef SAMREGISTRY_H
#define SAMREGISTRY_H

#include <QObject>
#include <QGeoCoordinate>

class SamRegistry : public QObject
{
    Q_OBJECT

public:
    explicit SamRegistry(QObject *parent = nullptr);

    Q_INVOKABLE void setSamPosition(const QGeoCoordinate &coordinate);

private:
    QGeoCoordinate mSamPosition;
};

#endif // SAMREGISTRY_H
