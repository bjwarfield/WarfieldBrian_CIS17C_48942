#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H
#include "Container/simplevector.h"
#include "Entity/entity.h"
#include "Main/gamewidget.h"

class GameWidget;

//path following behavior
struct Path{
private:
    Vector<Point> nodes;
public:
    void addNode(Point node){nodes.append(node);}
    Vector<Point> &getNodes(){return nodes;}
};

class EnemyEntity: public Entity
{

public:
    EnemyEntity(GameState *game, int x, int y, polarType polarity = WHITE,
                Path *path = NULL, QString ref = ":/sprites/enemy/scout.png");
    virtual void draw(QPainter *painter)Q_DECL_OVERRIDE;
    virtual void doLogic(double delta)Q_DECL_OVERRIDE;
    virtual void shoot(int speed, const e_ptr &targetPlayer, float deg);
    virtual void shoot(int speed, Point targetPlayer, float deg);
    virtual void collidedWith(const e_ptr &other)Q_DECL_OVERRIDE;
    virtual void boundCheck();
    bool isDead();

    virtual ~EnemyEntity();

protected:


    int maxHealth;
    int health;
    int value;
    bool hit;
    bool dead;
    Point gun;

    double startTime;
    double elapsed;
    double ticker;
    double aDelta;
    int moveTicks;
    int lastMove;
    int shotTicks;
    int lastShot;

    float angle;
    float maxSpeed;

    Point targetPlayer;
    float targetAngle;

    Path *path;
    int currentNode;

    Point tv;//target vector
    Point sv;//steering vector

    virtual void init();
    virtual void seek(const Point &trgt, float dist, double delta);
    virtual void followPath(double delta);
    virtual void parseFrames(int cols, int rows);




};

#endif // ENEMYENTITY_H
