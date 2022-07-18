#ifndef ABSTRACTPROTAGONIST_P_H
#define ABSTRACTPROTAGONIST_P_H
#include"protagonist.h"
#include<QTimeLine>

#include"private/abstractinterativeitem_p.h"

class AbstractProtagonist;
class AbstractProtagonistPrivate:public AbstractInterativeItemPrivate
{
public:
    //Trajectory2d trajectory;
//    qreal xSpeed;
//    qreal ySpeed;
//    qreal xAcceleration;
//    qreal yAcceleration;
//    int accelleratingTime;
//    bool launched;
    AbstractProtagonistPrivate():mousePressed(false),gravity(0),speedChangeFactorOnBouncing(0.7),lastMovedTime(0),launchingChance(0),freezed(false),timeDilationFactor(1),xSpeed(0),ySpeed(0),
        xAcceleration(0),yAcceleration(0),accelerationRestTime(0),trajectorIndicator(nullptr){};
    bool mousePressed;
    qreal gravity;
    qreal speedChangeFactorOnBouncing;
    int lastMovedTime;
    //int frameChangedFromLastLuanch;
    int launchingChance;
    bool freezed;
    qreal timeDilationFactor;
    qreal xSpeed;
    qreal ySpeed;
    qreal xAcceleration;
    qreal yAcceleration;
    int accelerationRestTime;
    TrajectoryIndicator*trajectorIndicator;

   // Trajectory2d trajectory;
    QPointF checkPoint;

    QTimeLine accelerationTimeLine;

    static AbstractProtagonistPrivate*get(AbstractProtagonist*p){return p->d_func();};
    static const AbstractProtagonistPrivate*get(const AbstractProtagonist*p){return p->d_func();};


};
#endif // ABSTRACTPROTAGONIST_P_H
