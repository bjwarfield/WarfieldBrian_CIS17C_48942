#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H
#include <QtMath>
#include <QVector>
#include "entity.h"
#include "gamewidget.h"

class GameWidget;

class EnemyEntity: public Entity
{
private:
    GameWidget *game;
public:
    EnemyEntity(GameWidget *game, int x, int y, polarType polarity = WHITE);
    void move(double delta);
    void draw(QPainter *painter);
    void doLogic();
    bool isDead();
    void shoot(int speed, e_ptr target, float deg);
    void collidedWith(e_ptr other);

    ~EnemyEntity();

protected:

    int health;
    bool hit;
    bool dead;

    double lastFrameChange;
    int currentFrame;

};

#endif // ENEMYENTITY_H
