#ifndef ENEMYSCOUT_H
#define ENEMYSCOUT_H

#include "enemyentity.h"



class EnemyScout: public EnemyEntity
{
public:
    EnemyScout(GameState *game, int x, int y, polarType polarity, Path *path = NULL, QString ref = "");


    // EnemyEntity interface
protected:
    void init();

    // Entity interface
public:
    void doLogic(double delta);
};

#endif // ENEMYSCOUT_H
