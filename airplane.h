#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QQuickPaintedItem>
#include <QPainter>

class AirPlane : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit AirPlane(QQuickPaintedItem *parent = nullptr);

    void paint(QPainter *painter) override;
};

#endif // AIRPLANE_H
