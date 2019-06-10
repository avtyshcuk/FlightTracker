#ifndef SAMITEM_H
#define SAMITEM_H

#include <QQuickPaintedItem>
#include <QPainter>

class SamItem : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit SamItem(QQuickPaintedItem *parent = nullptr);

    void paint(QPainter *painter) override;
};

#endif // SAMITEM_H
