#include "enemyprobe.h"

EnemyProbe::EnemyProbe(GameState *game, int x, int y, polarType polarity, Path *path, QString ref):
    EnemyEntity(game, x, y, polarity, path, ":/sprites/enemy/probe.png" )
{
    Q_UNUSED(ref);
    init();

}


void EnemyProbe::init()
{
//    this->path = new Path;
//    this->path->addNode(Point(100,200));
//    this->path->addNode(Point(700,300));
//    this->path->addNode(Point(100,400));
//    this->path->addNode(Point(700,500));
//    this->path->addNode(Point(400,1000));
    maxHealth = health = 15;
    maxSpeed = 225;
    value = 150;
    int cols = 1;
    int rows = 2;
    parseFrames(cols, rows);

    sprite = frames.at(polarity);

    //set Gun pos
    gun.setPoint(getX(), getY() + sprite->getHeight() /2);
}

void EnemyProbe::doLogic(double delta)
{
    EnemyEntity::doLogic(delta);
    angle = moveTicks*0.05;
}
