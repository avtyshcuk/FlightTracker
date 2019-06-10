#include "samregistry.h"

SamRegistry::SamRegistry(QObject *parent)
    : QObject(parent)
{

}

void SamRegistry::setIsSamModifying(bool isSamModifying)
{
    mIsSamModifying = isSamModifying;
    emit isSamModifyingChanged();
}
