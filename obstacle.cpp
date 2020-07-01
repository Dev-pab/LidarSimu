#include "obstacle.h"

Obstacle::Obstacle()
{
    QLine ligne;
    obstacle_Ligne << ligne;
}

void Obstacle::loadConfig()
{

}

void  Obstacle::addLigne(QPoint point1, QPoint point2)
{

    QLine ligne;

    ligne.setPoints(point1, point2);
    obstacle_Ligne << ligne;

}
