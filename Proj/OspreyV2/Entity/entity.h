#ifndef ENTITY_H
#define ENTITY_H

#include <QDebug>
#include <QPainter>
#include <QRect>
#include <QtMath>
#include "Util/point.h"
#include "Util/sprite.h"



class Entity;
typedef  QSharedPointer<Entity> e_ptr;
typedef QSharedPointer<Sprite> s_ptr;
enum polarType{WHITE, BLACK};
enum entityType{PLAYER, SHOT, BURST, ENEMY, ENEMYSHOT, ENEMYBEAM, EFFECT, SHIP};

#include <GameState/gamestate.h>

#include <Container/simplevector.h>
class GameState;
class Entity
{
public:

    Entity(GameState *game, int x, int y, QString ref);
    Entity(GameState *game, Point point, QString ref);
    virtual ~Entity();

    virtual void move(double delta);
    virtual void move(double delta, float xShift);
    virtual void move(double delta, float xShift, float yShift);
    void setHorizontalMovement(float dx);
    void setVerticalMovement(float dy);
    float getHorizontalMovement() const;
    float getVerticalMovement() const;

    virtual void draw(QPainter * painter);

    virtual void doLogic(double delta) = 0;


    Point getPos() const;
    int getX()const{return static_cast<int>(pos.x());}
    int getY()const{return static_cast<int>(pos.y());}
    int width()const{return sprite->getWidth();}
    int height()const{return sprite->getHeight();}
    float distanceTo(const e_ptr &other);
    float distanceTo(const QPoint &other);
    float distanceTo(const Point &other);

    virtual bool collidesWith(const e_ptr &other);
    virtual void collidedWith(const e_ptr &other);

    virtual void boundCheck();

    QRect getHitBox() const;

    polarType getPolarity() const;

    entityType getType() const;


    bool getRemoveThis() const;
    void setRemoveThis(bool value);


protected:
    GameState *game;
    //    float x;
//    float y;
    Point pos;

    s_ptr sprite;
//    float dx;
//    float dy;
    Point dir;

    bool
    removeThis;

    QRect hitBox;
    polarType polarity;
    entityType type;

    Vector<s_ptr> frames;
    double lastFrameChange;
    int currentFrame;

};




#endif // ENTITY_H
