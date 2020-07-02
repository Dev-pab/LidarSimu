#include "robot.h"

#include <QtMath>
#include <QDebug>

Robot::Robot()
{
    Xposition = 0;
    Yposition = 0;

    diametreRobot = 150;
}

void Robot::addObjectf(double x, double y)
{
    QPoint _newPoint(x, y);
    objectif << _newPoint; 


    goToObjectif(objectif.size());

}

void Robot::setPos(double x, double y)
{
    Xposition = x;
    Yposition = y;
}

void Robot::setX(double x)
{
    Xposition = x;
}

void Robot::setY(double y)
{
    Yposition = y;
}

void Robot::ScannerTour()
{
    for (int i=0; i<=360; i++)
    {
        calculLigneLidar(i);
    }

}

void Robot::calculLigneLidar(double angle)
{
    double angle_radian =  qDegreesToRadians(angle);
    double cos = qCos(angle_radian) * rayonLidar_mm;
    double sin = qSin(angle_radian) * rayonLidar_mm;

    for (int i=0; i<300; i++)
    {
        ligneLidar[0][i] = cos * (i/300.000) + Xposition;
        ligneLidar[1][i] = sin * (i/300.000) + Yposition;

    }
}

void Robot::goToObjectif(int number)
{
    currentObjectif = number;

    double xdist, ydist;

    xdist = abs(Xposition - objectif[number-1].x());
    ydist = abs(Yposition - objectif[number-1].y());

    distanceToNextObjectif = sqrt( pow(xdist, 2) + pow(ydist, 2));

    step = distanceToNextObjectif / vitesse_mms;

    if (Xposition > objectif[number-1].x())
    {
        stepX = -xdist / step;
    }
    else
    {
        stepX = xdist / step;
    }

    if (Yposition > objectif[number-1].y())
    {
        stepY = -ydist / step;
    }
    else
    {
        stepY = ydist / step;
    }

}

void Robot::newTic()
{
    if(!(step == 0))
    {
        Xposition += stepX;
        Yposition += stepY;

        step--;
    }
    else
    {
        stepX = 0;
        stepY = 0;
    }

}


