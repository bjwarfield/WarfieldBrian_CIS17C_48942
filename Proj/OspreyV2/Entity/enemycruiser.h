#ifndef ENEMYCRUISER_H
#define ENEMYCRUISER_H

#include "enemyentity.h"



class EnemyCruiser : public EnemyEntity
{
public:
    EnemyCruiser(GameState *game, int x, int y, polarType polarity, Path *path = NULL, QString ref = "");

    // Entity interface
public:
    void doLogic(double delta);

    // EnemyEntity interface
protected:
    void init();
    virtual void shoot();
};

#endif // ENEMYCRUISER_H
