#ifndef ENEMYSHOTENTITY_H
#define ENEMYSHOTENTITY_H

#include "entity.h"
#include "gamewidget.h"
class EnemyShotEntity: public Entity
{
private:
    GameWidget* game;


public:
    EnemyShotEntity(GameWidget * game, int x, int y, polarType polarity = WHITE);

    // Entity interface
public:
    void move(double delta);
    void draw(QPainter *painter);
    void doLogic();
    void collidedWith(e_ptr other);
    ~EnemyShotEntity();

protected:

    bool hit;

};

#endif // ENEMYSHOTENTITY_H
