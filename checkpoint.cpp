#include "checkpoint.h"
#include<QTimeLine>
#include"protagonist.h"
#include"private/stickpoint_p.h"
#include<QPainterPathStroker>
class CheckPointPrivate:public StickPointPrivate
{
public:
    CheckPointPrivate():border(10){};
    QPainterPath shapeBeforeActivating;
    QRectF shapeBeforeActivatingBouncingRect;
    QTimeLine activatingTimeLine;
    qreal border;
    bool activationEnded()const{return activatingTimeLine.currentTime()>=activatingTimeLine.duration();};
    QPainterPath getShape()const
    {

        if(activationEnded())
        {
            QPainterPathStroker stroker;
            stroker.setWidth(border*2);
             return stroker.createStroke( stickedItem->shape());
        }
        if(activatingTimeLine.state()==QTimeLine::NotRunning or activatingTimeLine.currentValue()==0)
              return shapeBeforeActivating;



        QPainterPathStroker stroker;
        stroker.setWidth(border*2);
         QTransform transform;
         QTransform::quadToQuad(shapeBeforeActivatingBouncingRect,stickedItem->boundingRect(),transform);
         QPainterPath shape=stroker.createStroke( stickedItem->shape());

       //  t.scale(activatingTimeLine.currentValue(),activatingTimeLine.currentValue());

          return ((transform*activatingTimeLine.currentValue()).map(shape)+(shapeBeforeActivating));

    }

};

QPainterPath CheckPoint::shapeBeforeActivated() const
{
    Q_D(const CheckPoint);
   return d->shapeBeforeActivating;
}

void CheckPoint::setShapeBeforeActivated(const QPainterPath &shape)
{
     Q_D(CheckPoint);
    d->shapeBeforeActivating=shape;
    d->shapeBeforeActivatingBouncingRect=shape.boundingRect();
    setShape(d->getShape());

}

void CheckPoint::setActivatingTime(int ms)
{
    Q_D(CheckPoint);
    d->activatingTimeLine.setDuration(ms);
}

void CheckPoint::setBorder(qreal border)
{
       Q_D(CheckPoint);
    d->border=border;
    setShape(d->getShape());

    update();
}

int CheckPoint::activatingTime() const
{
       Q_D(const CheckPoint);
    return d->activatingTimeLine.duration();
}

qreal CheckPoint::border() const
{
    Q_D(const CheckPoint);
    return d->border;
}

CheckPoint::CheckPoint(QGraphicsItem *parent)
    :CheckPoint(*new CheckPointPrivate,parent)
{

}

void CheckPoint::_activate(qreal progress)
{
    Q_D(CheckPoint);

    setShape(d->getShape());

//    QPainterPath shape=stickedItem()->shape();
//    QTransform t;
//    t.scale(progress,progress);
//    setShape(shape|d->shapeBeforeActivating);
}

void CheckPoint::_stopActivating()
{
     Q_D(CheckPoint);
    setShape(d->getShape());
    disconnect(stickedItem(),&AbstractProtagonist::shapeChanged,this,&StickPoint::setShape);

}



CheckPoint::CheckPoint(CheckPointPrivate &d, QGraphicsItem *parent)
    :StickPoint(d,parent)
{
   setPen(QPen(QColor(51, 240, 164,100),3));
   setBrush(QColor(51, 240, 164,50));
}



void CheckPoint::setStickedItem(AbstractProtagonist *item)
{
    Q_D(CheckPoint);
    d->activatingTimeLine.setCurrentTime(0);
    qDebug()<<"setStickedItem"<<this<<"************************";

//    if(d->stickedItem)
//    {
//        disconnect(&d->activatingTimeLine,&QTimeLine::finished,this,&CheckPoint::_stopActivating);
//        disconnect(&d->activatingTimeLine,&QTimeLine::valueChanged,this,&CheckPoint::_activate);
//    }
    if(item!=nullptr){
        item->setCheckPoint(mapToItem(item->parentItem(),QPointF(0,0)));
         d->activatingTimeLine.start();
        connect(&d->activatingTimeLine,&QTimeLine::finished,this,&CheckPoint::_stopActivating);
        connect(&d->activatingTimeLine,&QTimeLine::valueChanged,this,&CheckPoint::_activate);
    }
    setShape(d->shapeBeforeActivating);
    StickPoint::setStickedItem(item);




}



