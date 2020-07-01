#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QLine>
#include <QPoint>

class Obstacle
{
public:
    Obstacle();

    void loadConfig();

    void addLigne(QPoint point1, QPoint point2);

    int update_number;

    QVector<QLine> obstacle_Ligne;

    QVector<double> X1Obstacle;
    QVector<double> Y1Obstacle;
};

#endif // OBSTACLE_H
