#ifndef SAMREGISTRY_H
#define SAMREGISTRY_H

#include <QObject>

class SamRegistry : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isSamModifying READ isSamModifying WRITE setIsSamModifying
               NOTIFY isSamModifyingChanged)

public:
    explicit SamRegistry(QObject *parent = nullptr);

    bool isSamModifying() const { return mIsSamModifying; }
    void setIsSamModifying(bool isSamModifying);

signals:
    void isSamModifyingChanged();

private:
    bool mIsSamModifying = false;
};

#endif // SAMREGISTRY_H
