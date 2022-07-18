#ifndef MATH2D_H
#define MATH2D_H
#include<QLineF>
#include<QGraphicsScene>
#include<QtDebug>
#include<QPainterPath>
namespace Private {

}


template<typename Iterator>
void outlinePoints( Iterator begin,Iterator end,qreal distanceFromPoint)
{
    if(begin==end)
        return;
    auto next=begin;
    if(++next==end)
        return;
    QLineF lastLine(begin->x(),begin->y(),next->x(),next->y());
    lastLine.translate(QLineF::fromPolar(distanceFromPoint,lastLine.angle()-90).p2());
    QPointF newPos=lastLine.p1();
    begin->setX(newPos.x());begin->setY(newPos.y());
    while (true) {
        begin=next;
        ++next;
        if(next==end)
        {
            begin->setX(lastLine.x2());
            begin->setY(lastLine.y2());
            break;

        }

        QLineF nextLine(begin->x(),begin->y(),next->x(),next->y());
        nextLine.translate(QLineF::fromPolar(distanceFromPoint,nextLine.angle()-90).p2());
        ;
        QPointF newPos;
        if(lastLine.intersects(nextLine,&newPos)==QLineF::NoIntersection)
            lastLine.setP2(nextLine.p2());
        else{
            begin->setX(newPos.x());
            begin->setY(newPos.y());
            lastLine=nextLine;
        }

    }
}
//template<typename Iterator>
//Iterator walkPointForDistance(Iterator begin,Iterator end,qreal distance,bool*successed=nullptr)
//{
//    if(begin==end){
//        if(successed!=nullptr)
//            *successed=(distance!=0);
//    return begin;
//    }
//    qreal walked=0;
//    QPointF lastPoint(begin->x(),begin->y());
//    ++begin;
//    while(begin!=end)
//    {
//        distance+=QLineF (lastPoint.x(),lastPoint.y(),begin->x(),begin->y()).length();
//        if(walked>distance)
//        {
//            if(successed!=nullptr)
//                *successed=true;
//            return begin;
//        }
//        ++begin;

//    }
//    if(successed!=nullptr)
//        *successed=true;
//    return begin;

//};
struct BouncingInfo
{
    qreal bouncingAngle;
    QPointF bouncingPos;
    QPointF lastPosBeforeBouncing;

};
inline qreal normalizedAngle(qreal angle)
{
    if(angle<0)
        angle+=qCeil(qAbs(0-angle)/360)*360;
    else if(angle>360)
        angle-=qFloor(angle/360)*360;
    return angle;
};


BouncingInfo getBouncingInfo(const QLineF&motion,const QPainterPath&shape,const QPainterPath&obstacle,bool*bounced);

QPainterPath unitShapeWithSurfaceTension(const QPainterPath&shape1,const QPainterPath&shape2,qreal surfaceTension);;
QPainterPath addInertiaToShape(const QPainterPath&shape, const QPointF&inertia);



QPainterPath regionToPath(const QRegion &region);
qreal ellipseRadiusAtAngle(const QSizeF&size,qreal angle);
QPointF ellipisePointAtAngle(const QRectF&rect,qreal angle);
#endif // MATH2D_H
