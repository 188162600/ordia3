
#include <QApplication>
#include<QGraphicsView>
#include<QAbstractItemView>
#include<protagonist.h>
#include<trajectory.h>
#include<math2d.h>
#include"spikes.h"
#include<rock.h>
#include"checkpoint.h"
#include<trajectoryindicator.h>
#include<QPicture>
#include<QGraphicsSceneMouseEvent>
#include"gamescene.h"
#include<QMessageBox>
#include<QPushButton>
#include<QGraphicsPixmapItem>


//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QGraphicsScene scene;
//    HH::scene=&scene;
//    QGraphicsView view(&scene);

//    Protagonist p(QRectF(-10,-10,20,20),nullptr);
//   // p.setPos(200,200);
//    p.setAccleration(-3.354e-05,-0.000449413,1000);
//    p.setSpeed(0.01,0.2422);
//    Trajectory2d t;
//    t.setInitialSpeed(p.xSpeed(),p.ySpeed());
//    t.setAcceleration(p.xAcceleration(),p.yAcceleration(),1000);

//    scene.addPolygon(t.toPoints(25,500));
//     ;
//   scene.addItem(&p);
//    p.launch();
//    view.show();


//    return a.exec();


//}

/////////AbstractProtagonist::setPosFollowingTrajectory有问题
#include <QGraphicsProxyWidget>
#include<QHash>
#include<QImage>
#include <QTimeLine>
#include<QVariantAnimation>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // a joke
  //  qDebug()<<QLineF(0,0,0,0).angle();
     QMessageBox box(QMessageBox::Icon::Information,"Info","wow you clicked i quit. I felt so sad because you want me to get 0 :(");
    qDebug()<<box.windowFlags();
    box.setWindowFlag(Qt::WindowCloseButtonHint,false);
    QMessageBox box1(QMessageBox::Icon::Information,"","As I know you would not win the game. Quit the game");
   // box1.setWindowFlag(Qt::WindowCloseButtonHint,false);
   // box.setEscapeButton(QMessageBox::Close);
    QMessageBox box2(QMessageBox::Icon::Information,"","no no no dont click cancel");
  // box1.setEscapeButton(QMessageBox::Cancel);
    box2.setWindowFlag(Qt::WindowCloseButtonHint,false);
    QMessageBox box3(QMessageBox::Icon::Information,"","the close button is fake");
    box3.setWindowFlag(Qt::WindowCloseButtonHint,false);
    QObject::connect(box1.addButton("I quit",QMessageBox::ButtonRole::AcceptRole),
                     &QPushButton::clicked,&box,&QWidget::show);
    QObject::connect(box1.addButton("cencel",QMessageBox::ButtonRole::AcceptRole),
                     &QPushButton::clicked,&box2,&QWidget::show);
    QObject::connect(&box1,&QMessageBox::rejected,&box3,&QMessageBox::show);
   // QWidget::close
     box1.show();

    QObject::connect(box2.addButton("I quit",QMessageBox::AcceptRole),
                     &QPushButton::clicked,&box,&QWidget::show);
    QObject::connect(box2.addButton(QMessageBox::Close),
                     &QPushButton::clicked,&box3,&QWidget::show);
  QObject::connect(&box2,&QMessageBox::rejected,&box3,&QMessageBox::show);


  QObject::connect(box3.addButton("I quit",QMessageBox::AcceptRole),
                   &QPushButton::clicked,&box,&QWidget::show);
  QObject::connect(box3.addButton(QMessageBox::Close),
                   &QPushButton::clicked,&box3,&QWidget::show);
    QObject::connect(&box3,&QMessageBox::rejected,&box3,&QMessageBox::show);

   QObject::connect(&box,&QDialog::reject,&box,&QWidget::show);
    //



    QGraphicsScene scene;

    QGraphicsView view;
    view.setScene(&scene);
    view.show();
    view.showFullScreen();



    Protagonist p(QRectF(-20,-20,40,40),nullptr);
    TrajectoryIndicator indicator;
    QPen pen(QColor(51, 240, 164),3);
    pen.setDashPattern({10,10});
    pen.setCapStyle(Qt::RoundCap);
    indicator.setTrajectoryLength(150);
    indicator.setPen(pen);

    p.setTrajectoryIndicator(&indicator);
    p.setLaunchingChance(100);
    p.setGravity(0.0003);
    setUpLevel1Contents(&p,&scene);

    QPixmap pixmap(":images/main page.png");
    qDebug()<<scene.width()<<pixmap.rect();

    QGraphicsPixmapItem*pixmapItem= scene.addPixmap( pixmap.scaled(view.width(),view.height(),Qt::AspectRatioMode::KeepAspectRatioByExpanding));
    qDebug()<<pixmapItem->boundingRect()<<scene.width()<<scene.height()<<view.rect();
   // view.centerOn(p.pos());
    QPushButton goLevel1;
    goLevel1.setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsProxyWidget*widget= scene.addWidget(&goLevel1);
  //  widget->setPalette(QPalette(Qt::transparent,Qt::transparent,Qt::transparent,Qt::transparent,Qt::transparent,Qt::transparent,Qt::transparent,Qt::transparent,Qt::transparent));
    widget->setPos(scene.width()*0.42,scene.height()*0.143);
    //widget->setZValue(1);
    QPixmap icon(":images/lv1 entrance.png");
   // QIcon icon(":images/lv1 entrance.png");
      goLevel1.setIconSize(icon.size());
      goLevel1.setStyleSheet("border:0");
      qDebug()<<icon.rect()<<icon.mask().rect();
    goLevel1.setIcon(icon);
   goLevel1.setMask(icon.mask());
    view.centerOn(0,pixmapItem->boundingRect().height()-view.height()/2);
    QVariantAnimation ani;
    ani.setStartValue(QPointF(0,pixmapItem->boundingRect().height()-view.height()/2));
    ani.setEndValue(QPointF(0,pixmapItem->boundingRect().height()-view.height()/2-scene.height()*0.1));
    ani.setDuration(5000);
    QObject::connect(&box,&QMessageBox::finished,&ani,[&](){;ani.start();});
    QObject::connect(&ani,&QVariantAnimation::valueChanged,[&](const QVariant&v){view.centerOn(v.toPointF());});
  //  p.grabMouse();
    QObject::connect(&goLevel1,&QPushButton::clicked,[&](){
         view.centerOn(p.pos());
        widget->hide();
        pixmapItem->hide();
        p.grabMouse();


    });


   QObject::connect(&p,&Protagonist::posChanged,&view,[&](const QPointF&pos){
       view.centerOn(p.pos());

   });
   QTimeLine timeLine;
   QObject::connect(&p,&Protagonist::died,[&]()
   {
       auto rect=scene.addRect(scene.sceneRect());
       rect->setBrush(Qt::black);
       rect->show();
       QObject::connect(&timeLine,&QTimeLine::valueChanged,[=](qreal value)
       {
           qDebug()<<value;
           QBrush b=rect->brush();
           QColor c=b.color();
           c.setAlphaF(1-value);
           b.setColor(c);
            qDebug()<<b;
           rect->setBrush(b);
       });
       QObject::connect(&timeLine,&QTimeLine::stop,[&]()
       {
           scene.removeItem(rect);
       });
       timeLine.start();




   });
   QObject::connect(&goLevel1,&QPushButton::clicked,[&]()
   {
       auto rect=scene.addRect(scene.sceneRect());
       rect->setBrush(Qt::black);
       rect->show();
       QObject::connect(&timeLine,&QTimeLine::valueChanged,[=](qreal value)
       {
           qDebug()<<value;
           QBrush b=rect->brush();
           QColor c=b.color();
           c.setAlphaF(1-value);
           b.setColor(c);
            qDebug()<<b;
           rect->setBrush(b);
       });
       QObject::connect(&timeLine,&QTimeLine::stop,[&]()
       {
           scene.removeItem(rect);
       });
       timeLine.start();




   });
    return a.exec();



}
