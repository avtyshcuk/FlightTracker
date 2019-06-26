#ifndef BEAMPOSITIONITEM_H
#define BEAMPOSITIONITEM_H

#include <QQuickPaintedItem>
#include <QPainter>

class BeamPositionItem : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QPointF startPoint READ startPoint WRITE setStartPoint NOTIFY startPointChanged)
    Q_PROPERTY(QPointF endPoint READ endPoint WRITE setEndPoint NOTIFY endPointChanged)

public:
    explicit BeamPositionItem(QQuickPaintedItem *parent = nullptr);

    void paint(QPainter *painter) override;

    QPointF startPoint() const { return mStartPoint; }
    void setStartPoint(const QPointF &startPoint);
    QPointF endPoint() const { return mEndPoint; }
    void setEndPoint(const QPointF &endPoint);

signals:
    void startPointChanged();
    void endPointChanged();

private:
    QPointF mStartPoint;
    QPointF mEndPoint;
};

#endif // BEAMPOSITIONITEM_H
