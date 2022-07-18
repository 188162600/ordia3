#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include"stickpoint.h"

class AbstractProtagonist;
class CheckPointPrivate;
class CheckPoint:public StickPoint
{
    Q_OBJECT
public:

    QPainterPath shapeBeforeActivated()const;
    void setShapeBeforeActivated(const QPainterPath&shape);
    void setActivatingTime(int ms);
    void setBorder(qreal border);
    int activatingTime()const;
    qreal border()const;
    CheckPoint(QGraphicsItem*parent=nullptr);
private Q_SLOTS:
     void _activate(qreal progress);
     void _stopActivating();

private:
     CheckPoint(CheckPointPrivate&d,QGraphicsItem*parent);
     Q_DECLARE_PRIVATE_D(QGraphicsItem::d_ptr,CheckPoint);
    // void _collide(AbstractInterativeItem*item,AbstractInterativeItem::CollidingReason reason);

     // StickPoint interface
protected:
     void setStickedItem(AbstractProtagonist *item) override;
};

#endif // CHECKPOINT_H
