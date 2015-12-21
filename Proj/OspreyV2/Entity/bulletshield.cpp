#include "bulletshield.h"
#include "Util/timer.h"

BulletShield::BulletShield(GameState *game, double time)
    :Entity(game, 0,0,":/sprites/blank.png"),
      startTime(Timer::getTime()), expire(time)
{
    this->type = PLAYER;
}



void BulletShield::doLogic(double delta)
{
    Q_UNUSED(delta);
    if(Timer::getTime() - startTime > expire){
        removeThis = true;
    }
}

bool BulletShield::collidesWith(const e_ptr &other)
{
    Q_UNUSED(other);
    return true;
}
