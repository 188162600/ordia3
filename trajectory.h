#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include<Qt>
#include<QPointF>
#include<QVector>
#include<QSharedDataPointer>
namespace Private {
class Trajectory2dPrivate:public QSharedData
{
public:
    inline Trajectory2dPrivate(qreal xSpeed=0,qreal ySpeed=0,qreal xAcceleration=0,qreal yAcceleration=0,int accelerationDuration=0):
        xs(xSpeed),ys(ySpeed),xa(xAcceleration),ya(yAcceleration),accelerationDuration(accelerationDuration){};
    qreal xs,ys;
    qreal xa,ya;
    int accelerationDuration;
};

}
class Trajectory2dPrivate;
class Trajectory2d
{
public:
    Trajectory2d();
    void setInitialSpeed(qreal xSpeed,qreal ySpeed);
    void setSpeedFromAngle(qreal angle,qreal speed);
    void setAcceleration(qreal xAcceleration,qreal yAcceleration,int duration);
    void setAccelerationDuration(int duration);
    void setInitialXSpeed(qreal x);
    void setInitialXYpeed(qreal y);
    void setXAcceleration(qreal x);
    void setYAcceleration(qreal y);
    qreal xInitialSpeed()const;
    qreal yInitialSpeed()const;
    qreal xAcceleration()const;
    qreal yAcceleration()const;
    int accerationDuration()const;
    bool isNull()const;
    QPointF posAt(int time)const;
    QVector<QPointF>toPoints(int timeInterval, qreal length, bool testIsNull=true);
private:
    QSharedDataPointer<Private::Trajectory2dPrivate>d;

};

#endif // TRAJECTORY_H
