#ifndef ROBOT_H
#define ROBOT_H

#include <QMainWindow>
#include <QVector>
#include <QPoint>

class Robot
{
public:
    Robot();

    int rayonLidar_mm = 1500;
    double vitesse_mms = 20;

    double Xposition;
    double Yposition;

    double distancelidar[360];

    double diametreRobot;

    int currentObjectif=0;
    double distanceToNextObjectif;
    double stepX=0;
    double stepY=0;
    int step=0;

    QVector<QPoint> marqueur;
    QVector<QPoint> posRobotWhenScan;
    QVector<int> posRobotWhenScanNUM;
    QVector<QPoint> objectif;

    int update_number;

    double ligneLidar[2][400];

    QPoint marqueurObstacle[360];

    void addObjectf(double x, double y);
    void setPos(double x, double y);
    void setX(double x);
    void setY(double y);


    void calculLigneLidar(double angle);
    void ScannerTour();
    void goToObjectif(int number);

    void newTic();
};

#endif // ROBOT_H
