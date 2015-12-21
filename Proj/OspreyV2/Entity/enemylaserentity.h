#ifndef ENEMYLASERENTITY_H
#define ENEMYLASERENTITY_H

#include "enemyshotentity.h"



class EnemyLaserEntity : public EnemyShotEntity
{
public:
    EnemyLaserEntity(GameState *game, int x, int y, polarType polarity = WHITE);

    // Entity interface
public:
    void draw(QPainter *painter);
    void doLogic(double delta);
    void collidedWith(const e_ptr &other);

    // EnemyShotEntity interface
protected:
    virtual void init();
    Point trail;
};

#endif // ENEMYLASERENTITY_H
