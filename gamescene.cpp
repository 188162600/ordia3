#include "gamescene.h"
#include"stickpoint.h"
#include"checkpoint.h"
#include<QPainterPath>
#include<QPropertyAnimation>
#include"rock.h"
#include<QBitmap>
#include"protagonist.h"
#include<QRegion>
#include"trajectoryindicator.h"
#include<QGraphicsSceneMouseEvent>
#include<QVector2D>
#include"private/qgraphicsscene_p.h"
#include"enemy.h"
//class GameScenePrivate
//{
//public:
//     QVector2D getAcceleration(qreal angelToMouse,qreal distanceToMouse)
//    {

//        return QVector2D(QLineF::fromPolar(std::min(distanceToMouse,qreal(150)),angelToMouse).p2()/100000);
//    };
//     qreal getStretchingIntensity(qreal distanceToMouse)
//    {
//
//        return std::min(distanceToMouse/5,protagonist->boundingRect().height()/4);
//    }
//    const static int indicatedTrajectoryLength=100;

//    inline GameScenePrivate():protagonist(nullptr),trajectoryIndicator(nullptr),gravity(0.001){};
//    AbstractProtagonist*protagonist;
//    TrajectoryIndicator*trajectoryIndicator;
//    qreal gravity;

//};

QPainterPath makeEllipseShaepe(const QRectF&rect){QPainterPath shape;shape.addEllipse(rect);return shape;};

void setUpStickPoint(StickPoint*stickPoint)
{
    static const QRectF rect(-20,-20,40,40);
    static const QPainterPath shape=makeEllipseShaepe(rect);
    stickPoint->setShape(shape);
}



struct StickPointAnimationActivator
{
    StickPointAnimationActivator(QPropertyAnimation*animation,const QPointF&start,const QPointF&end):animation(animation),start(start),end(end){};
    QPropertyAnimation*animation;
    QPointF start;
    QPointF end;


    void operator()(const QRectF&rect)
    {
        if(rect.contains(start) or rect.contains(end))

            animation->start();

        else

            animation->stop();


    }


};
void setUpMovableStickPoint(StickPoint*stickPoint,const QPointF&start,const QPointF&end,qreal speedPerMs)
{
    setUpStickPoint(stickPoint);
    QPropertyAnimation*animation=new QPropertyAnimation(stickPoint,"pos");
    animation->setDuration(QLineF(start,end).length()/speedPerMs*2);
 //
    animation->setStartValue(start);
    animation->setKeyValueAt(0.5,end);
    animation->setEndValue(start);
    animation->setLoopCount(-1);

    QObject::connect(stickPoint->scene(),&QGraphicsScene::sceneRectChanged,StickPointAnimationActivator(animation,start,end));


       animation->start();
       qDebug()<<animation->state();


}

void setUpCheckPoint(CheckPoint*checkPoint)
{
    static int v=0;
    qDebug()<<"check point"<<v<<checkPoint;
    static const QRectF rect(-25,-25,50,50);
    static const QPainterPath shape=makeEllipseShaepe(rect);
    checkPoint->setShape(shape);

}


//GameScene::GameScene(QObject *parent)
//    :GameScene(*new GameScenePrivate,parent)
//{

//}

//void GameScene::setProtagonist(AbstractProtagonist *p)
//{

//    addItem(p);
//    d->protagonist=p;

//}

void setUpLevel1Contents(AbstractProtagonist *p, QGraphicsScene *scene)
{
    scene->addPixmap(QPixmap(":images/decoration2.png"));
   // qDebug()<<"img"<<QPixmap(":images/decoration2.png");

    Rock*r=new Rock;

    r->setPen(QPen(Qt::black,3));
    r->setBrush(Qt::black);
    r->setShape(regionToPath(QRegion(QBitmap (":images/rocks2.png"))));
    qDebug()<<"img"<<QBitmap (":images/rocks2.png");
    qreal w=r->boundingRect().width(),h=r->boundingRect().height();


    Enemy*sticks=new Enemy;
    sticks->setShape(regionToPath(QRegion(QBitmap (":images/sticks3.png"))));
    qDebug()<<QBitmap (":images/sticks3.png");
    sticks->setBrush(QBrush(QColor(205,39,152)));
    scene->addItem(p);
    scene->addItem(r);
    scene->addItem(sticks);
    p->setPos( w* 0.5 ,h* 0.952-1);
    //QV;
    QObject::connect(p,&QGraphicsObject::yChanged,[=](){
        QRectF b=r->boundingRect();qreal limit= (r->y()+b.top()+b.height()*0.952);
        qDebug()<<limit<<b;
        if(p->y()> limit)
        {
            qDebug()<<p->xAcceleration()<<p->yAcceleration()<<p->xSpeed()<<p->ySpeed();
            p->setY(limit-1);
            p->setAccleration(0,0,0);
            p->setSpeed(0,0);
            p->freezeUntilNextLaunch();
            p->setLaunchingChance(1);
        };
    });
    p->setLaunchingChance(1);
    p->setGravity(0.0005);
    p->setCheckPoint(QPointF(w* 0.5 ,h* 0.96-1));


    const static qreal stickPointMoveSpeed=0.1;


   // p->stackBefore(nullptr);




    ;

 //   p->grabMouse();
    StickPoint*stickPoint=new StickPoint;
    stickPoint->setPos(QPointF(w* 0.5 ,h* 0.93));
    setUpStickPoint(stickPoint);
    scene->addItem(stickPoint);


    StickPoint*stickPoint1=new StickPoint;
    scene->addItem(stickPoint1);
    setUpMovableStickPoint(stickPoint1,QPointF(w* 0.496124 ,h* 0.0877784),QPointF(w* 0.49677 ,h* 0.111808 ),stickPointMoveSpeed);



    StickPoint*stickPoint2=new StickPoint;
    stickPoint2->setPos(w* 0.406331 ,h* 0.149384 );
    setUpStickPoint(stickPoint2);
    scene->addItem(stickPoint2);



    StickPoint*stickPoint3=new StickPoint;
    stickPoint3->setPos(w* 0.647933 ,h* 0.149307);
    setUpStickPoint(stickPoint3);
    scene->addItem(stickPoint3);



    StickPoint*stickPoint4=new StickPoint;
     scene->addItem(stickPoint4);
    setUpMovableStickPoint(stickPoint4,QPointF(w* 0.383721 ,h* 0.173873 ),QPointF(w* 0.630491 ,h* 0.175327),stickPointMoveSpeed);



    StickPoint*stickPoint5=new StickPoint;
    scene->addItem(stickPoint5);

    setUpMovableStickPoint(stickPoint5,QPointF(w* 0.381137 ,h* 0.206015 ),QPointF(w* 0.640827 ,h* 0.208617 ),stickPointMoveSpeed);



    StickPoint*stickPoint6=new StickPoint;
    stickPoint6->setPos(w* 0.596899 ,h* 0.231652 );//
    setUpStickPoint(stickPoint6);

    scene->addItem(stickPoint6);


    StickPoint*stickPoint7=new StickPoint;
    stickPoint7->setPos(w* 0.432171 ,h* 0.252392 );//
    setUpStickPoint(stickPoint7);
    scene->addItem(stickPoint7);



    StickPoint*stickPoint8=new StickPoint;
    scene->addItem(stickPoint8);
    setUpMovableStickPoint(stickPoint8,QPointF(w* 0.580749 ,h* 0.30711 ),QPointF(w* 0.638243 ,h* 0.281779),stickPointMoveSpeed);


    CheckPoint*CheckPoint1=new CheckPoint;
    CheckPoint1->setPos(w* 0.478036 ,h* 0.321573);
    setUpCheckPoint(CheckPoint1);
    scene->addItem(CheckPoint1);



    StickPoint*stickPoint9=new StickPoint;
    stickPoint9->setPos(w* 0.659561 ,h* 0.349124 );
    setUpStickPoint(stickPoint9);
    scene->addItem(stickPoint9);


    StickPoint*stickPoint10=new StickPoint;
    stickPoint10->setPos(w* 0.547804 ,h* 0.376138 );
    setUpStickPoint(stickPoint10);
    scene->addItem(stickPoint10);


    StickPoint*stickPoint11=new StickPoint;
    stickPoint11->setPos(w* 0.839147 ,h* 0.387924 );
    setUpStickPoint(stickPoint11);
    scene->addItem(stickPoint11);



    StickPoint*stickPoint12=new StickPoint;
    stickPoint12->setPos(w* 0.619509 ,h* 0.397796);
    setUpStickPoint(stickPoint12);
    scene->addItem(stickPoint12);


    StickPoint*stickPoint13=new StickPoint;
    stickPoint13->setPos(w* 0.771318 ,h* 0.419224 );
    setUpStickPoint(stickPoint13);
    scene->addItem(stickPoint13);



    StickPoint*stickPoint14=new StickPoint;
    stickPoint14->setPos(w* 0.70155 ,h* 0.4418);
    setUpStickPoint(stickPoint14);
    scene->addItem(stickPoint14);




    StickPoint*stickPoint15=new StickPoint;
    stickPoint15->setPos(w* 0.79522 ,h* 0.454886);
    setUpStickPoint(stickPoint15);
    scene->addItem(stickPoint15);



    StickPoint*stickPoint16=new StickPoint;
    stickPoint16->setPos(w* 0.596899 ,h* 0.475855 );
    setUpStickPoint(stickPoint16);
    scene->addItem(stickPoint16);




    StickPoint*stickPoint17=new StickPoint;
    stickPoint17->setPos(w* 0.479328 ,h* 0.499043 );
    setUpStickPoint(stickPoint17);
    scene->addItem(stickPoint17);



    StickPoint*stickPoint18=new StickPoint;
    stickPoint18->setPos(w* 0.640827 ,h* 0.533022);
    setUpStickPoint(stickPoint18);
    scene->addItem(stickPoint18);



    StickPoint*stickPoint19=new StickPoint;
    stickPoint19->setPos(w* 0.479974 ,h* 0.551772 );
    setUpStickPoint(stickPoint19);
    scene->addItem(stickPoint19);



    StickPoint*stickPoint20=new StickPoint;
    stickPoint20->setPos(w* 0.563307 ,h* 0.573659);
    setUpStickPoint(stickPoint20);
    scene->addItem(stickPoint20);
 //   stickPoint20->deleteLater();




    StickPoint*stickPoint21=new StickPoint;
    stickPoint21->setPos(w* 0.383075 ,h* 0.601592 );
    setUpStickPoint(stickPoint21);
    scene->addItem(stickPoint21);



    CheckPoint*CheckPoint2=new CheckPoint;
    CheckPoint2->setPos(w* 0.478036 ,h* 0.321573);
    setUpCheckPoint(CheckPoint2);
    scene->addItem(CheckPoint2);
   // CheckPoint2->deleteLater();


    StickPoint*stickPoint22=new StickPoint;
    stickPoint22->setPos(w* 0.49031 ,h* 0.626999 );
    setUpStickPoint(stickPoint22);
    scene->addItem(stickPoint22);



    StickPoint*stickPoint23=new StickPoint;
    stickPoint23->setPos(w* 0.478036 ,h* 0.646055);
    setUpStickPoint(stickPoint23);
    scene->addItem(stickPoint23);


    StickPoint*stickPoint24=new StickPoint;
    stickPoint24->setPos(w* 0.478036 ,h* 0.646055);
    setUpStickPoint(stickPoint24);
    scene->addItem(stickPoint24);


    StickPoint*stickPoint25=new StickPoint;
    stickPoint25->setPos(w* 0.478036 ,h* 0.646055);
    setUpStickPoint(stickPoint25);
    scene->addItem(stickPoint25);


    StickPoint*stickPoint26=new StickPoint;
    stickPoint26->setPos(w* 0.478036 ,h* 0.646055);
    setUpStickPoint(stickPoint26);
    scene->addItem(stickPoint26);



     StickPoint*stickPoint27=new StickPoint;
        stickPoint27->setPos( w* 0.482558 ,h* 0.655927);
        setUpStickPoint(stickPoint27);
        scene->addItem(stickPoint27);


     StickPoint*stickPoint28=new StickPoint;
        stickPoint28->setPos( w* 0.596253 ,h* 0.674371);
        setUpStickPoint(stickPoint28);
        scene->addItem(stickPoint28);



     StickPoint*stickPoint29=new StickPoint;
        stickPoint29->setPos( w* 0.470284 ,h* 0.687304 );
        setUpStickPoint(stickPoint29);
        scene->addItem(stickPoint29);


     StickPoint*stickPoint30=new StickPoint;
        stickPoint30->setPos( w* 0.460594 ,h* 0.712941);
        setUpStickPoint(stickPoint30);
        scene->addItem(stickPoint30);
       // stickPoint30->deleteLater();


     StickPoint*stickPoint31=new StickPoint;
        stickPoint31->setPos( w* 0.394703 ,h* 0.720211 );
        setUpStickPoint(stickPoint31);
        scene->addItem(stickPoint31);





     StickPoint*stickPoint32=new StickPoint;
        stickPoint32->setPos( w* 0.594315 ,h* 0.75021);
        setUpStickPoint(stickPoint32);
        scene->addItem(stickPoint32);


        StickPoint*moveableStickPoint5a1=new StickPoint;
           scene->addItem(moveableStickPoint5a1);
        setUpMovableStickPoint(moveableStickPoint5a1,QPointF(w* 0.613049 ,h* 0.760159),QPointF(w* 0.607235 ,h* 0.796969),stickPointMoveSpeed);

      //  moveableStickPoint5a1->deleteLater();

     StickPoint*stickPoint33=new StickPoint;
        stickPoint33->setPos(w* 0.436047 ,h* 0.804699  );
        setUpStickPoint(stickPoint33);
        scene->addItem(stickPoint33);


     StickPoint*stickPoint34=new StickPoint;
        stickPoint34->setPos( w* 0.499354 ,h* 0.827198);
        setUpStickPoint(stickPoint34);
        scene->addItem(stickPoint34);


     StickPoint*stickPoint35=new StickPoint;
        stickPoint35->setPos( w* 0.382429 ,h* 0.844494);
        setUpStickPoint(stickPoint35);
        scene->addItem(stickPoint35);


     StickPoint*stickPoint36=new StickPoint;
        stickPoint36->setPos( w* 0.654393 ,h* 0.860871);
        setUpStickPoint(stickPoint36);
        scene->addItem(stickPoint36);


     StickPoint*stickPoint37=new StickPoint;
        stickPoint37->setPos( w* 0.474806 ,h* 0.880233);
        setUpStickPoint(stickPoint37);
        scene->addItem(stickPoint37);


     StickPoint*stickPoint38=new StickPoint;
        stickPoint38->setPos( w* 0.427649 ,h* 0.903497);
        setUpStickPoint(stickPoint38);
        scene->addItem(stickPoint38);





}

//void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{

//}

//void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    //stick point 对launch

//    if(d->protagonist!=nullptr)
//    {
//        if(d->protagonist->launchingChance()>=1)
//        {
//            d->trajectoryIndicator->hide();
//            d->protagonist->stretchTail(0,0);
//            d->protagonist-> launch();
//        }

//    }
//}

//void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{

//    if(d->protagonist!=nullptr)
//    {
//        if(d->protagonist->launchingChance()>=1)
//        {
//            QPointF posInItem=d->protagonist->mapFromScene(event->scenePos());
//            QLineF line(0,0,posInItem.x(),posInItem.y());
//            qreal angle=line.angle();
//            qreal len=line.length();
//            if(d->protagonist->contains(posInItem))
//                d->trajectoryIndicator->hide();
//            else{
//                d->trajectoryIndicator->show();

//                d->trajectoryIndicator->setPos(d->protagonist->scenePos());
//                Trajectory2d t;

//                auto a=d->getAcceleration(angle+180,len);
//                t.setAcceleration(a.x(),a.y()-d->gravity,INT_MAX);
//                t.setInitialSpeed(0,0);
//                d->trajectoryIndicator->setTrajectory(t,GameScenePrivate::indicatedTrajectoryLength);
//                QGraphicsRectItem *item=new QGraphicsRectItem(d->trajectoryIndicator->boundingRect());
//                addItem(item);
//
//            }

//            d->protagonist->stretchTail(angle,d->getStretchingIntensity(len));
//  d->protagonist->update();

//        }
//    }
//}

//GameScene::GameScene(GameScenePrivate &dd, QObject *parent)
//    :QGraphicsScene(parent),d(&dd)
//{

//    d->trajectoryIndicator=new TrajectoryIndicator;
//    QPen pen;
//    qreal space=4;
//    pen.setDashPattern( QVector<qreal>({4,space}));
//    d->trajectoryIndicator->setPen(pen);
//    addItem(d->trajectoryIndicator);

//}

//GameScene::~GameScene()
//{
//    delete d->trajectoryIndicator;
//    delete d;
//}
