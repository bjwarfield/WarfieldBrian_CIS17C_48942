#ifndef BULLETSHIELD_H
#define BULLETSHIELD_H

#include "entity.h"



class BulletShield : public Entity
{
public:
    BulletShield(GameState *game, double time);
    double startTime;
    double expire;
    // Entity interface
public:
    void doLogic(double delta);
    bool collidesWith(const e_ptr &other);

};

#endif // BULLETSHIELD_H
