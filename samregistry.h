#ifndef SAMREGISTRY_H
#define SAMREGISTRY_H

#include <QObject>
#include <QGeoCoordinate>

class SamRegistry : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QGeoCoordinate samPosition MEMBER mSamPosition NOTIFY samPositionChanged)

public:
    explicit SamRegistry(QObject *parent = nullptr);

    Q_INVOKABLE void setSamPosition(const QGeoCoordinate &coordinate);

signals:
    void samPositionChanged();

private:
    QGeoCoordinate mSamPosition;
};

#endif // SAMREGISTRY_H
