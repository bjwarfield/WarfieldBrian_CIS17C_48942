#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include <QtMath>
#include "Container/simplevector.h"
#include "Entity/entity.h"

class PlayerEntity:public Entity
{
public:
    enum throttle{OFF, FULL, TURBO};
    PlayerEntity(GameState *game, int x, int y);
    void move(double delta)Q_DECL_OVERRIDE;

    void doLogic(double delta)Q_DECL_OVERRIDE;
    void draw(QPainter * painter)Q_DECL_OVERRIDE;

    void collidedWith(const e_ptr &other)Q_DECL_OVERRIDE;

    ~PlayerEntity();

    int getEnergy() const;
    void setFlinching(double flinchTime);
    void setThrottleSetting(const throttle &value);

private:


    Vector<s_ptr> thrusterframes;
    Vector<s_ptr> flashFrames;

    //control variables
    bool left;
    bool right;
    bool up;
    bool down;
    bool trigger;
    bool polarize;
    bool burst;
    bool polarKeyLock;

    bool flinching;
    double flinchTimer;

    int moveSpeed;
    const float DIAGONAL;
//    Point push;

    int haloSize;
    double lastShot;
    double shotInterval;

    int energy;
    throttle throttleSetting;
    QRadialGradient whiteAura;
    QRadialGradient blackAura;


    void shoot();
    void shootBurst();
    void polarSwap();
    void die();
};

#endif // PLAYERENTITY_H
