#ifndef MYALGORITHM_H
#define MYALGORITHM_H
#include<global.h>
#include<algorithm>
#include<QList>
#include<QPointF>
#include<QRectF>
#define sortWithKey(Begin,End,Key)std::sort(Begin,End,[](decltype(Begin)a,decltype(Begin)b){return a->Key<b->Key;});
template<typename Container,typename RectType>
Container randPoints(const RectType&bound,qsizetype count)
{
    Container c;
    while(count>0)
    {
        c.push_back(typename Container::value_type(randInt(bound.left(),bound.right()),randInt(bound.top(),bound.bottom())));
        --count;
    }
    return c;
}
#endif // MYALGORITHM_H
