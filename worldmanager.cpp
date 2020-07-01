#include "worldmanager.h"

#include <QtMath>

WorldManager::WorldManager()
{

}

void WorldManager::init(Robot *Robot, Obstacle *obstacle)
{
    _Robot = Robot;
    _obstacle = obstacle;
}

void WorldManager::testPoint()
{
    /*
    for (int i=1; i < _obstacle->obstacle_Ligne.size(); i++)
    {
        //qDebug() << "obstacle : " << i;
        for (int point = 0; point <360; point++)
        {
            double a1, a2, b1, b2;

            a1 = (_Robot->ligneLidar[1][point] - _Robot->Yposition) / (_Robot->ligneLidar[0][point] - _Robot->Xposition);
            a2 = (_obstacle->obstacle_Ligne[i].y2() - _obstacle->obstacle_Ligne[i].y1()) / (_obstacle->obstacle_Ligne[i].x2() - _obstacle->obstacle_Ligne[i].x1());

            if (a1 != a2)
            {
                b1 = _Robot->Yposition - (a1 * _Robot->Xposition);
                b2 = _obstacle->obstacle_Ligne[i].y1() - (a2 * _obstacle->obstacle_Ligne[i].x1());
                QPoint Lpoint((b2 - b1), (a1 - a2));

                _Robot->marqueur << Lpoint;
            }
        }

    }*/
}
