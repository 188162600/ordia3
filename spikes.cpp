#include "spikes.h"
#include"private/abstractinterativeitem_p.h"
#include"protagonist.h"
class SpikesPrivate:public AbstractInterativeItemPrivate
{
public:
    SpikesPrivate():pen(Qt::NoPen),brush(QColor(231, 40, 151)){}
    QList<Spikes::Spike>spikes;
    QPainterPath shape;
    QPen pen;
    QBrush brush;
};

Spikes::Spikes( QGraphicsItem *parent)
    :Spikes(*new SpikesPrivate,parent)
{

}

void Spikes::setSpikes(const QList<Spike> &spikes)
{
     Q_D(Spikes);
    d->spikes=spikes;
    d->shape.clear();
    for(const auto &i:d->spikes)
    {
        QPointF translation=QLineF::fromPolar(i.width/2,i.body.angle()+90).p2();
        d->shape.addPolygon(QPolygonF({i.body.p1()+translation,i.body.p2()+translation,
                                        i.body.p2()-translation,i.body.p1()-translation}));
        d->shape.addEllipse(i.body.x2()-i.headSize.width()/2,i.body.y2()-i.headSize.width()/2,
                          i.headSize.width(),i.headSize.height());

    }
    update();
}

QList<Spikes::Spike> Spikes::spikes() const
{
      Q_D(const Spikes);
    return d->spikes;
}

QPen Spikes::pen() const
{
     Q_D(const Spikes);
    return d->pen;
}

QBrush Spikes::brush() const
{
     Q_D(const Spikes);
    return d->brush;
}

void Spikes::setPen(const QPen &pen)
{
     Q_D( Spikes);
    d->pen=pen;
    update();
}

void Spikes::setBrush(const QBrush &brush)
{
    Q_D( Spikes);
   d->brush=brush;
   update();
}

QRectF Spikes::boundingRect() const
{
    Q_D(const Spikes);
    return d->shape.boundingRect();
}

void Spikes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(Spikes);
    painter->setBrush(d->brush);
    painter->setPen(d->pen);
    painter->drawPath(d->shape);



}

Spikes::Spikes(SpikesPrivate &dd, QGraphicsItem *parent)
    :AbstractInterativeItem(dd,parent)
{
    Q_D(Spikes);
    d->shape.setFillRule(Qt::WindingFill);
    connect(this,&AbstractInterativeItem::collided,this,&Spikes::_collidedItem);
}

void Spikes::_collidedItem(AbstractInterativeItem *item,CollidingReason reason)
{
    AbstractProtagonist*p=qobject_cast<AbstractProtagonist*>(item);
    if(p)
        p->die();
}



QPainterPath Spikes::shape() const
{
    Q_D(const Spikes);
    return d->shape;
}
