#ifndef ABSTRACTINTERATIVEITEM_P_H
#define ABSTRACTINTERATIVEITEM_P_H
#include"private/qgraphicsitem_p.h"
class AbstractInterativeItemPrivate:public QGraphicsItemPrivate
{
public:
    using QGraphicsItemPrivate::QGraphicsItemPrivate;
    bool checkCollison=true;
};

#endif // ABSTRACTINTERATIVEITEM_P_H
