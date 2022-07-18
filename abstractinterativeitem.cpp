#include "abstractinterativeitem.h"
#include"private/abstractinterativeitem_p.h"

AbstractInterativeItem::AbstractInterativeItem(QGraphicsItem *parent) :
    AbstractInterativeItem(*new AbstractInterativeItemPrivate,parent)
{}

AbstractInterativeItem::AbstractInterativeItem(AbstractInterativeItemPrivate &dd, QGraphicsItem *parent)
    :QGraphicsObject(dd,parent)
{
    setFlag(ItemSendsGeometryChanges);
}

QVariant AbstractInterativeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    Q_D(AbstractInterativeItem);
    if(change==ItemPositionHasChanged)
    {
        Q_EMIT(posChanged(value.toPoint()));
        if(not d->checkCollison)
            return QGraphicsObject::itemChange(change,value);;
        for(QGraphicsItem*item:collidingItems(Qt::IntersectsItemShape))
        {
            AbstractInterativeItem*other=qobject_cast<AbstractInterativeItem*>(item->toGraphicsObject());

             if(other)
             {
            Q_EMIT(collided(other,ItemMoved));
                Q_EMIT(other->collided(this,OtherMoved));
             }

        }
    }
    return QGraphicsObject::itemChange(change,value);
}
