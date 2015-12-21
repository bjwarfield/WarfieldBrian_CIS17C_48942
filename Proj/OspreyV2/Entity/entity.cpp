
#include "entity.h"


Entity::Entity(GameState *game, int x, int y, QString ref):
    game(game), pos(x,y), removeThis(false)
{
    sprite = s_ptr(new Sprite(ref));
}

Entity::Entity(GameState *game, Point point, QString ref):
    game(game), pos(point), removeThis(false)
{
    sprite = s_ptr(new Sprite(ref));
}

Entity::~Entity()
{

}

void Entity::move(double delta)
{
    pos.rx() += (delta * dir.x());
    pos.ry() += (delta * dir.y());
    hitBox.setRect(getX()-sprite->getWidth()/2,getY()-sprite->getHeight()/2,
                   sprite->getWidth(),sprite->getHeight());

}

void Entity::move(double delta, float xShift)
{
    pos.rx() += (delta * (dir.x() + xShift));
    pos.ry() += (delta * dir.y());
    hitBox.setRect(getX()-sprite->getWidth()/2,getY()-sprite->getHeight()/2,
                   sprite->getWidth(),sprite->getHeight());
}

void Entity::move(double delta, float xShift, float yShift)
{
    pos.rx() += (delta * (dir.x() + xShift));
    pos.ry() += (delta * (dir.y() + yShift));
    hitBox.setRect(getX()-sprite->getWidth()/2,getY()-sprite->getHeight()/2,
                   sprite->getWidth(),sprite->getHeight());
}

void Entity::setHorizontalMovement(float dx)
{
    dir.rx() = dx;
}

void Entity::setVerticalMovement(float dy)
{
    dir.ry()= dy;
}

float Entity::getHorizontalMovement() const
{
    return dir.x();
}

float Entity::getVerticalMovement() const
{
    return dir.y();
}


void Entity::draw(QPainter *painter)
{
    sprite->draw(painter, getX(), getY());
}

float Entity::distanceTo(const e_ptr &other)
{
    return qSqrt(qPow(pos.x() - other->getX(), 2)+qPow(pos.y() - other->getY(), 2));
}

float Entity::distanceTo(const QPoint &other)
{
    return qSqrt(qPow(pos.x() - other.x(), 2)+qPow(pos.y() - other.y(), 2));
}

float Entity::distanceTo(const Point &other)
{
    return other.distanceTo(Point(getX(),getY()));
}

bool Entity::collidesWith(const e_ptr &other)
{
    return hitBox.intersects(other->getHitBox());
}

void Entity::collidedWith(const e_ptr &other)
{
    Q_UNUSED(other);
}

void Entity::boundCheck()
{
    //bound check. Remove entity if it strays too far off entity map
    if (getX() + (width() / 2) <  -50
            || getX() - (width() / 2) > game->width()+ 50
            || getY() - (height() / 2) > game->height() + 50
            || getY() + (height() / 2) < - 50) {
        removeThis = true;
    }
}
QRect Entity::getHitBox() const
{
    return hitBox;
}
polarType Entity::getPolarity() const
{
    return polarity;
}
entityType Entity::getType() const
{

    return type;
}
bool Entity::getRemoveThis() const
{
    return removeThis;
}
void Entity::setRemoveThis(bool value)
{
    removeThis = value;
}
Point Entity::getPos() const
{
    return pos;
}










