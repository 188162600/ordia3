#include "enemy.h"
#include"private/abstractinterativeitem_p.h"
#include"protagonist.h"
class EnemyPrivate:public AbstractInterativeItemPrivate
{
public:
    QPen pen;
    QBrush brush;
    QPainterPath shape;
    mutable QRectF bouncingRect;
};


Enemy::Enemy(QGraphicsItem *parent)
    :Enemy(*new EnemyPrivate,parent)
{

}

QPen Enemy::pen() const
{
    Q_D(const Enemy);
    return d->pen;

}

QBrush Enemy::brush() const
{
    Q_D(const Enemy);
    return d->brush;
}

void Enemy::setPen(const QPen &pen)
{
    Q_D( Enemy);
     d->bouncingRect=QRectF();
     d->pen=pen;
}

void Enemy::setBrush(const QBrush &brush)
{
    Q_D(Enemy);
    d->brush=brush;
}

QPainterPath Enemy::shape() const
{
    Q_D(const Enemy);
    return d->shape;

}

void Enemy::setShape(const QPainterPath &shape)
{
    Q_D( Enemy);
    d->bouncingRect=QRectF();
    d->shape=shape;
    update();

}

Enemy::Enemy(EnemyPrivate &d, QGraphicsItem *parent)
    :AbstractInterativeItem(d,parent)
{
    connect(this,&AbstractInterativeItem::collided,this,&Enemy::_collides);
}

void Enemy::_collides(AbstractInterativeItem *item, CollidingReason reason)
{
    AbstractProtagonist*p=qobject_cast<AbstractProtagonist*>(item);
    if(p!=nullptr)
    {

        p->die();

    }
}

QRectF Enemy::boundingRect() const
{
    Q_D(const Enemy);
    if(d->bouncingRect==QRectF())
    {
        qreal pad=d->pen.widthF()/2;
        d->bouncingRect=d->shape.boundingRect().adjusted(-pad,-pad,pad,pad);
    }
    return d->bouncingRect;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(Enemy);
    painter->setBrush(d->brush);
    painter->setPen(d->pen);
    painter->drawPath(d->shape);

}


