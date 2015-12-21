#include "enemyentity.h"
#include "shotentity.h"



ShotEntity::ShotEntity(GameWidget *game, int x, int y, polarType polarity):
Entity(x,y,":/resources/sprites/player/polarLaser.png"),shotSpeed(1000),
  hit(false),game(game)
{
    this->polarity = polarity;
    type = SHOT;

    dy = -shotSpeed;

    int tileWidth = sprite->getWidth()/2;

    frames.resize(2);
    for(int i=0; i<frames.size(); i++){
        frames.data()[i] = s_ptr(
                    new Sprite(sprite->getRef(), sprite->getImage().copy(
                       tileWidth*i, 0, tileWidth, sprite->getHeight())));

    }

    sprite = frames.at(polarity);
    hitBox.setRect(getX()-sprite->getWidth()/2,
                   getY()-sprite->getHeight()/2,
                   sprite->getWidth(),
                   sprite->getHeight());

}

void ShotEntity::draw(QPainter *painter)
{
    Entity::draw(painter);
//    painter->setPen(Qt::green);
//    painter->drawRect(hitBox);
}

void ShotEntity::move(double delta)
{
    Entity::move(delta);


    if(y < -150){
        removeThis = true;
    }
}

void ShotEntity::doLogic()
{

}


bool ShotEntity::getHit() const
{
    return hit;
}

void ShotEntity::collidedWith(e_ptr other)
{
    if(hit){
        return;
    }

    if(other->getType() == ENEMY){
        if(qSharedPointerCast<EnemyEntity>(other)->isDead()){
            return;
        }
        hit = true;
        removeThis = true;
//        qDebug()<<"Shot hit Enemy";
    }
}

ShotEntity::~ShotEntity()
{
//    qDebug()<<"Shot Destroyed: " <<x;
}




