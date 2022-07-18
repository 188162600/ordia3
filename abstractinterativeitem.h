#ifndef ABSTRACTINTERATIVEITEM_H
#define ABSTRACTINTERATIVEITEM_H

#include <QGraphicsObject>
class AbstractInterativeItemPrivate;
class AbstractInterativeItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum CollidingReason{ItemMoved,OtherMoved};
    AbstractInterativeItem(QGraphicsItem *parent = nullptr);
Q_SIGNALS:

    void collided(AbstractInterativeItem*other,CollidingReason reason);
    void posChanged(const QPointF&pos);
protected:
    AbstractInterativeItem(AbstractInterativeItemPrivate&dd,QGraphicsItem*parent);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,AbstractInterativeItem);
};

#endif // ABSTRACTINTERATIVEITEM_H
