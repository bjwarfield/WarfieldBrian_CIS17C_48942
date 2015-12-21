#ifndef ENEMYSHOTENTITY_H
#define ENEMYSHOTENTITY_H

#include "entity.h"
#include "Main/gamewidget.h"
class EnemyShotEntity: public Entity
{
public:
    EnemyShotEntity(GameState *game, int x, int y, polarType polarity = WHITE);

    // Entity interface
public:
    virtual void draw(QPainter *painter)Q_DECL_OVERRIDE;
    virtual void doLogic(double delta)Q_DECL_OVERRIDE;
    virtual void collidedWith(const e_ptr &other)Q_DECL_OVERRIDE;
    ~EnemyShotEntity();

protected:
    virtual void init();
    bool hit;

};

#endif // ENEMYSHOTENTITY_H
