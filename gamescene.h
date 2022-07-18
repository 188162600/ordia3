#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<QGraphicsScene>
class AbstractProtagonist;
void setUpLevel1Contents(AbstractProtagonist*p,QGraphicsScene *scene);

//class GameScenePrivate;
//class AbstractProtagonist;
//class GameScene:public QGraphicsScene
//{
//public:
//    GameScene(QObject*parent=nullptr);

//    void setProtagonist(AbstractProtagonist*p);
//    ~GameScene();

//    // QGraphicsScene interface
//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//private:
//    GameScenePrivate*d;
//    GameScene(GameScenePrivate&d,QObject *parent );

//};

#endif // GAMESCENE_H
