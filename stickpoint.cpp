#include "stickpoint.h"
#include<protagonist.h>
#include<QPainter>
#include"private/abstractinterativeitem_p.h"
#include"private/stickpoint_p.h"
#include"private/abstractprotagonist_p.h"
void StickPointPrivate::updateBoundingRect()
{qreal pad=pen.widthF()/2;boundingRect=shape.boundingRect().adjusted(-pad,-pad,pad,pad);}
StickPoint::StickPoint(QGraphicsItem*parent)
    :StickPoint(*new StickPointPrivate,parent)
{
    setFlag(ItemSendsGeometryChanges);
}

void StickPoint::setPen(const QPen &pen)
{
     Q_D( StickPoint);
    d->pen=pen;
    d->updateBoundingRect();
    update();
}

void StickPoint::setBrush(const QBrush &brush)
{
     Q_D( StickPoint);
    d->brush=brush;
    update();
}

void StickPoint::setShape(const QPainterPath &shape)
{
     Q_D( StickPoint);
    d->shape=shape;
    d->updateBoundingRect();
    update();
}

void StickPoint::setAttractingTime(int time)
{
    Q_D( StickPoint);
     d->attractingTime=time;
}


QPen StickPoint::pen() const
{
    Q_D(const StickPoint);
  return d->pen;
}

QBrush StickPoint::brush() const
{
    Q_D(const StickPoint);
    return d->brush;
}

int StickPoint::attractingTime() const
{

    Q_D(const StickPoint);
    return d->attractingTime;
}



AbstractProtagonist *StickPoint::stickedItem() const
{
    Q_D(const StickPoint);
    return d->stickedItem;
}

void StickPoint::setStickedItem(AbstractProtagonist *item)
{
    Q_D(StickPoint);

    d->attracingState=StickPointPrivate::NotAttracingItem;
    if(d->stickedItem!=nullptr){
        disconnect(&AbstractProtagonistPrivate::get(d->stickedItem)->accelerationTimeLine,&QTimeLine::valueChanged,this,&StickPoint::attractStickedItem);
        disconnect(d->stickedItem,&AbstractProtagonist::launched,this,&StickPoint::_stickedItemLaunch);
    }
    d->stickedItem=item;
    if(item)
    {
        this->stackBefore(item);
       // item->stackBefore(this);
        item->setLaunchingChance(item->launchingChance()+1);
        connect(&AbstractProtagonistPrivate::get(d->stickedItem)->accelerationTimeLine,&QTimeLine::valueChanged,this,&StickPoint::attractStickedItem);
        connect(d->stickedItem,&AbstractProtagonist::launched,this,&StickPoint::_stickedItemLaunch);
        //connect(d->stickedItem,&AbstractProtagonist::launched,this,&StickPoint::_stickedItemLaunch,Qt::ConnectionType(Qt::BlockingQueuedConnection|Qt::SingleShotConnection));
    }

    attractStickedItem();

}

QRectF StickPoint::boundingRect() const
{
    Q_D(const StickPoint);

  return d->boundingRect;
}

QPainterPath StickPoint::shape() const
{
      Q_D(const StickPoint);
    return d->shape;
}

void StickPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(const StickPoint);
    painter->setPen(d->pen);
    painter->setBrush(d->brush);
    painter->drawPath(d->shape);

}

StickPoint::StickPoint(StickPointPrivate &d, QGraphicsItem *parent)
    :AbstractInterativeItem(d,parent)
{

    connect(this,&AbstractInterativeItem::collided,this,&StickPoint::_collide);

  //  connect(this,&StickPoint::,this,&StickPoint::_collide);

}

void StickPoint::attractStickedItem()
{
    Q_D(StickPoint);


    if(d->stickedItem)
    {
          ;
         
        switch (d->attracingState) {
        case StickPointPrivate::NotAttracingItem:
        {

            QPointF itemScenePos=d->stickedItem->scenePos();
            QPointF posInScene=scenePos();
            qreal xAcceleration=2*((posInScene.x()-itemScenePos.x()-d->stickedItem->xSpeed()*d->attractingTime)/d->attractingTime/d->attractingTime);
            qreal yAcceleration=2*((posInScene.y()-itemScenePos.y()-d->stickedItem->ySpeed()*d->attractingTime)/d->attractingTime/d->attractingTime);
             d->stickedItem->setAccleration(xAcceleration,yAcceleration,d->attractingTime);

             d->attracingState=StickPointPrivate::AttracingItem;

            Trajectory2d t;
            t.setInitialSpeed(d->stickedItem->xSpeed(),d->stickedItem->ySpeed());
            t.setAcceleration(xAcceleration,yAcceleration,d->attractingTime);
            break;
        }
        case StickPointPrivate::UpdatingAttraction:
        {
            QPointF itemScenePos=d->stickedItem->scenePos();
            QPointF posInScene=scenePos();
            qreal time=d->stickedItem->accelerationRestTime();
            qreal xAcceleration=2*((posInScene.x()-itemScenePos.x()-d->stickedItem->xSpeed()*time)/time/time);
            qreal yAcceleration=2*((posInScene.y()-itemScenePos.y()-d->stickedItem->ySpeed()*time)/time/time);
             d->stickedItem->setAccleration(xAcceleration,yAcceleration,time);
             d->attracingState=StickPointPrivate::AttracingItem;

            Trajectory2d t;
            t.setInitialSpeed(d->stickedItem->xSpeed(),d->stickedItem->ySpeed());
            t.setAcceleration(xAcceleration,yAcceleration,d->attractingTime);
            if(d->stickedItem->accelerationRestTime()<=0)
            {
                     
                d->attracingState=StickPointPrivate::AttractedItem;
                d->stickedItem->setSpeed(0,0);
                 d->stickedItem->setAccleration(0,0,0);
                 d->stickedItem->freezeUntilNextLaunch();

              }
            break;
        }
        case StickPointPrivate::AttracingItem:
        {

            if(d->stickedItem->accelerationRestTime()<=0)
            {
                     
                d->attracingState=StickPointPrivate::AttractedItem;
                d->stickedItem->setSpeed(0,0);
                 d->stickedItem->setAccleration(0,0,0);
                d->stickedItem->setLaunchingChance(1);
              }
            break;
            ;
        }
        case StickPointPrivate::AttractedItem:
        {

            QPointF moveBy=scenePos()-d->stickedItem->scenePos();
            d->stickedItem->moveBy(moveBy.x(),moveBy.y());

            break;
        }
        case StickPointPrivate::StopAttracting:{
            if(not d->stickedItem->collidesWithItem(this))
                setStickedItem(nullptr);
        }



    }
    }
}



void StickPoint::_collide(AbstractInterativeItem *item, CollidingReason reason)
{
    Q_D(const StickPoint);
     
    if(d->stickedItem==nullptr)
    {
        AbstractProtagonist*p=qobject_cast<AbstractProtagonist*>(item);
        if(p!=nullptr){
             setStickedItem(p);
//            QPointF speed=QLineF(0,0,p->xSpeed(),p->ySpeed()).pointAt(0.5);
//            p->setSpeed(speed.x(),speed.y());

//              

        }
        attractStickedItem();
    }






}

void StickPoint::_stickedItemLaunch()
{
     Q_D(StickPoint);
    d->attracingState=StickPointPrivate::StopAttracting;
}

QVariant StickPoint::itemChange(GraphicsItemChange change, const QVariant &value)
{
    Q_D(StickPoint);
    switch (change) {
    case ItemPositionChange:
        if(d->attracingState!=StickPointPrivate::StopAttracting)
            d->attracingState=StickPointPrivate::UpdatingAttraction;
        attractStickedItem();

        break;
    case ItemPositionHasChanged:
        if(d->stickedItem)
            d->stickedItem->setPos(value.toPointF());
    default:
        break;

    }
    return AbstractInterativeItem::itemChange(change,value);

}
