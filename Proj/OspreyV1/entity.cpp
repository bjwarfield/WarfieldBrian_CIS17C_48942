#include <entity.h>


Entity::Entity(int x, int y, QString ref):
    x(x),y(y), removeThis(false)
{
    sprite = s_ptr(new Sprite(ref));
    hitBox.setRect(x,y,sprite->getWidth(),sprite->getHeight());
}

Entity::~Entity()
{

}

void Entity::move(double delta)
{
    x += (delta * dx);
    y += (delta * dy);
    hitBox.setRect(getX()-sprite->getWidth()/2,getY()-sprite->getHeight()/2,
                   sprite->getWidth(),sprite->getHeight());

}

void Entity::setHorizontalMovement(float dx)
{
    this->dx = dx;
}

void Entity::setVerticalMovement(float dy)
{
    this->dy = dy;
}

float Entity::getHorizontalMovement()
{
    return dx;
}

float Entity::getVerticalMovement()
{
    return dy;
}


void Entity::draw(QPainter *painter)
{
    sprite->draw(painter, getX(), getY());
}

bool Entity::collidesWith(e_ptr other)
{
    return hitBox.intersects(other->getHitBox());
}

void Entity::collidedWith(e_ptr other)
{
    Q_UNUSED(other);
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








