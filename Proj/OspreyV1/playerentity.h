#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include <QtMath>
#include <QVector>
#include "entity.h"
#include "gamewidget.h"

class GameWidget;


class PlayerEntity:public Entity
{
public:
    PlayerEntity(GameWidget * game, int x, int y);
    void move(double delta);

    void doLogic();
    void draw(QPainter * painter);

    void collidedWith(e_ptr other);

    void setLeft(bool left);
    void setRight(bool right);
    void setUp(bool up);
    void setDown(bool down);
    void setTrigger(bool trigger);
    void setPolarize(bool polarize);
    ~PlayerEntity();


    int getEnergy() const;

private:
    GameWidget * game;


    bool left;
    bool right;
    bool up;
    bool down;
    bool trigger;
    bool polarize;

    int moveSpeed;
    const float DIAGONAL;

    double lastShot;
    double shotInterval;

    int energy;

    void shoot();
    void polarSwap();


};

#endif // PLAYERENTITY_H
