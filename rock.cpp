#include "rock.h"
#include"private/abstractinterativeitem_p.h"
#include"protagonist.h"
#include"math2d.h"
class RockPrivate:public AbstractInterativeItemPrivate
{
public:
    QPainterPath shape;
    QPen pen;
    QBrush brush;

};

void Rock::setShape(const QPainterPath &shape)
{
    Q_D(Rock);
    d->shape=shape;
    update();
}

Rock::Rock(QGraphicsItem *parent)
    :Rock(*new RockPrivate,parent)
{

}



QRectF Rock::boundingRect() const
{
    Q_D(const Rock);
  return d->shape.boundingRect();
}

QPainterPath Rock::shape() const
{
      Q_D(const Rock);
    return d->shape;
}

QPen Rock::pen() const
{
     Q_D(const Rock);
    return d->pen;
}

QBrush Rock::brush() const
{
     Q_D(const Rock);
    return d->brush;
}

void Rock::setPen(const QPen &pen)
{
     Q_D( Rock);
    d->pen=pen;
    update();
}

void Rock::setBrush(const QBrush &brush)
{
    Q_D( Rock);
   d->brush=brush;
   update();
}

void Rock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(const Rock);
    painter->setPen(d->pen);
    painter->setBrush(d->brush);
    painter->drawPath(d->shape);
}

Rock::Rock(RockPrivate &d, QGraphicsItem *parent)
    :AbstractInterativeItem(d,parent)
{

}

