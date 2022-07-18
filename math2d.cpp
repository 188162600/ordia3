#include "math2d.h"
#include<QVarLengthArray>

BouncingInfo getBouncingInfo(const QLineF &motion, const QPainterPath &shape, const QPainterPath &obstacle, bool *bounced)
{
    static int times=0;
    ++times;

  //
    BouncingInfo info;
    QPainterPath intersection=shape.translated(motion.p2()).intersected(obstacle);

    if(intersection.isEmpty()){
        *bounced=false;
        return info;
    }

    //find the most left point index in each subPolygons
    qreal motionAngle=motion.angle();
    QTransform transform;transform.rotate(motionAngle);
    QList<QPolygonF> subPolygons=intersection.toSubpathPolygons(transform);
   // QTransform transform2;transform2.rotate(motionAngle);
 QList<qsizetype>mostLeftPointIndexes(subPolygons.size());
    QList<qsizetype>mostRightPointIndexes(subPolygons.size());
    for(qsizetype i=0;i<subPolygons.size();++i){
        qsizetype mostLeft=0;
        qsizetype mostRight=0;
         ;
        for(qsizetype i2=1;i2<subPolygons[i].size();++i2){
            ;
            if(subPolygons[i][i2].x()<subPolygons[i][mostLeft].x())
                mostLeft=i2;
            else if(subPolygons[i][i2].x()>subPolygons[i][mostRight].x())
                mostRight=i2;
        }
        mostLeftPointIndexes[i]=mostLeft;
        mostRightPointIndexes[i]=mostRight;

    }



    //find the most left polygon
    qsizetype mostLeftPolygonIndex=0,mostRightPolygonIndex=0;
    for(qsizetype i=1;i<subPolygons.size();++i)
    {
        if(subPolygons[i][mostLeftPointIndexes[i]].x()<subPolygons[mostLeftPolygonIndex][mostLeftPointIndexes[i]].x())
            mostLeftPolygonIndex=i;
        else if(subPolygons[i][mostRightPointIndexes[i]].x()>subPolygons[mostRightPolygonIndex][mostRightPointIndexes[i]].x())
            mostRightPolygonIndex=i;
    }


    //get bouncingPos and lastPosBeforeBouncing
    const QPolygonF&mostLeftPolygon=subPolygons.at(mostLeftPolygonIndex),mostRightPolygon=subPolygons.at(mostRightPolygonIndex);
    qsizetype mostLeftPointIndex=mostLeftPointIndexes[mostLeftPolygonIndex],mostRightPointIndex=mostRightPointIndexes[mostRightPolygonIndex];
    transform.reset();
    transform.rotate(-motionAngle);
    info.bouncingPos=transform.map(mostLeftPolygon[mostLeftPointIndex]);

    //  info.lastPosBeforeBouncing=info.bouncingPos;
    //HH::scene->addEllipse(QRectF(info.bouncingPos,QSizeF(10,10)),QPen(Qt::yellow));
   QLineF m=motion;

    m.setLength(m.length()+(mostLeftPolygon[mostLeftPointIndex].x()-mostRightPolygon[mostRightPointIndex].x())-3);
    info.lastPosBeforeBouncing=m.p2();



    //find where the 2 object collides
    qsizetype bouncingAt[3]{mostLeftPointIndex,mostLeftPointIndex,mostLeftPointIndex};
    for(qsizetype i=mostLeftPointIndex+1;true;++i)
    {
        if(mostLeftPolygon[mostLeftPointIndex]!=mostLeftPolygon[i]){
            bouncingAt[2]=i;
            break;
        }
        if(i>=mostLeftPolygon.size())
         {
            for(qsizetype i=0;i<mostLeftPointIndex;++i)
                if(mostLeftPolygon[mostLeftPointIndex]!=mostLeftPolygon[i]){
                    bouncingAt[2]=i;
                    break;
                }
            break;
        }



    }

    for(qsizetype i=mostLeftPointIndex-1;true;--i)
    {
        if(mostLeftPolygon[mostLeftPointIndex]!=mostLeftPolygon[i]){
            bouncingAt[0]=i;
            break;
        }
        if(i<=0)
        {
            for(qsizetype i=mostLeftPolygon.size()-1;i>mostLeftPointIndex;--i)
                if(mostLeftPolygon[mostLeftPointIndex]!=mostLeftPolygon[i]){
                    bouncingAt[0]=i;
                    break;
                }
            break;
        }

  }

 //   HH::scene->addLine(transform.map(line3),QPen(Qt::green));
//


    //find the angle of the first line in obstacle that collide the object
    qreal collidingLineAngle;

    if(mostLeftPolygon[bouncingAt[0]].x()<mostLeftPolygon[bouncingAt[2]].x())
        collidingLineAngle=QLineF(mostLeftPolygon[bouncingAt[1]],mostLeftPolygon[bouncingAt[2]]).angle();
    else
        collidingLineAngle=QLineF(mostLeftPolygon[bouncingAt[1]],mostLeftPolygon[bouncingAt[0]]).angle();

    qreal bouncingAngle=std::min(collidingLineAngle,normalizedAngle(collidingLineAngle-180))*2+motionAngle;

    info.bouncingAngle=bouncingAngle;
    return info;





}

//BouncingInfo getBouncingInfo(const QLineF &motion, const QPainterPath &shape, const QPainterPath &obstacle, bool *bounced)
//{
//    static int times=0;
//    ++times;
//
//    BouncingInfo info;
//    QPainterPath intersection=shape.translated(motion.p2()).intersected(obstacle);
//    if(intersection.isEmpty()){
//        *bounced=false;
//        return info;
//    }

//    //find the most left point index in each subPolygons
//    qreal motionAngle=motion.angle();
//    QTransform transform;transform.rotate(motionAngle);
//    QList<QPolygonF> subPolygons=intersection.toSubpathPolygons(transform);
//    QTransform transform2;transform2.rotate(motionAngle);
//
//    ;
//    QList<qsizetype>mostLeftPointIndexes(subPolygons.size());
//    QList<qsizetype>mostRightPointIndexes(subPolygons.size());
//    for(qsizetype i=0;i<subPolygons.size();++i){
//        qsizetype mostLeft=0;
//        qsizetype mostRight=0;
//         ;
//        for(qsizetype i2=1;i2<subPolygons[i].size();++i2){
//            ;
//            if(subPolygons[i][i2].x()<subPolygons[i][mostLeft].x())
//                mostLeft=i2;
//            else if(subPolygons[i][i2].x()>subPolygons[i][mostRight].x())
//                mostRight=i2;
//        }
//        mostLeftPointIndexes[i]=mostLeft;
//        mostRightPointIndexes[i]=mostRight;
//        qDebug()<<"mostLeft"<<subPolygons[i][mostLeftPointIndexes[i]]
//               <<"mostRight"<<subPolygons[i][mostRightPointIndexes[i]]
//                <<mostLeftPointIndexes[i]<<mostRightPointIndexes[i];
//    }



//    //find the most left polygon
//    qsizetype mostLeftPolygonIndex=0,mostRightPolygonIndex=0;
//    for(qsizetype i=1;i<subPolygons.size();++i)
//    {
//        if(subPolygons[i][mostLeftPointIndexes[i]].x()<subPolygons[mostLeftPolygonIndex][mostLeftPointIndexes[i]].x())
//            mostLeftPolygonIndex=i;
//        else if(subPolygons[i][mostRightPointIndexes[i]].x()>subPolygons[mostRightPolygonIndex][mostRightPointIndexes[i]].x())
//            mostRightPolygonIndex=i;
//    }


//    //get bouncingPos and lastPosBeforeBouncing
//    const QPolygonF&mostLeftPolygon=subPolygons.at(mostLeftPolygonIndex),mostRightPolygon=subPolygons.at(mostRightPolygonIndex);
//    HH::scene->addPolygon(mostLeftPolygon,QPen(Qt::red));
//    qsizetype mostLeftPointIndex=mostLeftPointIndexes[mostLeftPolygonIndex],mostRightPointIndex=mostRightPointIndexes[mostRightPolygonIndex];
//    transform.reset();
//    transform.rotate(-motionAngle);
//    info.bouncingPos=transform.map(mostLeftPolygon[mostLeftPointIndex]);

//     ;
//
//    QLineF m=motion;

//    m.setLength(m.length()+(mostLeftPolygon[mostLeftPointIndex].x()-mostRightPolygon[mostRightPointIndex].x())-10);
//    info.lastPosBeforeBouncing=m.p2();
//
//     ;



//    //find where the 2 object collides
//    qsizetype bouncingAt[3]{mostLeftPointIndex,mostLeftPointIndex,mostLeftPointIndex};
//    for(qsizetype i=mostLeftPointIndex+1;true;++i)
//    {
//        if(mostLeftPolygon[mostLeftPointIndex]!=mostLeftPolygon[i]){
//            bouncingAt[2]=i;
//            break;
//        }
//        if(i>=mostLeftPolygon.size())
//         {
//            for(qsizetype i=0;i<mostLeftPointIndex;++i)
//                if(mostLeftPolygon[mostLeftPointIndex]!=mostLeftPolygon[i]){
//                    bouncingAt[2]=i;
//                    break;
//                }
//            break;
//        }
//

//    }

//    for(qsizetype i=mostLeftPointIndex-1;true;--i)
//    {
//        if(mostLeftPolygon[mostLeftPointIndex]!=mostLeftPolygon[i]){
//            bouncingAt[0]=i;
//            break;
//        }
//        if(i<=0)
//        {
//            for(qsizetype i=mostLeftPolygon.size()-1;i>mostLeftPointIndex;--i)
//                if(mostLeftPolygon[mostLeftPointIndex]!=mostLeftPolygon[i]){
//                    bouncingAt[0]=i;
//                    break;
//                }
//            break;
//        }

//  }


//    //find the angle of the first line in obstacle that collide the object
//    qreal collidingLineAngle;
//    if(mostLeftPolygon[bouncingAt[0]].x()<mostLeftPolygon[bouncingAt[2]].x())
//    {
//        collidingLineAngle=QLineF(mostLeftPolygon[bouncingAt[1]],mostLeftPolygon[bouncingAt[2]]).angle();
//       //  HH::scene->addLine(QLineF(mostLeftPolygon[bouncingAt[1]],mostLeftPolygon[bouncingAt[2]]));
//    }
//    else
//    {
//        collidingLineAngle=QLineF(mostLeftPolygon[bouncingAt[1]],mostLeftPolygon[bouncingAt[0]]).angle();
//      //   HH::scene->addLine(QLineF(mostLeftPolygon[bouncingAt[1]],mostLeftPolygon[bouncingAt[0]]));
//    }

//    QLineF line=QLineF::fromPolar(100,std::min(collidingLineAngle,normalizedAngle(collidingLineAngle-180))*2).translated(mostLeftPolygon[bouncingAt[1]]);
//    QLineF line2=QLineF::fromPolar(100,std::min(collidingLineAngle,collidingLineAngle)).translated(mostLeftPolygon[bouncingAt[1]]);

//    HH::scene->addLine(line);
//     HH::scene->addLine((line2));
//    HH::scene->addLine(transform.map(line));
//   HH::scene->addLine(transform.map(line2));
//    qreal bouncingAngle=std::min(collidingLineAngle,normalizedAngle(collidingLineAngle-180))*2+motionAngle;
//
//    info.bouncingAngle=bouncingAngle;
//    return info;





//}

QPainterPath unitPainterPathWithSurfaceTension(const QPainterPath &shape1, const QPainterPath &shape2, qreal surfaceTension)
{
    return shape1|shape2;
}

QPainterPath addInertiaToShape(const QPainterPath &shape, const QPointF &inertia)
{
    return shape;
}

struct Segment
{
    Segment() {}
    Segment(const QPoint &p)
        : added(false)
        , point(p)
    {
    }

    int left() const
    {
        return qMin(point.x(), next->point.x());
    }

    int right() const
    {
        return qMax(point.x(), next->point.x());
    }

    bool overlaps(const Segment &other) const
    {
        return left() < other.right() && other.left() < right();
    }

    void connect(Segment &other)
    {
        next = &other;
        other.prev = this;

        horizontal = (point.y() == other.point.y());
    }

    void merge(Segment &other)
    {
        if (right() <= other.right()) {
            QPoint p = other.point;
            Segment *oprev = other.prev;

            other.point = point;
            other.prev = prev;
            prev->next = &other;

            point = p;
            prev = oprev;
            oprev->next = this;
        } else {
            Segment *onext = other.next;
            other.next = next;
            next->prev = &other;

            next = onext;
            next->prev = this;
        }
    }

    int horizontal : 1;
    int added : 1;

    QPoint point;
    Segment *prev;
    Segment *next;
};
void mergeSegments(Segment *a, int na, Segment *b, int nb)
{
    int i = 0;
    int j = 0;

    while (i != na && j != nb) {
        Segment &sa = a[i];
        Segment &sb = b[j];
        const int ra = sa.right();
        const int rb = sb.right();
        if (sa.overlaps(sb))
            sa.merge(sb);
        i += (rb >= ra);
        j += (ra >= rb);
    }
}

void addSegmentsToPath(Segment *segment, QPainterPath &path)
{
    Segment *current = segment;
    path.moveTo(current->point);

    current->added = true;

    Segment *last = current;
    current = current->next;
    while (current != segment) {
        if (current->horizontal != last->horizontal)
            path.lineTo(current->point);
        current->added = true;
        last = current;
        current = current->next;
    }
}

QPainterPath regionToPath(const QRegion &region)
{
    QPainterPath result;
    if (region.rectCount() == 1) {
        result.addRect(region.boundingRect());
        return result;
    }

    auto rect = region.begin();
    const auto end = region.end();

    QVarLengthArray<Segment> segments;
    segments.resize(4 * (end - rect));

    int lastRowSegmentCount = 0;
    Segment *lastRowSegments = nullptr;

    int lastSegment = 0;
    int lastY = 0;
    while (rect != end) {
        const int y = rect[0].y();
        int count = 0;
        while (&rect[count] != end && rect[count].y() == y)
            ++count;

        for (int i = 0; i < count; ++i) {
            int offset = lastSegment + i;
            segments[offset] = Segment(rect[i].topLeft());
            segments[offset += count] = Segment(rect[i].topRight() + QPoint(1, 0));
            segments[offset += count] = Segment(rect[i].bottomRight() + QPoint(1, 1));
            segments[offset += count] = Segment(rect[i].bottomLeft() + QPoint(0, 1));

            offset = lastSegment + i;
            for (int j = 0; j < 4; ++j)
                segments[offset + j * count].connect(segments[offset + ((j + 1) % 4) * count]);
        }

        if (lastRowSegments && lastY == y)
            mergeSegments(lastRowSegments, lastRowSegmentCount, &segments[lastSegment], count);

        lastRowSegments = &segments[lastSegment + 2 * count];
        lastRowSegmentCount = count;
        lastSegment += 4 * count;
        lastY = y + rect[0].height();
        rect += count;
    }

    for (int i = 0; i < lastSegment; ++i) {
        Segment *segment = &segments[i];
        if (!segment->added)
            addSegmentsToPath(segment, result);
    }

    return result;
}

qreal ellipseRadiusAtAngle(const QSizeF&size,qreal angle)
{
    qreal A=size.width()/2;
    qreal B=size.height()/2;
    if(qFuzzyCompare(angle,0))
        return  A;
    else if(qFuzzyCompare(angle,90))
        return  B;
    else if(qFuzzyCompare(angle,180))
        return  A;
    else if(qFuzzyCompare(angle,270))
        return  B;
    qreal radian=qDegreesToRadians(angle);
    return A*B/qSqrt(qPow(A*sin(radian),2)+qPow(B*cos(radian),2));
}
QPointF ellipisePointAtAngle(const QRectF&rect,qreal angle)
{
    return rect.center()+QLineF::fromPolar(ellipseRadiusAtAngle(rect.size(),angle),angle).p2();

}
