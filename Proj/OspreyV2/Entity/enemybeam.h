#ifndef ENEMYBEAM_H
#define ENEMYBEAM_H

#include "enemyshotentity.h"



class EnemyBeam : public EnemyShotEntity
{
public:
    EnemyBeam(GameState *game, int x, int y, polarType polarity = WHITE);

    // Entity interface
public:
    void draw(QPainter *painter);
    void doLogic(double delta);
protected:
    virtual void init();
    Point trail;
    QRadialGradient whiteBlast;
    QRadialGradient blackBlast;
    int currentRadius;
    int targetRadius;

    // Entity interface
public:
    void collidedWith(const e_ptr &other);
};

#endif // ENEMYBEAM_H
