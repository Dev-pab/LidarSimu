#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "robot.h"
#include "obstacle.h"

class WorldManager
{
public:
    WorldManager();

    Robot *_Robot;
    Obstacle *_obstacle;

    double toleranceDetection = 0.1;

    void init(Robot *Robot, Obstacle *obstacle);
    void testPoint();
};

#endif // WORLDMANAGER_H
