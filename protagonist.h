#ifndef PROTAGONIST_H
#define PROTAGONIST_H

#include<QGraphicsObject>
#include<QPen>
#include<QBrush>
#include<QSharedDataPointer>
#include"trajectory.h"
#include"global.h"
#include"trajectoryindicator.h"
#include"abstractinterativeitem.h"
#include<QVector2D>
//#include<functional>
#include<QGraphicsSceneEvent>
class AbstractProtagonistPrivate;
class ProtagonistPrivate;

class AbstractProtagonist:public AbstractInterativeItem
{
    Q_OBJECT
    friend class AbstractProtagonistPrivate;
public:
    AbstractProtagonist(QGraphicsItem *parent=nullptr);
    qreal gravity()const;
    qreal timeDilationFactor()const;
    int launchingChance()const;
    qreal xSpeed()const;
    qreal ySpeed()const;
    qreal xAcceleration()const;
    qreal yAcceleration()const;
    int accelerationRestTime()const;
    qreal speedChangeFactorOnBouncing()const;
    int restAcceleratingTime()const;
    TrajectoryIndicator*trajectoryIndicator()const;
public Q_SLOTS:
    virtual void stretchTail(qreal angle,qreal intensity)=0;
    virtual qreal intensityAfterDrag(qreal angle,qreal distance);
    virtual QVector2D potentialSpeedAfterDrag(qreal angle,qreal distance);
//    bool bounce(const QPainterPath&obstacle);
//    bool bounce(const QGraphicsItem*obstacle);
    void setGravity(qreal g);
    void setTrajectoryIndicator(TrajectoryIndicator*indicator);
    void setLaunchingChance(int c);
    virtual void setSpeed(qreal xSpeed,qreal ySpeed);
    virtual void setAccleration(qreal xAcceleration,qreal yAcceleration,int duration);

    void setTimeDilationFactor(qreal factor);
    void setCheckPoint(const QPointF&point);

    void spawn();
    void die();
    bool launch(int spentLaunchingChance=1);
    //void setMovable(bool enable);

    void setSpeedChangeFactorOnBouncing(qreal factor);
    void freezeUntilNextLaunch();
Q_SIGNALS:
    void shapeChanged(const QPainterPath&shape);
    void launchingChanceChanged(int newChance);
    void timeDilationFactorChanged(qreal factor);

    void launched();
    void trajectoryChanged(const Trajectory2d&trajectory);
     void checkPointChanged(const QPointF&trajectory);
    void died();
    void spawned();

//    void freezed();
//    void unfreezed();

protected:
    bool sceneEvent(QEvent*e)override{return AbstractInterativeItem::sceneEvent(e);}
    AbstractProtagonist(AbstractProtagonistPrivate&dd,QGraphicsItem*parent);
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)override;

    private:
    void setPosFollowingTrajectory();

    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,AbstractProtagonist);


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
   // void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

};

class Protagonist:public AbstractProtagonist
{
    Q_OBJECT
public:

    Protagonist(QGraphicsItem*parent=nullptr);
    Protagonist(const QRectF&bodyRect,QGraphicsItem*parent);
    // QGraphicsItem interface
public:
    QBrush eyeBrush()const;
     QBrush eyeBallBrush()const;
      QBrush bodyBrush()const;
      QPen eyePen()const;
       QPen eyeBallPen()const;
        QPen bodyPen()const;
        QRectF eyeRect()const;
         QRectF eyeBallRect()const;
          QRectF bodyRect()const;

    void setEyeBrush(const QBrush &brush);
    void setEyePen(const QPen&pen);
    void setEyeballBrush(const QBrush&brush);
    void setEyeBallPen(const QPen&pen);
    void setBodyBrush(const QBrush &brush);
    void setBodyPen(const QPen&pen);
    void setBodyRect(const QRectF&rect);
    void setEyeRect(const QRectF&rect);
    void setEyeballRect(const QRectF&rect);

    void closeEye(qreal degree,QFlags<Eyelid>usedEyelids={UpperEyelid,LowerEyelid});


    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;

private:
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,Protagonist);


    // QGraphicsItem interface
public:
    QPainterPath shape() const override;

    // AbstractProtagonist interface
public slots:
    void stretchTail(qreal angle, qreal intensity) override;

    // AbstractProtagonist interface
public slots:
    void setSpeed(qreal xSpeed, qreal ySpeed) override;
};

#endif // PROTAGONIST_H
