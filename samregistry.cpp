#include "samregistry.h"

SamRegistry::SamRegistry(QObject *parent)
    : QObject(parent)
{

}

void SamRegistry::setSamPosition(const QGeoCoordinate &coordinate)
{
    if (coordinate != mSamPosition) {
        mSamPosition = coordinate;
        emit samPositionChanged();
    }
}
