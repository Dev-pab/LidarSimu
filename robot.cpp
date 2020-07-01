#include "robot.h"

#include <QtMath>
#include <QDebug>

Robot::Robot()
{
    Xposition = 200;
    Yposition = 200;

    diametreRobot = 150;
}

void Robot::addObjectf(double x, double y)
{
    QPoint _newPoint(x, y);
    objectif << _newPoint;
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
