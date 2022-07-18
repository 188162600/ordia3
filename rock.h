#ifndef ROCK_H
#define ROCK_H

#include"abstractinterativeitem.h"
class RockPrivate;
class Rock:public AbstractInterativeItem
{
    Q_OBJECT
public:
    void setShape(const QPainterPath&shape);
    Rock(QGraphicsItem*parent=nullptr);
    QPen pen()const;
    QBrush brush()const;
    void setPen(const QPen&pen);
    void setBrush(const QBrush&brush);
    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Rock(RockPrivate&d,QGraphicsItem*parent);
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,Rock);

//private Q_SLOTS:
//    void _isAboutToCollideItem(AbstractInterativeItem*item, const QPointF&newPos,CollidingReason reason);
//    void _collidedItem(AbstractInterativeItem*item, CollidingReason reason);
};

#endif // ROCK_H
