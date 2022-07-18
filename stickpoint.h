#ifndef STICKPOINT_H
#define STICKPOINT_H
#include<QPen>
#include<QBrush>
#include"abstractinterativeitem.h"
#include<QPainterPath>
#include"math2d.h"
class AbstractProtagonist;
class StickPointPrivate;
class StickPoint:public AbstractInterativeItem
{
    Q_OBJECT
public:
    StickPoint(QGraphicsItem *parent=nullptr);
    void setPen(const QPen&pen);
     void setBrush(const QBrush&brush);
     void setShape(const QPainterPath&shape);
     void setAttractingTime(int time);
     QPen pen()const;
     QBrush brush()const;
     int attractingTime()const;
     AbstractProtagonist*stickedItem()const;

     QRectF boundingRect() const override;
     QPainterPath shape() const override;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public Q_SLOTS:
     inline void setPos(const QPointF&pos){QGraphicsItem::setPos(pos);};
     inline void setPos(qreal x,qreal y){QGraphicsItem::setPos(x,y);};
protected:
     virtual void setStickedItem(AbstractProtagonist*item);
     StickPoint(StickPointPrivate&d,QGraphicsItem*parent);

//Q_SIGNALS:
//     void stickedItemChange(AbstractProtagonist*newItem);
private:
     Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,StickPoint)
     void attractStickedItem();

     // QGraphicsItem interface
private Q_SLOTS:
     void _stickedItemLaunch();
     void _collide(AbstractInterativeItem*item,AbstractInterativeItem::CollidingReason reason);



     // QGraphicsItem interface
protected:
     QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // STICKPOINT_H
