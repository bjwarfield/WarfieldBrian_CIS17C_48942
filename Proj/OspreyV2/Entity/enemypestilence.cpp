#include "enemypestilence.h"

EnemyPestilence::EnemyPestilence(GameState *game, int x, int y, polarType polarity, Path *path, QString ref):
    EnemyEntity(game, x, y, polarity, path, ":/sprites/enemy/pestilence.png" )
{
    Q_UNUSED(ref);
    init();

}

void EnemyPestilence::init()
{
//    this->path = new Path;
//    this->path->addNode(Point(100,200));
//    this->path->addNode(Point(700,300));
//    this->path->addNode(Point(100,400));
//    this->path->addNode(Point(700,500));
//    this->path->addNode(Point(400,1000));
    maxHealth = health = 100;
    maxSpeed = 225;
    value = 150;

    int cols = 1;
    int rows = 2;
    parseFrames(cols, rows);

    sprite = frames.at(polarity);

    //set Gun pos
    gun.setPoint(getX(), getY() + sprite->getHeight() /2);
}

void EnemyPestilence::draw(QPainter *painter)
{
    EnemyEntity::draw(painter);
}

void EnemyPestilence::doLogic(double delta)
{
    EnemyEntity::doLogic(delta);
    angle = pos.angleTo(targetPlayer);

    if(shotTicks > lastShot){
        lastShot = shotTicks;
        if(shotTicks % 50 == 45){
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
        }
        if(shotTicks % 50 == 46){
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
        }
        if(shotTicks % 50 == 47){
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
        }
        if(shotTicks % 50 == 48){
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
        }
        if(shotTicks % 50 == 49){
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
            shoot(200, targetPlayer,game->rand(-10,10)/10.0f);
        }
    }

    maxSpeed = currentNode == 1 ? 50 : 255;
}

void EnemyPestilence::collidedWith(const e_ptr &other)
{
    EnemyEntity::collidedWith(other);
}


