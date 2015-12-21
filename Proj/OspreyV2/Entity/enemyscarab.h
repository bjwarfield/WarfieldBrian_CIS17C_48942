#ifndef ENEMYSCARAB_H
#define ENEMYSCARAB_H

#include "enemyentity.h"



class EnemyScarab:public EnemyEntity
{
public:
    EnemyScarab(GameState *game, int x, int y, polarType polarity,
                Path *path = NULL, QString ref = "");
    ~EnemyScarab();
    // Entity interface
public:
    void draw(QPainter *painter);
    void doLogic(double delta);
    bool collidesWith(const e_ptr &other);
    void collidedWith(const e_ptr &other);

    // EnemyEntity interface
protected:
    enum wingStatus{OPEN, CLOSED};
    void init();
    DList<e_ptr> probeList;
    int orbitRadius;
    DList<QSharedPointer<Point> > probeOrbits;
    wingStatus wings;
    int currentProbe;
    float orbitSpeedMod;


    // EnemyEntity interface
protected:
    void followPath(double delta);

    // Entity interface
public:
    void move(double delta, float xShift);
};

class OrbitalProbe:public EnemyEntity
{

public:
    OrbitalProbe(GameState *game, int x, int y, polarType polarity,
                 QSharedPointer<Point> &orbit, QString ref = "");
    ~OrbitalProbe();
    void move(double delta, float xShift);
    void draw(QPainter *painter);
    void doLogic(double delta);


    // EnemyEntity interface
protected:
    void init();
    Point *orbit;

};

#endif // ENEMYSCARAB_H
