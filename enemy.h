#ifndef ENEMY_H
#define ENEMY_H

#include"abstractinterativeitem.h"
class EnemyPrivate;
class Enemy:public AbstractInterativeItem
{
    Q_OBJECT
public:
    Enemy(QGraphicsItem*parent=nullptr);
    QPen pen()const;
    QBrush brush()const;
    void setPen(const QPen&pen);
    void setBrush(const QBrush&brush);
    QPainterPath shape() const override;
    void setShape(const QPainterPath&shape);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
      Enemy(EnemyPrivate&d,QGraphicsItem*parent);
      Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,Enemy);
private Q_SLOTS:

    void _collides(AbstractInterativeItem*item, CollidingReason reason);




};

#endif // ENEMY_H
