#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QMainWindow>
#include "robot.h"
#include "worldmanager.h"
#include "obstacle.h"


#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QVector>

class Affichage
{
public:
    Affichage();

    void init(Robot *robot, WorldManager *MyWord, Obstacle *obstacle, QGraphicsScene *scene);
    void setAffichage();
    void upObjectif();
    void upObstacle();
    void upLignePoint();
    void upRobot();
    void upLidar();

    void setLignePointVisible(int etat);


private:

    Robot *_Robot;
    WorldManager *_MyWord;
    QGraphicsScene *_scene;
    Obstacle *_obstacle;

    QPen PointilleVert;
    QPen PointilleRouge;
    QPen redPen;
    QPen BigBlackPen;
    QPen blackdotted;
    QBrush redBrush;

    QGraphicsEllipseItem *Robot_body;
    QGraphicsRectItem *Playfield;

    QVector<QGraphicsEllipseItem*> objectif;
    QVector<QGraphicsLineItem*> obstacle;

    QVector<QGraphicsLineItem*> LignePoint1;
    QVector<QGraphicsLineItem*> LignePoint2;
};

#endif // AFFICHAGE_H
