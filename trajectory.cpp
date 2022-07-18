#include "trajectory.h"
#include<QLineF>
#include<QSharedData>
#include<QDebug>

Trajectory2d::Trajectory2d()
    :d(new Private::Trajectory2dPrivate)
{

}

void Trajectory2d::setInitialSpeed(qreal xSpeed, qreal ySpeed)
{
    auto d_ptr=d.data();
    d_ptr->xs=xSpeed;
    d_ptr->ys=ySpeed;

}

void Trajectory2d::setSpeedFromAngle(qreal angle, qreal speed)
{
    auto line=QLineF::fromPolar(speed,angle);
    setInitialSpeed(line.x2(),line.y2());
}

void Trajectory2d::setAcceleration(qreal xAcceleration, qreal yAcceleration, int duration)
{
    auto d_ptr=d.data();
    d_ptr->xa=xAcceleration;
    d_ptr->ya=yAcceleration;
    d_ptr->accelerationDuration=duration;
}

void Trajectory2d::setAccelerationDuration(int duration)
{
     auto d_ptr=d.data();
     d_ptr->accelerationDuration=duration;
}

void Trajectory2d::setInitialXSpeed(qreal x)
{
     auto d_ptr=d.data();
     d_ptr->xs=x;
}

void Trajectory2d::setInitialXYpeed(qreal y)
{
    auto d_ptr=d.data();
    d_ptr->ys=y;
}

void Trajectory2d::setXAcceleration(qreal x)
{
    auto d_ptr=d.data();
    d_ptr->xa=x;
}

void Trajectory2d::setYAcceleration(qreal y)
{
    auto d_ptr=d.data();
    d_ptr->ya=y;
}

qreal Trajectory2d::xInitialSpeed() const
{
    return d->xs;
}

qreal Trajectory2d::yInitialSpeed() const
{
    return d->ys;
}

qreal Trajectory2d::xAcceleration() const
{
    return d->xa;
}

qreal Trajectory2d::yAcceleration() const
{
    return d->ya;
}

int Trajectory2d::accerationDuration() const
{
    return d->accelerationDuration;
}

bool Trajectory2d::isNull() const
{

    return ((d->xa==0 and d->ya==0)or d->accelerationDuration==0)
            and  d->ys==0  and  d->ys==0;
}

QPointF Trajectory2d::posAt(int time) const
{
     ;

    if(time>d->accelerationDuration)
    {
        ;
        return QPointF(d->xs*time+d->xa*d->accelerationDuration*d->accelerationDuration/2,
                       d->ys*time+d->ya*d->accelerationDuration*d->accelerationDuration/2);
    }
    return QPointF(d->xs*time+d->xa*time*time/2,
                   d->ys*time+d->ya*time*time/2);
}

QVector<QPointF> Trajectory2d::toPoints(int timeInterval, qreal length,bool testIsNull)//the implement is so bad but i have no time to do a good one
{
    if(testIsNull)
        if(isNull())
            return QVector<QPointF>();
    QVector<QPointF> points{QPointF(0,0)};
    int time=timeInterval;
    qreal currentLength=0;
    while (currentLength<length) {

        points.push_back(posAt(time));
        currentLength+=QLineF(*(points.end()-1),*(points.end()-2)).length();
        time+=timeInterval;

    };
    return points;
}
