#ifndef STICKPOINT_P_H
#define STICKPOINT_P_H
#include"private/abstractinterativeitem_p.h"
#include<QPen>
#include<QBrush>
class AbstractProtagonist;
class StickPointPrivate:public AbstractInterativeItemPrivate
{
public:
   enum AttracingState{NotAttracingItem,AttracingItem,AttractedItem,UpdatingAttraction,StopAttracting};
    StickPointPrivate():stickedItem(nullptr),attractingTime(300),attracingState(NotAttracingItem),pen(Qt::NoPen),brush(QColor(51, 240, 164)){};
    AbstractProtagonist *stickedItem;
    int attractingTime;
    AttracingState attracingState;
    //bool attractedItem;
    QRectF boundingRect;

    QPen pen;
    QBrush brush;
    QPainterPath shape;
    void updateBoundingRect();


};
#endif // STICKPOINT_P_H
