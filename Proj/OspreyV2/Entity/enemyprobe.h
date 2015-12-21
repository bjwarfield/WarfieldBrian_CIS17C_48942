#ifndef ENEMYPROBE_H
#define ENEMYPROBE_H

#include "enemyentity.h"



class EnemyProbe : public EnemyEntity
{
public:
    EnemyProbe(GameState *game, int x, int y, polarType polarity, Path *path = NULL, QString ref = "");



    // EnemyEntity interface
protected:
    void init();
public:
    void doLogic(double delta);
};

#endif // ENEMYPROBE_H
