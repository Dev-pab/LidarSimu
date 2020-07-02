#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "robot.h"
#include "worldmanager.h"
#include "affichage.h"
#include "obstacle.h"

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *timer;

    void leftClick();
    void rightClick();
    void CoordSouris();

    void setObstacleVisible(int etat);

    void testPoint(int angle);

    QPen pointille;
    QPen PointilleVert;
    QPen PointilleRouge;
    QPen redPen;
    QPen blackdotted;
    QBrush redBrush;

    QGraphicsScene *scene;

    QGraphicsLineItem *obstacleIhm;
    QPoint debutLigneIhm;
    QPoint finLigneIhm;

    Robot *MyRobot;
    WorldManager *MyWorld;
    Affichage *MyAffichage;
    Obstacle *MyObstacle;

    Ui::MainWindow *ui;

public slots:

    void timerEvent();

private slots:

    void ajusterVue();
    void on_button_reserAffichage_clicked();
    void on_checkBox_ligneObstacle_stateChanged(int arg1);
    void on_spinBox_Xrobot_valueChanged(int arg1);
    void on_spinBox_YRobot_valueChanged(int arg1);
    void on_pushButton_tourLidar_clicked();
    void on_checkBox_Obstacle_stateChanged(int arg1);
    void on_pushButton_lecture_clicked();
    void on_pushButton_pause_clicked();
    void on_horizontalSlider_temps_valueChanged(int value);
};

extern MainWindow* ptW;

#endif // MAINWINDOW_H
