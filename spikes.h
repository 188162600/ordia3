#ifndef SPIKES_H
#define SPIKES_H

#include<abstractinterativeitem.h>
class SpikesPrivate;
class Spikes:public AbstractInterativeItem
{
public:
    struct Spike
    {
        Spike(const QLineF&body,qreal width,const QSizeF&headSize):body(body),width(width),headSize(headSize){};
        QLineF body;
        qreal width;
        QSizeF headSize;


    };

    Spikes(QGraphicsItem*parent=nullptr);
    void setSpikes(const QList<Spike>&spikes);

     QList<Spike>spikes()const;


     QPen pen()const;
     QBrush brush()const;
     void setPen(const QPen&pen);
     void setBrush(const QBrush&brush);
      QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    Spikes(SpikesPrivate&dd,QGraphicsItem*parent);
private:
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,Spikes);

private Q_SLOTS:
    void _collidedItem(AbstractInterativeItem*item, CollidingReason reason);
};

#endif // SPIKES_H
