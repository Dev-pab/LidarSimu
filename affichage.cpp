#include "affichage.h"
#include <QDebug>

Affichage::Affichage()
{
    PointilleVert.setColor(Qt::green);
    PointilleVert.setStyle(Qt::DashDotLine);
    PointilleVert.setWidth(5);

    PointilleRouge.setColor(Qt::red);
    PointilleRouge.setStyle(Qt::DashDotLine);
    PointilleRouge.setWidth(2);

    BigBlackPen.setWidth(8);
}

void Affichage::init(Robot *robot, WorldManager *MyWord, Obstacle *obstacle, QGraphicsScene *scene)
{

    _Robot = robot;
    _MyWord = MyWord;
    _scene = scene;
    _obstacle = obstacle;

    qDebug() << "create robot" << endl;
    Robot_body = scene->addEllipse(_Robot->Xposition-_Robot->diametreRobot/2, _Robot->Yposition-_Robot->diametreRobot/2, _Robot->diametreRobot, _Robot->diametreRobot, redPen, redBrush);
    Playfield = scene->addRect(0, 0, 3000, 2000, redPen, redBrush);

    RobotTravel = scene->addLine(0,0,0,0, PointilleVert);

    _obstacle->loadConfig();

    _MyWord->init(_Robot, _obstacle);

    qDebug() << "create robot * DONE" << endl;
}

void Affichage::setAffichage()
{
    //Robot_body->setPos(_Robot->Xposition-_Robot->diametreRobot/2, _Robot->Yposition-_Robot->diametreRobot/2);
}

void  Affichage::upObjectif()
{

    QGraphicsEllipseItem* _objectif;

    if (objectif.size() != _Robot->objectif.size())
    {
        _objectif  = _scene->addEllipse( _Robot->objectif[objectif.size()].x() - _Robot->diametreRobot/2, _Robot->objectif[objectif.size()].y() - _Robot->diametreRobot/2, _Robot->diametreRobot, _Robot->diametreRobot, PointilleVert, redBrush);
        objectif << _objectif;
    }

    for (int i=0; i < _Robot->objectif.size(); i++)
    {
        if (i == _Robot->currentObjectif-1)
        {
            objectif[i]->setRect(_Robot->objectif[i].x() - _Robot->diametreRobot/2, _Robot->objectif[i].y() - _Robot->diametreRobot/2, _Robot->diametreRobot, _Robot->diametreRobot);
        }
        else
        {
            objectif[i]->setRect(_Robot->objectif[i].x() - 15, _Robot->objectif[i].y() - 15, 30, 30);
        }
        qDebug() << i << " " << _Robot->objectif.size();
    }



}

void  Affichage::upObstacle()
{
    if (obstacle.size() != _obstacle->obstacle_Ligne.size()-1)
    {
        obstacle << _scene->addLine(_obstacle->obstacle_Ligne[_obstacle->obstacle_Ligne.size()-1], BigBlackPen);
        LignePoint1 << _scene->addLine(_obstacle->obstacle_Ligne[_obstacle->obstacle_Ligne.size()-1].x1(), _obstacle->obstacle_Ligne[_obstacle->obstacle_Ligne.size()-1].y1(), _Robot->Xposition, _Robot->Yposition, PointilleRouge);
        LignePoint2 << _scene->addLine(_obstacle->obstacle_Ligne[_obstacle->obstacle_Ligne.size()-1].x2(), _obstacle->obstacle_Ligne[_obstacle->obstacle_Ligne.size()-1].y2(), _Robot->Xposition, _Robot->Yposition, PointilleRouge);
    }

}

void  Affichage::upLignePoint()
{
    for (int i=0; i<LignePoint1.size(); i++)
    {
        LignePoint1[i]->setLine(_obstacle->obstacle_Ligne[i+1].x1(), _obstacle->obstacle_Ligne[i+1].y1(),_Robot->Xposition, _Robot->Yposition);
        LignePoint2[i]->setLine(_obstacle->obstacle_Ligne[i+1].x2(), _obstacle->obstacle_Ligne[i+1].y2(),_Robot->Xposition, _Robot->Yposition);
    }
}

void Affichage::upRobot()
{
    Robot_body->setPos(_Robot->Xposition, _Robot->Yposition);

    if (objectif.size() != 0)
    {
        RobotTravel->setLine(_Robot->Xposition,  _Robot->Yposition, _Robot->objectif[_Robot->currentObjectif-1].x(), _Robot->objectif[_Robot->currentObjectif-1].y());
    }

    //upLignePoint();
}

void Affichage::setLignePointVisible(int etat)
{
    if (etat)
    {
        for (int i=0; i<LignePoint1.size(); i++)
        {
            LignePoint1[i]->setVisible(true);
            LignePoint2[i]->setVisible(true);
        }
    }
    else
    {
        for (int i=0; i<LignePoint1.size(); i++)
        {
            LignePoint1[i]->setVisible(false);
            LignePoint2[i]->setVisible(false);
        }
    }
}


void Affichage::upLidar()
{
    //qDebug() << _Robot->posRobotWhenScan.size();
    for (int i=0; i<_Robot->marqueur.size(); i++)
    {
        marqueurObstacle << _scene->addEllipse(_Robot->marqueur[i].x()-10, _Robot->marqueur[i].y()-10, 20, 20, PointilleRouge, redBrush);
    }
}
