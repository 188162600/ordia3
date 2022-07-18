#include "protagonist.h"
#include<QPainter>
#include<QTimeLine>
#include"abstractinterativeitem.h"
#include"private/abstractprotagonist_p.h"
#include"rock.h"
#include"math2d.h"
#include<QGraphicsSceneMouseEvent>
class ProtagonistPrivate:public AbstractProtagonistPrivate
{
public:
//    Trajectory2d trajectory;
//    bool launched;
//    int frameChangedFromLastLuanch;
    ProtagonistPrivate():eyeClosingDegree(0),strechingTailAngle(0),stretchedDistance(0),bodyPen(Qt::NoPen),bodyBrush(QColor(51, 240, 164),Qt::SolidPattern),
        eyePen(Qt::NoPen),eyeBrush(Qt::white,Qt::SolidPattern),eyeBallPen(Qt::NoPen),eyeBallBrush(Qt::black,Qt::SolidPattern){};

    double eyeClosingDegree;
    QFlags<Eyelid>usedEyelidInClosingEye;
    qreal strechingTailAngle;
    qreal stretchedDistance;
    QRectF eyeBallRect;
    QRectF bodyRect;
    QRectF eyeRect;
    QPen bodyPen;
    QBrush bodyBrush;
    QPen eyePen;
    QBrush eyeBrush;
    QPen eyeBallPen;
    QBrush eyeBallBrush;
    QPainterPath bodyShape;
    void updateBodyShape();

};

Protagonist::Protagonist(QGraphicsItem *parent)
    :AbstractProtagonist(*new ProtagonistPrivate,parent)

{

}

Protagonist::Protagonist(const QRectF &bodyRect, QGraphicsItem *parent)
    :Protagonist(parent)
{
    Q_D( Protagonist);
    d->accelerationTimeLine.setUpdateInterval(10);
   setBodyRect(bodyRect);
   setEyeRect(bodyRect.adjusted(bodyRect.width()/7,bodyRect.height()/7,-bodyRect.width()/7,-bodyRect.height()/7));

   setEyeballRect(d->eyeRect.adjusted(eyeRect().width()/3-1,eyeRect().height()/3-1,-eyeRect().width()/3+1,-eyeRect().height()/3+1));

}

QBrush Protagonist::eyeBrush() const
{
    Q_D(const Protagonist);
    return d->eyeBrush;
}

QBrush Protagonist::eyeBallBrush() const
{
    Q_D(const Protagonist);
    return d->eyeBallBrush;
}

QBrush Protagonist::bodyBrush() const
{
    Q_D(const Protagonist);
    return d->bodyBrush;
}

QPen Protagonist::eyePen() const
{
    Q_D(const Protagonist);
    return d->eyePen;
}

QPen Protagonist::eyeBallPen() const
{
    Q_D(const Protagonist);
    return d->eyeBallPen;
}

QPen Protagonist::bodyPen() const
{

    Q_D(const Protagonist);
    return d->bodyPen;
}

QRectF Protagonist::eyeRect() const
{

    Q_D(const Protagonist);
    return d->eyeRect;
}

QRectF Protagonist::eyeBallRect() const
{
    Q_D(const Protagonist);
    return d->eyeBallRect;
}

QRectF Protagonist::bodyRect() const
{
    Q_D(const Protagonist);
    return d->bodyRect;
}

void Protagonist::setEyeBrush(const QBrush &brush)
{
    Q_D( Protagonist);
   d->eyeBrush=brush;
   update();

}

void Protagonist::setEyePen(const QPen &pen)
{

    Q_D( Protagonist);
   d->eyePen=pen;
   update();
}

void Protagonist::setEyeballBrush(const QBrush &brush)
{

    Q_D( Protagonist);
   d->eyeBallBrush=brush;
   update();
   ;

}

void Protagonist::setEyeBallPen(const QPen &pen)
{

    Q_D( Protagonist);
   d->eyeBallPen=pen;
   update();
}

void Protagonist::setBodyBrush(const QBrush &brush)
{

    Q_D(Protagonist);
   d->bodyBrush=brush;
   update();

}

void Protagonist::setBodyPen(const QPen &pen)
{

    Q_D( Protagonist);
   d->bodyPen=pen;
     prepareGeometryChange();
   update();

}

void Protagonist::setBodyRect(const QRectF &rect)
{

    Q_D( Protagonist);
   d->bodyRect=rect;
   d->updateBodyShape();
   Q_EMIT(shapeChanged(d->bodyShape));
     prepareGeometryChange();
   update();
}

void Protagonist::setEyeRect(const QRectF &rect)
{
    Q_D( Protagonist);
   d->eyeRect=rect;
   update();
}

void Protagonist::setEyeballRect(const QRectF &rect)
{
    Q_D( Protagonist);
   d->eyeBallRect=rect;
   update();

}

void Protagonist::closeEye(qreal degree, QFlags<Eyelid> usedEyelids)
{
    Q_D( Protagonist);
   d->eyeClosingDegree=degree;
   d->usedEyelidInClosingEye=usedEyelids;
   update();
}



QRectF Protagonist::boundingRect() const
{
    Q_D(const Protagonist);
    return d->bodyShape.boundingRect();
}



QPainterPath upperEyelidShape(const QRectF&rect,qreal closingDegree)
{
    QPainterPath shape;
    shape.moveTo(rect.left(),(rect.top()+rect.bottom())/2);
    shape.arcTo(rect.x(),rect.y()+rect.height()*closingDegree,rect.width(),rect.height()*(0.5-closingDegree)*2,180,-180);
    shape.arcTo(rect,0,180);
    return shape;
}
QPainterPath lowerEyelid(const QRectF&rect,qreal closingDegree)
{

    QPainterPath shape;
    shape.moveTo(rect.left(),(rect.top()+rect.bottom())/2);
   shape.arcTo(rect.x(),rect.y()+rect.height()*closingDegree,rect.width(),rect.height()*(0.5-closingDegree)*2,-180,180);
    shape.arcTo(rect,0,-180);
    return shape;
}
void paintUpperEyelid(QPainter*painter,const QRectF&rect,qreal closingDegree)
{
    //painter->drawRect(rect.x(),rect.y()+rect.height()*closingDegree,rect.width(),rect.height()*(0.5-closingDegree)*2);
    painter->drawPath(upperEyelidShape(rect,closingDegree));
}
void paintLowerEyelid(QPainter*painter,const QRectF&rect,qreal closingDegree)
{

     painter->drawPath(lowerEyelid(rect,closingDegree));
    // painter->drawRect(QRectF(rect.x(),rect.y()+rect.height()*closingDegree,rect.width(),rect.height()*(0.5-closingDegree)*2));
}
void Protagonist::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

     Q_D( Protagonist);
     ;

    //painter->save();

    painter->setBrush(d->bodyBrush);
    painter->setPen(d->bodyPen);
   //painter->setPen(QPen());
     ;

    painter->drawPath(d->bodyShape);

    painter->setBrush(d->eyeBrush);
    painter->setPen(d->eyePen);
    painter->drawEllipse(d->eyeRect);

    painter->setBrush(d->eyeBallBrush);
    painter->setPen(d->eyeBallPen);
    painter->drawEllipse(d->eyeBallRect);


    painter->setBrush(d->bodyBrush);
    painter->setPen(d->bodyPen);

    painter->setBrush(d->bodyBrush);
    painter->setPen(d->bodyPen);

     ;


    switch (d->usedEyelidInClosingEye&(UpperEyelid|LowerEyelid)) {
        case UpperEyelid:
        paintUpperEyelid(painter,d->eyeRect,d->eyeClosingDegree);
        break;
    case LowerEyelid:
        paintLowerEyelid(painter,d->eyeRect,d->eyeClosingDegree);
        break;
    case LowerEyelid|UpperEyelid:
        paintLowerEyelid(painter,d->eyeRect,d->eyeClosingDegree/2);
       paintUpperEyelid(painter,d->eyeRect,d->eyeClosingDegree/2);
        break;
    }

//    painter->setBrush(d->eyeBallBrush);
//    painter->setPen(d->eyeBallPen);
//    QPainterPath eyeBallShape;
//    eyeBallShape.addEllipse(d->eyeBallRect);
//    eyeBallShape-=eyelid;
//    // painter->setBrush(Qt::blue);
//    painter->drawPath(eyeBallShape);
//    painter->restore();

   // return QGraphicsObject::paint(painter,option,widget);

}

QPainterPath Protagonist::shape() const
{
    Q_D(const Protagonist);

    return d->bodyShape;
}

void Protagonist::stretchTail(qreal angle, qreal intensity)
{
     Q_D(Protagonist);
    d->strechingTailAngle=angle;
    d->stretchedDistance=intensity;
     shapeChanged(d->bodyShape);
    d->updateBodyShape();
      prepareGeometryChange();
      update();
}

void Protagonist::setSpeed(qreal xSpeed, qreal ySpeed)
{
    Q_D(const Protagonist);
    qreal angle=QLineF(0,0,xSpeed,ySpeed).angle();
   // line.setLength(ellipseRadiusAtAngle())
    qreal len=(ellipseRadiusAtAngle(d->eyeRect.size(),angle)-ellipseRadiusAtAngle(d->eyeBallRect.size(),angle))/2;
   QPointF eyeBallPos=QLineF::fromPolar(len,angle).p2();
   setEyeballRect(d->eyeBallRect.translated(eyeBallPos-d->eyeBallRect.center()));
    AbstractProtagonist::setSpeed(xSpeed,ySpeed);
}



AbstractProtagonist::AbstractProtagonist(QGraphicsItem*parent)
    :AbstractProtagonist(*new AbstractProtagonistPrivate,parent)
{

}

qreal AbstractProtagonist::gravity() const
{
    Q_D(const AbstractProtagonist);
    return d->gravity;
}




qreal AbstractProtagonist::timeDilationFactor() const
{
    Q_D(const AbstractProtagonist);
    return d->timeDilationFactor;
}

int AbstractProtagonist::launchingChance() const
{
    Q_D(const AbstractProtagonist);
    return d->launchingChance;
}

qreal AbstractProtagonist::xSpeed() const
{
    Q_D(const AbstractProtagonist);
    return d->xSpeed;
}

qreal AbstractProtagonist::ySpeed() const
{
    Q_D(const AbstractProtagonist);
    return d->ySpeed;
}

qreal AbstractProtagonist::xAcceleration() const
{
    Q_D(const AbstractProtagonist);
    return d->xAcceleration;
}

qreal AbstractProtagonist::yAcceleration() const
{
    Q_D(const AbstractProtagonist);
    return d->yAcceleration;
}

int AbstractProtagonist::accelerationRestTime() const
{
    Q_D(const AbstractProtagonist);
    return d->accelerationRestTime;
}

qreal AbstractProtagonist::speedChangeFactorOnBouncing() const
{
    Q_D(const AbstractProtagonist);
    return  d->speedChangeFactorOnBouncing;
}

int AbstractProtagonist::restAcceleratingTime() const
{
    Q_D(const AbstractProtagonist);
    return d->accelerationRestTime;
}

TrajectoryIndicator *AbstractProtagonist::trajectoryIndicator() const
{
    Q_D(const AbstractProtagonist);
    return d->trajectorIndicator;
}



qreal AbstractProtagonist::intensityAfterDrag(qreal angle, qreal distance)
{
    return std::min(boundingRect().height()/4,QLineF::fromPolar(distance,angle).length()/5);
}

QVector2D AbstractProtagonist::potentialSpeedAfterDrag(qreal angle, qreal distance)
{

    return QVector2D(QLineF::fromPolar(std::min(distance,(qreal)150),angle+180).p2()/210);
}

void AbstractProtagonist::setGravity(qreal g)
{
    Q_D( AbstractProtagonist);
     d->gravity=g;
}

void AbstractProtagonist::setTrajectoryIndicator(TrajectoryIndicator *indicator)
{
Q_D(AbstractProtagonist);
    if(d->trajectorIndicator)
        indicator->setParent(nullptr);
    d->trajectorIndicator=indicator;
    indicator->setParentItem(this);

}

void AbstractProtagonist::setLaunchingChance(int newChance)
{
   Q_D( AbstractProtagonist);
    d->launchingChance=std::max(newChance,0);
    Q_EMIT(launchingChanceChanged(newChance));
}

void AbstractProtagonist::setSpeed(qreal xSpeed, qreal ySpeed)
{
     Q_D( AbstractProtagonist);
    d->xSpeed=xSpeed;
    d->ySpeed=ySpeed;

}

void AbstractProtagonist::setAccleration(qreal xAcceleration, qreal yAcceleration, int duration)
{
    Q_D( AbstractProtagonist);
   d->xAcceleration=xAcceleration;
   d->yAcceleration=yAcceleration;
   d->accelerationRestTime=duration;
 //
   //d->accelerationTimeLine.setCurrentTime(0);
}


void AbstractProtagonist::setTimeDilationFactor(qreal factor)
{
     Q_D( AbstractProtagonist);
      d->timeDilationFactor=factor;
        Q_EMIT(timeDilationFactorChanged(factor));
}

void AbstractProtagonist::setCheckPoint(const QPointF &point)
{
   Q_D( AbstractProtagonist);
    d->checkPoint=point;
    Q_EMIT(checkPointChanged(point));
}

void AbstractProtagonist::spawn()
{
  Q_D( AbstractProtagonist);

    d->checkCollison=false;

    setPos(d->checkPoint);

    d->checkCollison=true;

    setLaunchingChance(1);

    //d->timeLine.stop();

    Q_EMIT(spawned());

}

void AbstractProtagonist::die()
{
    Q_D( AbstractProtagonist);
    setSpeed(0,0);
    setAccleration(0,0,0);
    d->accelerationTimeLine.stop();


    Q_EMIT(died());
    spawn();
}

bool AbstractProtagonist::launch(int spentLaunchingChance)
{
   Q_D( AbstractProtagonist);
    d->launchingChance-=spentLaunchingChance;
    if(d->launchingChance<0){
        d->launchingChance=0;
        return false;
    }
    switch (d->accelerationTimeLine.state()) {
    case QTimeLine::NotRunning:
        d->lastMovedTime=0;
        d->accelerationTimeLine.start();
        break;
    case QTimeLine::Paused:
        d->accelerationTimeLine.setPaused(false);
        break;
    default:
        break;

    }


    Q_EMIT(launched());
    return true;

}





void AbstractProtagonist::setSpeedChangeFactorOnBouncing(qreal factor)
{
    Q_D(AbstractProtagonist);
    d->speedChangeFactorOnBouncing=factor;
}

void AbstractProtagonist::freezeUntilNextLaunch()
{
    Q_D(AbstractProtagonist);
       d->accelerationTimeLine.setPaused(true);
}

AbstractProtagonist::AbstractProtagonist(AbstractProtagonistPrivate &dd,QGraphicsItem*parent)
    :AbstractInterativeItem(dd,parent)
{
    Q_D(AbstractProtagonist);
    d->accelerationTimeLine.setDuration(INT_MAX);
    //d->accelerationTimeLine.setCurrentTime(0);
    setFlag(ItemSendsGeometryChanges);


   // setPanelModality()

   //grabKeyboard();
    connect(&d->accelerationTimeLine,&QTimeLine::valueChanged,this,&AbstractProtagonist::setPosFollowingTrajectory);
    // connect(&d->timeLine,&QTimeLine::valueChanged,this,&AbstractProtagonist::hh);
      ;
}

QVariant AbstractProtagonist::itemChange(GraphicsItemChange change, const QVariant &value)
{
   //  return AbstractInterativeItem::itemChange(change,value);

    Q_D(AbstractProtagonist);
    switch (change) {

    case ItemPositionChange:
    {
        if(not d->checkCollison)
            break;

        if(d->freezed)
            return pos();
        if(scene()==nullptr)
            break;
        //for(auto i:collidingItems())

       QPainterPath itemShape=(shape().translated(scenePos()+value.toPointF()-pos()));
        for(auto i:scene()->items(itemShape))
        {
            //qDebug()<<i;
            if(qobject_cast<Rock*>(i->toGraphicsObject())!=nullptr)
            {


               // return AbstractInterativeItem::itemChange(change,pos());
                 ;
                bool bounced;

                auto bouncingInfo=getBouncingInfo(QLineF(pos(),value.toPointF())
                                                  ,((shape())),
                                                  i->mapToItem(this->parentItem(),(i->shape())),&bounced);//scene pos


                QLineF oldSpeed(0,0,d->xSpeed,d->ySpeed);
                QLineF speed=QLineF::fromPolar(oldSpeed.length()*0.5,bouncingInfo.bouncingAngle);

                QLineF copy=speed;copy.setLength(100);

                //HH::scene->addLine(copy,QPen(Qt::gray))->setPos(pos());

                //HH::scene->addLine(QLineF::fromPolar(100,bouncingInfo.bouncingAngle).translated(bouncingInfo.bouncingPos),QPen(Qt::GlobalColor::magenta))->setPos(pos());


                setSpeed(speed.x2(),speed.y2());
//                qreal originalMovedDistance=QLineF(pos(),value.toPointF()).length();
//                qreal movedDistance=QLineF(pos(),bouncingInfo.lastPosBeforeBouncing).length();
//                static int v=0;

//                 auto text1=HH::scene->addSimpleText(QString::number(v));
//                 text1->setPos(bouncingInfo.lastPosBeforeBouncing);
//                 text1->setPen(QPen(Qt::red));

//                // text1->s(Qt::red));
//                 auto text2=HH::scene->addSimpleText(QString::number(v+1));
//                  text2->setPos(value.toPointF());
//                  text2->setPen(QPen(Qt::blue));
//                  auto s=HH::scene->addPath(shape());
//                  s->setPos(bouncingInfo.lastPosBeforeBouncing);
//                  s->setPen(QPen(Qt::green));
//                  v+=2;

                  itemShape.translate(bouncingInfo.lastPosBeforeBouncing-value.toPointF());
                    qDebug()<<i;
                  if(i->collidesWithPath(itemShape,Qt::ItemSelectionMode::IntersectsItemShape))
                       return pos();

                return AbstractInterativeItem::itemChange(change,QVariant(bouncingInfo.lastPosBeforeBouncing));
               }

        }

//        if(d->accelerationTimeLine.currentFrame()>d->lastMovedTime)
//        {
//            d->xSpeed=(newPos.x()-x())/((d->accelerationTimeLine.currentTime()-d->lastMovedTime));
//             d->ySpeed=(newPos.y()-y())/((d->accelerationTimeLine.currentTime()-d->lastMovedTime));
//        }

        break;
    }

    default:
        break;
    }

    return AbstractInterativeItem::itemChange(change,value);
}

void AbstractProtagonist::setPosFollowingTrajectory()
{

    //TODO
     ;
    Q_D(AbstractProtagonist);

    Trajectory2d t;
    t.setInitialSpeed(d->xSpeed,d->ySpeed);
    t.setAcceleration(d->xAcceleration,d->yAcceleration,d->accelerationRestTime);
    int timeChanged=std::min( d->accelerationTimeLine.currentTime()-d->lastMovedTime,d->accelerationRestTime);
//
//
//    qDebug()<<"restTime"<<d->accelerationRestTime<<"timeChanged"<<timeChanged
//            <<"speed"<< d->xSpeed<< d->ySpeed<<d->xAcceleration<<d->yAcceleration
//           <<"lastMovedTime"<<d->lastMovedTime
//          <<"currentTime"<<d->accelerationTimeLine.currentTime()
//         <<"timeChanged"<<timeChanged;
//
    d->lastMovedTime=d->accelerationTimeLine.currentTime();
    d->accelerationRestTime-=timeChanged;
    if(d->accelerationRestTime>0)
    {
        setSpeed(d->xSpeed+timeChanged*d->xAcceleration,d->ySpeed+timeChanged*d->yAcceleration);

    }


//
//     qDebug()<<"speed"<< d->xSpeed<< d->ySpeed<<d->xAcceleration<<d->yAcceleration
//            <<"lastMovedTime"<<d->lastMovedTime
//           <<"currentTime"<<d->accelerationTimeLine.currentTime()
//          <<"timeChanged"<<timeChanged;
//
     ;
     QPointF move=t.posAt(timeChanged);
     moveBy(move.x(),move.y());
     //HH::scene->addRect(QRectF(scenePos(),QSizeF(3,3)));
   // setPos(pos()+t.posAt(timeChanged));
    ;


    // update();

}





void AbstractProtagonist::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    Q_D(AbstractProtagonist );
        qDebug()<<event;
    if(d->mousePressed==false)
        return;

    if(d->launchingChance<=0 )
        return;
    QLineF line(0,0,event->pos().x(),event->pos().y());
    qreal angle=line.angle();
    qreal length=line.length();
    QVector2D speed=potentialSpeedAfterDrag(angle,length);


    setSpeed(speed.x(),speed.y());

    setAccleration(0,d->gravity,INT_MAX);
    if(d->trajectorIndicator!=nullptr )//
    {
        if( contains(event->pos()))
        {
            d->trajectorIndicator->hide();
        }
        else{
             d->trajectorIndicator->show();
            Trajectory2d t;
            t.setInitialSpeed(d->xSpeed,d->ySpeed);

            t.setAcceleration(d->xAcceleration,d->yAcceleration,d->accelerationRestTime);

            d->trajectorIndicator->setTrajectory(t);

        }
    }


    stretchTail(angle,intensityAfterDrag(angle,length));
     AbstractInterativeItem::mouseMoveEvent(event);
}

void AbstractProtagonist::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug()<<event;
    Q_D(AbstractProtagonist);
    d->mousePressed=false;
        if(d->trajectorIndicator!=nullptr)
             d->trajectorIndicator->hide();

    stretchTail(0,0);
    if( not contains(event->pos())){
        launch();
        qDebug()<<"launch";
    }




    AbstractInterativeItem::mouseReleaseEvent(event);
}

void AbstractProtagonist::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event;

    Q_D(AbstractProtagonist);
    d->mousePressed=true;
//    if(d->trajectorIndicator!=nullptr)
//         d->trajectorIndicator->show();

    AbstractInterativeItem::mousePressEvent(event);
}





void ProtagonistPrivate::updateBodyShape()
{

    bodyShape.clear();
      bodyShape.addEllipse(bodyRect);
    if(stretchedDistance>0)
    {
        QPainterPath sub;
        qreal r=ellipseRadiusAtAngle(bodyRect.size(),strechingTailAngle);

        QPointF tail=QLineF::fromPolar(stretchedDistance+r,strechingTailAngle).p2()+bodyRect.center();
        //QRectF rect(d->bodyRect.right(),d->bodyRect.top()+d->bodyRect.height()/2,tail.x(),tail.y());
        QPointF translation=QLineF::fromPolar(r,strechingTailAngle-90).p2();

        sub.moveTo(bodyRect.center()+translation);
        sub.cubicTo(bodyRect.center()+translation/2,tail+translation,tail);
        sub.cubicTo(tail-translation, bodyRect.center()-translation/2,bodyRect.center()-translation);
        sub.lineTo(bodyRect.center()+translation);
        bodyShape+=sub-bodyShape;
        //bodyShape.closeSubpath();
     //  bodyShape+=sub;
     }


//      bodyShape.addEllipse(bodyRect);
//      bodyShape.addEllipse(bodyRect.translated(10,10));
//      bodyShape=bodyShape.simplified();

    //bodyShape.closeSubpath();
    //bodyShape=bodyShape.simplified();

}
