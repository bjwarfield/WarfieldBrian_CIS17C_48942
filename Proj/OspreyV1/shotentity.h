 #ifndef SHOTENTITY_H
#define SHOTENTITY_H

#include "gamewidget.h"
#include <QVector>


class ShotEntity: public Entity
{
private:
    int shotSpeed;
    bool hit;
    GameWidget *game;

public:
    ShotEntity(GameWidget *game, int x, int y, polarType polarity);
    void draw(QPainter *painter);

    // Entity interface
    void move(double delta);
    void doLogic();
    void collidedWith(e_ptr other);

    ~ShotEntity();
    bool getHit() const;

protected:
//    polarType polarity;
//    entityType type;

    // Entity interface
};

#endif // SHOTENTITY_H
