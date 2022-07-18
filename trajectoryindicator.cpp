#include "trajectoryindicator.h"
#include<QPainter>
#include"private/qgraphicsitem_p.h"
#include<deque>
class TrajectoryIndicatorPrivate:public QGraphicsItemPrivate
{
public:
    TrajectoryIndicatorPrivate():trajectoryLength(0){};
//    struct Dash
//    {
//        QPointF firstPoint;
//        QPointF lastPoint;
//        qsizetype start;
//        qsizetype end;

//    };
    QPainterPath dashes;
    QRectF boundingRect;
    Trajectory2d trajectory;
    QPen pen;
    qreal trajectoryLength;
    void updateTrajectory();
};


TrajectoryIndicator::TrajectoryIndicator(QGraphicsItem *parent)
    :TrajectoryIndicator(*new TrajectoryIndicatorPrivate,parent)
{

}

void TrajectoryIndicator::setTrajectory(const Trajectory2d &t,qreal length)
{
    Q_D(TrajectoryIndicator);
    d->trajectory=t;
    d->trajectoryLength=length;
    d->updateTrajectory();
    prepareGeometryChange();
    update();
}

void TrajectoryIndicator::setTrajectory(const Trajectory2d &t)
{
    Q_D(TrajectoryIndicator);
    d->trajectory=t;
    d->updateTrajectory();
    prepareGeometryChange();
    update();
}

void TrajectoryIndicator::setTrajectoryLength(qreal length)
{

    Q_D(TrajectoryIndicator);
    d->trajectoryLength=length;
    d->updateTrajectory();
    prepareGeometryChange();
    update();
}

qreal TrajectoryIndicator::trajectoryLength() const
{
      Q_D(const TrajectoryIndicator);
    return d->trajectoryLength;
}

Trajectory2d TrajectoryIndicator::trajectory()
{
     Q_D(const TrajectoryIndicator);
    return d->trajectory;
}

QPen TrajectoryIndicator::pen() const
{
    Q_D(const TrajectoryIndicator);
    return d->pen;
}

void TrajectoryIndicator::setPen(const QPen &pen)
{
    Q_D(TrajectoryIndicator);
    d->pen=pen;
    d->updateTrajectory();
      prepareGeometryChange();
    update();
}



QRectF TrajectoryIndicator::boundingRect() const
{
     Q_D(const TrajectoryIndicator);
    return d->boundingRect;
}

QPainterPath TrajectoryIndicator::shape() const
{

     Q_D(const TrajectoryIndicator);
    QPen noDashPen=d->pen;
    noDashPen.setStyle(Qt::SolidLine);
    noDashPen.setDashOffset(0);
    return QPainterPathStroker(noDashPen).createStroke(d->dashes);
}

void TrajectoryIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(const TrajectoryIndicator);
    QPen noDashPen=d->pen;
    noDashPen.setStyle(Qt::SolidLine);
    noDashPen.setDashOffset(0);
     painter->setPen(noDashPen);
     painter->drawPath(d->dashes);
//    for(const auto&i:d->dashes)
//    {
//        QPointF lastPoint=i.firstPoint;
//        qsizetype index=0;
//        while(index<i.end)
//        {
//            painter->drawLine(lastPoint,d->points[i.start+index]);
//            lastPoint=d->points[i.start+index];
//        }
//        painter->drawLine(lastPoint,i.lastPoint);

//    }



}

TrajectoryIndicator::TrajectoryIndicator(TrajectoryIndicatorPrivate &d, QGraphicsItem *parent)
    :QGraphicsObject(d,parent)
{

}
//template<typename Container>
//static void addLineToPainterPath(QPainterPath*shape,const QLineF&line,const Container&dashPattern,qsizetype firstDashPattern=0,qsizetype*lastPaternIndex=nullptr)
//{
//    qreal length=line.length();
//    while (true) {
//        qreal newLength
//    }

//}
static void addPolylinesToPainterPath(QPainterPath*shape,const QVector<QPointF>&points)
{
    if(points.isEmpty())
        return;

    shape->moveTo(points[0]);
    for(qsizetype i=1;i<points.size();++i)
        shape->lineTo(points[i]);

    shape->moveTo(points[0]);

}
void TrajectoryIndicatorPrivate::updateTrajectory()
{
    dashes.clear();
    if(trajectory.isNull())
        return;
    QList<qreal>dashPattern=pen.dashPattern();
     
    const static int timeInterval=40;
     if(dashPattern.isEmpty())
     {
         ;
         addPolylinesToPainterPath(&dashes,trajectory.toPoints(timeInterval,trajectoryLength,false));
         qreal pad=pen.widthF()/2;

         boundingRect=dashes.boundingRect();
         //boundingRect=dashes.boundingRect().adjusted(-10,-10,10,10);
         boundingRect=dashes.boundingRect().adjusted(-pad,-pad,pad,pad);
         return;
     }

    int currentTime=0;
    qsizetype currentDashIndex;

    qreal restDistance=trajectoryLength;

    QLineF currentLine;
    qreal distanceToNextDash=pen.dashOffset();

    if(pen.dashOffset()>=0){

        currentDashIndex=0;
        while (true) {

            qreal newDistance=distanceToNextDash-dashPattern[currentDashIndex];

            if(newDistance<0)
                break;
            distanceToNextDash=newDistance;
            ++currentDashIndex;
            if(currentDashIndex>=dashPattern.length())
                currentDashIndex=0;
            // distanceToNextDash=dashPattern[currentDashIndex]-distanceToNextDash;
        }
        distanceToNextDash=dashPattern[currentDashIndex]-distanceToNextDash;
    }
    else{
        currentDashIndex=dashPattern.length()-1;

        while (true) {

            qreal newDistance=distanceToNextDash+dashPattern[currentDashIndex];

//             qDebug()<<"currentDashIndex"<<currentDashIndex
//                    <<"\nnew dis"<<newDistance
//                      <<"\ndistanceToNextDash" <<distanceToNextDash
//                   <<"\ndashPattern"<<dashPattern[currentDashIndex];

            distanceToNextDash=newDistance;
            --currentDashIndex;
            if(currentDashIndex<=0)
                currentDashIndex=dashPattern.length()-1;
            if(newDistance>0)
                break;

             //distanceToNextDash+=dashPattern[currentDashIndex]+distanceToNextDash;
        }
        //distanceToNextDash=dashPattern[currentDashIndex]+distanceToNextDash;
    }


    while (true) {
      //  qDebug()//<<"\ncurrent time"<<currentTime
        //        <<"\ncurrentDashIndex"<<currentDashIndex;
//              <<"\nrestDistance"<<restDistance
//             <<"\ncurrentLine len"<<currentLine.length()
//            <<"\ncurrentLine"<<currentLine
//            <<"\ndistanceToNextDash"<<distanceToNextDash
//           <<"\ndash"<<dashPattern[currentDashIndex];
        bool goToNextLine=false;
        bool dash=false;
        qreal lineLen=currentLine.length();
        if(lineLen>=distanceToNextDash){

            currentLine.setLength(distanceToNextDash);
            restDistance-=distanceToNextDash;
            dash=true;
             ;

        }
        if(lineLen<=distanceToNextDash){

            distanceToNextDash-=lineLen;
            restDistance-=lineLen;
            goToNextLine=true;
        }

//        qDebug()<<"goToNextLine"<<goToNextLine
//               <<"\ndash"<<dash;


       // distanceToNextDash-=lineLength;
        if(restDistance<=0){
            if(isEven(currentDashIndex)){
                currentLine.setLength(currentLine.length()+distanceToNextDash);
                dashes.lineTo(currentLine.p2());
            }
            break;
        }

        if(isEven(currentDashIndex)){
             ;
            dashes.lineTo(currentLine.p2());
        }
        else{
            ;
            dashes.moveTo(currentLine.p2());
        }



        if(goToNextLine)
        {
            currentTime+=timeInterval;
            currentLine=QLineF(currentLine.p2(),trajectory.posAt(currentTime));

        }
        if(dash)
        {
              currentLine=QLineF(currentLine.p2(),trajectory.posAt(currentTime));
            if(++currentDashIndex>=dashPattern.length())
                currentDashIndex=0;
            distanceToNextDash=dashPattern[currentDashIndex];

        }


    }
     ;

    qreal pad=pen.widthF()/2;
    boundingRect=dashes.boundingRect().adjusted(-pad,-pad,pad,pad);
     
}
//void TrajectoryIndicatorPrivate::updateTrajectory()
//{
//    dashes.clear();
//    QList<qreal>dashPattern=pen.dashPattern();
//     
//    const static int timeInterval=40;
//     if(dashPattern.isEmpty())
//     {
//         ;
//         addPolylinesToPainterPath(&dashes,trajectory.toPoints(timeInterval,trajectoryLength));
//         return;
//     }

//    int currentTime=timeInterval;
//    qsizetype currentDashIndex=0;

//    qreal restDistance=trajectoryLength;

//    QLineF currentLine;
//    qreal distanceToNextDash=pen.dashOffset();

//        while (true) {
//            qreal newDistance=distanceToNextDash-dashPattern[currentDashIndex];
//            if(newDistance<0)
//                break;
//            distanceToNextDash=newDistance;
//            ++currentDashIndex;
//            if(currentDashIndex>=dashPattern.length())
//                currentDashIndex=0;
//        }

//     
//    while (true) {
//        qDebug()<<"currentDashIndex"<<currentDashIndex
//              <<"restDistance"<<restDistance
//             <<"currentLine len"<<currentLine.length()
//            <<"\ncurrentLine"<<currentLine
//            <<"distanceToNextDash"<<distanceToNextDash
//           <<dashPattern[currentDashIndex];
//        bool goToNextLine=false;
//        if(currentLine.length()>distanceToNextDash){
//              
//             
//            currentLine.setLength(distanceToNextDash);
//            restDistance-=distanceToNextDash;
//             
//            distanceToNextDash=dashPattern[currentDashIndex];
//              

//        }
//        else{
//             
//            distanceToNextDash-=currentLine.length();
//            restDistance-=currentLine.length();
//            goToNextLine=true;

//        }


//       // distanceToNextDash-=lineLength;
//        if(restDistance<=0){
//            if(isEven(currentDashIndex)){
//                currentLine.setLength(currentLine.length()+distanceToNextDash);
//                dashes.lineTo(currentLine.p2());
//            }
//            break;
//        }

//        if(isEven(currentDashIndex))
//            dashes.lineTo(currentLine.p2());
//        else
//            dashes.moveTo(currentLine.p2());

//        ++currentDashIndex;
//        if(currentDashIndex>=dashPattern.length())
//            currentDashIndex=0;
//        if(goToNextLine)
//        {
//             
//            currentLine=QLineF(currentLine.p2(),trajectory.posAt(currentTime));
//            currentTime+=timeInterval;
//        }
//    }
//     

//    qreal pad=pen.widthF()/2;
//    boundingRect=dashes.boundingRect().adjusted(-pad,-pad,pad,pad);
//}
//void TrajectoryIndicatorPrivate::updateTrajectory()
//{
//    QList<qreal>dashPattern=pen.dashPattern();
//    Q_ASSERT(not dashPattern.isEmpty());
//    const static int timeInterval=40;
//    int currentTime=timeInterval;
//    qreal dashOffset=pen.dashOffset();
//    QLineF currentLine(QPointF(0,0),trajectory.posAt(currentTime));
//    qsizetype currentDashIndex=0;
//    qreal distanceToNextDash=dashOffset;
//    while (true) {
//        qreal newDistance=distanceToNextDash-dashPattern[currentDashIndex];
//        if(newDistance<0)
//            break;
//        distanceToNextDash=newDistance;
//        ++currentDashIndex;
//        if(currentDashIndex>=dashPattern.length())
//            currentDashIndex=0;
//    }
//    if(currentLine.length()>distance)
//        currentLine.setLength(distance);
//    dashes.moveTo(currentLine.p1());
//    while (true) {
//        qreal newDistance=distanceToNextDash-dashPattern[currentDashIndex];

//        if(newDistance<=0)
//            dashes.lineTo(currentLine.p2());
//        else;


//    }
//}
//void TrajectoryIndicatorPrivate::updateTrajectory()
//{
//    int timeInterval=40;
//    int currentTime=timeInterval;
//    qreal dashOffset=pen.dashOffset();
//    qreal distance=0;
//    QPointF lastPos(0,0);
//    QList<qreal>dp=pen.dashPattern();
//    std::deque dashPattern(dp.begin(),dp.end());
//    while(true)
//    {
//        QPointF currentPos=trajectory.posAt(currentTime);

//    };
//}
//void TrajectoryIndicatorPrivate::updateTrajectory()
//{
//    QList<qreal>dashPattern=pen.dashPattern();
//    Q_ASSERT(not dashPattern.isEmpty());
//    int timeInterval=40;
//    int currentTime=timeInterval;
//    qreal dashOffset=pen.dashOffset();
//    qreal distanceToNextDash=dashOffset;
//    qsizetype currentDashIndex=0;
//    qreal distance=0;
//    while (true) {
//        qreal newDistance=distanceToNextDash-dashPattern[currentDashIndex];
//        if(newDistance<0)
//            break;
//        distanceToNextDash=newDistance;
//        ++currentDashIndex;
//        if(currentDashIndex>=dashPattern.length())
//            currentDashIndex=0;
//    }
//    QPointF lastPoint;
//    qreal currentDistance=0;
//    while (true) {
//        QPointF currentPos=trajectory.posAt(currentTime);
//        qreal currentLineLength=QLineF(lastPoint,currentPos).length();
//        distanceToNextDash-=currentLineLength;
//    }

//}
/*
void TrajectoryIndicatorPrivate::updateTrajectory()
{
    int timeInterval=40;
    int currentTime=timeInterval;
    qreal dashOffset=pen.dashOffset();
    qreal distanceToNextDash=dashOffset;
    QList<qreal>dashPattern=pen.dashPattern();
    Q_ASSERT(not dashPattern.isEmpty());
    qsizetype currentDashIndex=0;
    qreal distance=0;
    while (true) {
        qreal newDistance=distanceToNextDash-dashPattern[currentDashIndex];
        if(newDistance<0)
            break;
        distanceToNextDash=newDistance;
        ++currentDashIndex;
        if(currentDashIndex>=dashPattern.length())
            currentDashIndex=0;
    }

    QPointF lastPoint;
    qreal currentDistance=0;
    while(true) {
        QPointF currentPos=trajectory.posAt(currentTime);
        qreal currentLineLength=QLineF(lastPoint,currentPos).length();
        distanceToNextDash-=currentLineLength;
        while (distanceToNextDash) {
            distance+=currentLineLength+distanceToNextDash;
            dashes.lineTo(currentPos);
            ++currentDashIndex;
            distanceToNextDash+=dashPattern[currentDashIndex];
        }
        if(distanceToNextDash<0)
        {
            distance+=currentLineLength+distanceToNextDash;
            dashes.lineTo(currentPos);
            ++currentDashIndex;
            distanceToNextDash+=dashPattern[currentDashIndex];

        }


        qreal newDistance=currentDistance+currentLineLength;
        if(newDistance<0)
            break;

        if(currentDashIndex>=dashPattern.length())
            currentDashIndex=0;
    }




}*/
//void TrajectoryIndicatorPrivate::updateTrajectory()
//{
//    int timeInterval=40;
//    int currentTime=timeInterval;
//    int currentDashIndex=0;
//    QList<qreal>dashPattern=  pen.dashPattern();
//    QPointF lastPoint(0,0);
//    qreal currentDistance=0;
//    qreal distanceToNextDash=0;
//    dashes.clear();
//    while (true) {
//        QPointF currentPos=trajectory.posAt(currentTime);

//        currentTime+=timeInterval;
//        QLineF line(lastPoint,currentPos);
//        if(distanceToNextDash<0);
//    }



//}
