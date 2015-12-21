#include "enemyshotentity.h"

EnemyShotEntity::EnemyShotEntity(GameWidget *game, int x, int y, polarType polarity):
    Entity(x,y,":/resources/sprites/enemy/enemyShot.png"), game(game),
    hit(false)
{
    this->polarity = polarity;
    type = ENEMYSHOT;

    int tileHeight = sprite->getHeight()/2;

    frames.resize(2);

    for(int i = 0; i < frames.size(); i++){
        frames.data()[i] = s_ptr(new Sprite(
                    sprite->getRef(), sprite->getImage().copy(
                        0, tileHeight*i, sprite->getWidth(), tileHeight)));
    }

    sprite = frames.at(this->polarity);
}

void EnemyShotEntity::move(double delta)
{
    Entity::move(delta);
    if(y < -50 || y > game->height()+50 || x < -50 || x > game->width()+50 ){
        removeThis = true;
    }
}

void EnemyShotEntity::draw(QPainter *painter)
{
    Entity::draw(painter);
}

void EnemyShotEntity::doLogic()
{
}

void EnemyShotEntity::collidedWith(e_ptr other)
{
    if(hit){
        return;
    }
    if(other->getType() == PLAYER){
        hit = true;
        removeThis = true;
    }

}

EnemyShotEntity::~EnemyShotEntity()
{

}
