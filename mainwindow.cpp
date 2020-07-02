#include "mainwindow.h"
#include "ui_mainwindow.h"

double XSouris, YSouris;
bool isClicked;

class MaScene : public QGraphicsScene {
public:
    MaScene(QObject *parent) : QGraphicsScene(parent) {
    }

protected :

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        QPointF souris;

        isClicked = true;

        //qDebug() << "P" << event->scenePos();
        souris = QPointF(event->scenePos());

        XSouris = souris.x();
        YSouris = souris.y();

        if(event->button() == Qt::RightButton)
        {
            ptW->rightClick();
        }
        else if(event->button() == Qt::MiddleButton)
        {

        }
        else if(event->button() == Qt::LeftButton)
        {
            ptW->leftClick();
        }

        event->accept();


        QGraphicsScene::mousePressEvent(event);

    }
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        QPointF souris;

        souris = QPointF(event->scenePos());

        XSouris = souris.x();
        YSouris = souris.y();

        ptW->CoordSouris();

        event->accept();

        QGraphicsScene::mouseMoveEvent(event);

    }
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        isClicked = false;
        event->accept();

        QGraphicsScene::mouseReleaseEvent(event);
    }

};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new MaScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);

    setWindowTitle("LIDARsim  V0.01");

    pointille.setStyle(Qt::DashLine);
    pointille.setWidth(5);
    PointilleVert.setColor(Qt::green);
    PointilleVert.setStyle(Qt::DashDotLine);
    PointilleVert.setWidth(5);

    PointilleRouge.setColor(Qt::red);
    PointilleRouge.setStyle(Qt::DashDotLine);
    PointilleRouge.setWidth(2);

    Robot _MyRobot;
    WorldManager _MyWorld;
    Affichage _MyAffichage;
    Obstacle _MyObstacle;

    MyRobot = new Robot;
    MyWorld = new WorldManager;
    MyAffichage = new Affichage;
    MyObstacle = new Obstacle;

    MyAffichage->init(MyRobot, MyWorld, MyObstacle, scene);

    obstacleIhm = scene->addLine(0, 0, 3000, 0, pointille);
    obstacleIhm->setVisible(false);
    MyAffichage->upObstacle();

    QTimer::singleShot(500, this, SLOT(ajusterVue()));

    timer = new QTimer();
    timer->connect(timer, SIGNAL(timeout()),this, SLOT(timerEvent()));
}

MainWindow::~MainWindow()
{
    delete MyObstacle;
    delete MyAffichage;
    delete MyWorld;
    delete MyRobot;
    delete ui;
}

void MainWindow::ajusterVue()
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::on_button_reserAffichage_clicked()
{
    MyAffichage->setAffichage();
}

void MainWindow::rightClick()
{
    MyRobot->addObjectf(XSouris, YSouris);
    MyAffichage->upObjectif();
}

void MainWindow::leftClick()
{
    if (!obstacleIhm->isVisible())
    {
        obstacleIhm->setVisible(true);
        debutLigneIhm.setX(XSouris);
        debutLigneIhm.setY(YSouris);
        finLigneIhm.setX(XSouris);
        finLigneIhm.setY(YSouris);
        obstacleIhm->setLine(XSouris, YSouris, XSouris, YSouris);
    }
    else
    {
        obstacleIhm->setVisible(false);
        MyObstacle->addLigne(debutLigneIhm, finLigneIhm);
        MyAffichage->upObstacle();
    }

}

void MainWindow::setObstacleVisible(int etat)
{
    if (etat)
    {
        obstacleIhm->setVisible(true);
    }
    else
    {
        obstacleIhm->setVisible(false);
    }
}

void MainWindow::CoordSouris()
{
    if (obstacleIhm->isVisible())
    {
        if ( (XSouris>debutLigneIhm.x()-20) && (XSouris<debutLigneIhm.x()+20))
        {
            finLigneIhm.setX(debutLigneIhm.x());
        }
        else
        {
            finLigneIhm.setX(XSouris);
        }
        if ( (YSouris>debutLigneIhm.y()-20) && (YSouris<debutLigneIhm.y()+20))
        {
            finLigneIhm.setY(debutLigneIhm.y());
        }
        else
        {
            finLigneIhm.setY(YSouris);
        }

        obstacleIhm->setLine(debutLigneIhm.x(), debutLigneIhm.y() , finLigneIhm.x(), finLigneIhm.y());
    }

    ui->label_XSouris->setText(QString::number(XSouris));
    ui->label_YSouris->setText(QString::number(YSouris));
}

void MainWindow::on_checkBox_ligneObstacle_stateChanged(int arg1)
{
    MyAffichage->setLignePointVisible(arg1);
}
void MainWindow::on_checkBox_Obstacle_stateChanged(int arg1)
{

}


void MainWindow::on_spinBox_Xrobot_valueChanged(int arg1)
{
    MyRobot->setX(arg1);
    MyAffichage->upRobot();
}

void MainWindow::on_spinBox_YRobot_valueChanged(int arg1)
{
    MyRobot->setY(arg1);
    MyAffichage->upRobot();
}

void MainWindow::on_pushButton_tourLidar_clicked()
{
    QPoint posRobot(MyRobot->Xposition, MyRobot->Yposition);
    MyRobot->posRobotWhenScan << posRobot;

    for (int i=0; i<=360; i +=1)
    {
        //qDebug() << i;
        MyRobot->distancelidar[i] = 400;
        MyRobot->calculLigneLidar(i);
        testPoint(i);
    }
    MyAffichage->upLidar();
    MyRobot->posRobotWhenScanNUM << MyRobot->posRobotWhenScan.size();
}

void MainWindow::testPoint(int angle)
{
    int flagMur=0;

    for (int i=0; i < MyObstacle->obstacle_Ligne.size(); i++)
    {
        for (int point = 0; point < 400; point++)
        {
            double dist1, dist2, disttot;
            dist1 = sqrt( pow( abs(MyRobot->ligneLidar[0][point] - MyObstacle->obstacle_Ligne[i].x1()) , 2) + pow( abs(MyRobot->ligneLidar[1][point] - MyObstacle->obstacle_Ligne[i].y1()) , 2));
            dist2 = sqrt( pow( abs(MyRobot->ligneLidar[0][point] - MyObstacle->obstacle_Ligne[i].x2()) , 2) + pow( abs(MyRobot->ligneLidar[1][point] - MyObstacle->obstacle_Ligne[i].y2()) , 2));
            disttot = sqrt( pow( abs(MyObstacle->obstacle_Ligne[i].x1() - MyObstacle->obstacle_Ligne[i].x2()) , 2) + pow( abs(MyObstacle->obstacle_Ligne[i].y1() - MyObstacle->obstacle_Ligne[i].y2()) , 2));

            if ( ((dist1+dist2) >= (disttot * 1.001)) && (flagMur==0) && ( (MyRobot->ligneLidar[0][point] > 0) && (MyRobot->ligneLidar[0][point] < 3000) && (MyRobot->ligneLidar[1][point] > 0) && (MyRobot->ligneLidar[1][point] < 2000)))
            {

            }
            else if (flagMur==0)
            {

                if (MyRobot->distancelidar[angle] > point)
                {
                    MyRobot->distancelidar[angle] = point;
                    QPoint Lpoint(MyRobot->ligneLidar[0][point], MyRobot->ligneLidar[1][point]);
                    MyRobot->marqueur << Lpoint;
                }
                flagMur = 1;
            }
        }
        flagMur=0;
    }
}

void MainWindow::timerEvent()
{
    MyRobot->newTic();
    MyAffichage->upRobot();
    MyAffichage->upObjectif();
}


void MainWindow::on_pushButton_lecture_clicked()
{
    if (!timer->isActive())
    {
        timer->start(50);
    }
}

void MainWindow::on_pushButton_pause_clicked()
{
    if (timer->isActive())
    {
        timer->stop();
    }
}

void MainWindow::on_horizontalSlider_temps_valueChanged(int value)
{
    double delais = 50.00;
    delais = delais * (200 - value) / 100;
    timer->setInterval((int)delais);

    ui->spinBox_temps->setValue(value);
}
