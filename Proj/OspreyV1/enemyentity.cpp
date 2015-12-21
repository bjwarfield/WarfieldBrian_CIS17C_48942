#include "enemyentity.h"
#include "enemyshotentity.h"
#include "shotentity.h"

EnemyEntity::EnemyEntity(GameWidget *game, int x, int y, polarType polarity):
    Entity(x,y,":/resources/sprites/enemy/scout.png"), game(game),
    health(20), hit(false), dead(false)
{
    this->polarity = polarity;
    type = ENEMY;

    setVerticalMovement(0);
    setHorizontalMovement(0);

    int cols = 1;
    int rows = 2;
    int tileHeight = sprite->getHeight()/rows;
    int tileWidth = sprite->getWidth()/cols;

    frames.resize(cols*rows);

    for(int col = 0; col < cols; col++){
        for(int row = 0; row < rows; row++){
            frames.data()[col + (row * cols)] =
                    s_ptr( new Sprite(sprite->getRef(),
                                      sprite->getImage().copy(
                                          col*tileWidth,
                                          row*tileHeight,
                                          tileWidth,
                                          tileHeight)));
        }
    }
    sprite = frames.at(polarity);
}



void EnemyEntity::move(double delta)
{
    Entity::move(delta);

    if(y > game->height()+100 || x < -100 || x > game->width()+100 || y < -100){
        removeThis = true;
    }
}

void EnemyEntity::draw(QPainter *painter)
{

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    int xOffset = (20.0f/(game->width()/2.0f)*x - 20);
    int yOffset = (20.0f/(game->height()/2.0f)*y - 20);

    shadow->setBlurRadius(8);
    shadow->setOffset(xOffset, yOffset);
    shadow->setColor(QColor(0,0,0,115));
    sprite->drawWithEffect(painter, getX()-20, getY()-20, shadow,20);

    //    Entity::draw(painter);
    painter->setPen(Qt::magenta);
    painter->drawRect(hitBox);
}

void EnemyEntity::doLogic()
{

}

bool EnemyEntity::isDead()
{
    return dead;
}

void EnemyEntity::shoot(int speed, e_ptr target, float deg)
{
    float xDiff = target->getX() - x;
    float yDiff = target->getY() - (y +( sprite->getHeight()/2));

    float rads = atan2f(xDiff,yDiff);
    int gunX = getX();
    int gunY = getY() + (sprite->getHeight()/2);

    e_ptr shot(new EnemyShotEntity(game, gunX, gunY, polarity));
    shot->setHorizontalMovement(speed * sin(rads + qDegreesToRadians(deg)));
    shot->setVerticalMovement(speed * cos(rads + qDegreesToRadians(deg)));

    game->getEntities().push_back(shot);
}

void EnemyEntity::collidedWith(e_ptr other)
{
    if(!dead){
        if(other->getType() == SHOT){

            int dmg = 2;
            if(other->getPolarity() == polarity){
                health -= dmg/2;
            }else{
                health -= dmg * 2;
            }

            if(health <= 0){
                dead = true;
                removeThis = true;
            }
        }
    }
}

EnemyEntity::~EnemyEntity()
{

}
