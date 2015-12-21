#ifndef ENTITY_H
#define ENTITY_H

#include <QDebug>
#include <QPainter>
#include <QRect>
#include "sprite.h"


class Entity;
typedef QSharedPointer<Sprite> s_ptr;
typedef  QSharedPointer<Entity> e_ptr;
enum polarType{WHITE, BLACK};
enum entityType{PLAYER, SHOT, ENEMY, ENEMYSHOT, EFFECT};

class Entity
{
public:
    Entity(int x, int y, QString ref);
    virtual ~Entity();

    virtual void move(double delta);
    void setHorizontalMovement(float dx);
    void setVerticalMovement(float dy);
    float getHorizontalMovement();
    float getVerticalMovement();

    virtual void draw(QPainter * painter);

    virtual void doLogic() = 0;

    int getX()const{return static_cast<int>(x);}
    int getY()const{return static_cast<int>(y);}

    bool collidesWith(e_ptr other);
    virtual void collidedWith(e_ptr other);

    QRect getHitBox() const;

    polarType getPolarity() const;

    entityType getType() const;


    bool getRemoveThis() const;

protected:
    float x;
    float y;

    s_ptr sprite;
    float dx;
    float dy;

    bool removeThis;

    QRect hitBox;
    polarType polarity;
    entityType type;

    QVector<s_ptr> frames;
    double lastFrameChange;
    int currentFrame;

};




#endif // ENTITY_H
