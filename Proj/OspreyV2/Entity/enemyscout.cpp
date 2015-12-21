#include "enemyscout.h"

EnemyScout::EnemyScout(GameState *game, int x, int y, polarType polarity, Path *path, QString ref):
    EnemyEntity(game, x, y, polarity, path)
{
    Q_UNUSED(ref);
    init();
}


void EnemyScout::init()
{
    maxHealth = health = 25;
    maxSpeed = 225;
    value = 150;
    int cols = 1;
    int rows = 2;
    parseFrames(cols, rows);

    sprite = frames.at(polarity);

    //set Gun pos
    gun.setPoint(getX(), getY() + sprite->getHeight() /2);
}

void EnemyScout::doLogic(double delta)
{
    EnemyEntity::doLogic(delta);

    //shoot
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
}
