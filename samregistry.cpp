#include "samregistry.h"

SamRegistry::SamRegistry(QObject *parent)
    : QObject(parent)
{

}

void SamRegistry::setSamPosition(const QGeoCoordinate &coordinate)
{
    mSamPosition = coordinate;
}
