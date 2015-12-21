#ifndef BURSTSHOT_H
#define BURSTSHOT_H

#include "Entity/shotentity.h"


class BurstShot:public ShotEntity
{
public:
    BurstShot(GameState *game, int x, int y, float angle, polarType polarity);
    ~BurstShot();
    // Entity interface
public:
    void draw(QPainter *painter) Q_DECL_OVERRIDE;
    void doLogic(double delta) Q_DECL_OVERRIDE;
    void collidedWith(const e_ptr &other) Q_DECL_OVERRIDE;
//    bool collidesWith(e_ptr other);
    void move(double delta) Q_DECL_OVERRIDE;
    void move(double delta, float xShift) Q_DECL_OVERRIDE;
    void move(double delta, float xShift, float yShift) Q_DECL_OVERRIDE;

private:

    float angle;
    Point target;
    float targetAngle;
    float targetDistance;
    float angleDistance;
    float rotatesSpeed;
    Vector<Point> trail;

//    float getDistance(Point a, Point b);
    void steerShot(double delta);
    void setTrail();
    void drawLines(QPainter *painter, int maxSegments);
};

#endif // BURSTSHOT_H
