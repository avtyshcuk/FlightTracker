#include "samregistry.h"

SamRegistry::SamRegistry(QObject *parent)
    : QObject(parent)
{

}

void SamRegistry::registerSamPosition(const QGeoCoordinate &coordinate)
{
    mSamPosition = coordinate;

    mIsSamRegistered = true;
    emit isSamRegisteredChanged();
}

void SamRegistry::changeSamPosition(const QGeoCoordinate &coordinate)
{
    mSamPosition = coordinate;
}
