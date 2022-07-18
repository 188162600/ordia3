#ifndef TRAJECTORYINDICATOR_H
#define TRAJECTORYINDICATOR_H

#include<abstractinterativeitem.h>
#include"trajectory.h"
#include"global.h"
#include<QPen>
class TrajectoryIndicatorPrivate;
class TrajectoryIndicator:public QGraphicsObject
{
public:
    TrajectoryIndicator(QGraphicsItem*parent=nullptr);
    void setTrajectory(const Trajectory2d&t, qreal length);
     void setTrajectory(const Trajectory2d&t);
     void setTrajectoryLength(qreal length);
     qreal trajectoryLength()const;
    Trajectory2d trajectory();
    QPen pen()const;
    void setPen(const QPen&pen);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,TrajectoryIndicator);
private Q_SLOTS:
    TrajectoryIndicator(TrajectoryIndicatorPrivate&d,QGraphicsItem*parent);


};

#endif // TRAJECTORYINDICATOR_H
