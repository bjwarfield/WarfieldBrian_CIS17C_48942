#include "blasteffect.h"
#include "enemyentity.h"
#include "shotentity.h"


int ShotEntity::getDmg() const
{
    return dmg;
}
ShotEntity::ShotEntity(GameState *game, int x, int y, polarType polarity):
Entity(game, x,y,":/sprites/player/polarLaser.png"),shotSpeed(1000),
  hit(false),dmg(2)
{
    this->polarity = polarity;
    type = SHOT;

    dir.ry() = -shotSpeed;

    int tileWidth = sprite->getWidth()/2;
    int tileHeight = sprite->getHeight();
    frames.resize(2);
    for(int i=0; i<frames.size(); i++){
        frames.data()[i] = s_ptr(
                    new Sprite(sprite->getRef(), sprite->getImage().copy(
                       tileWidth*i, 0, tileWidth, tileHeight)));

    }

    sprite = frames.at(polarity);
    hitBox.setRect(getX()-sprite->getWidth()/2,
                   getY()-sprite->getHeight()/2,
                   sprite->getWidth(),
                   sprite->getHeight());

    Sprite frags(":/sprites/player/shotFrags.png");

    int cols = 4;
    int rows = 2;
    tileWidth = frags.getWidth()/cols;
    tileHeight = frags.getHeight()/rows;

    fragFrames.resize(cols * rows);

    for(int col = 0; col < cols; col++){
        for(int row = 0; row < rows; row++){
            fragFrames[col + row*cols] = s_ptr(new Sprite(frags.getRef(),
                        frags.getImage().copy(
                        tileWidth*col, tileHeight*row,
                        tileWidth, tileHeight)));
        }
    }
    currentFrag = 0;



}



void ShotEntity::draw(QPainter *painter)
{
    if(!hit){
        Entity::draw(painter);
    }else{
        fragFrames[currentFrag + polarity*4]->draw(painter, getX(),getY());
    }
//    painter->setPen(Qt::green);
//    painter->drawRect(hitBox);
}


void ShotEntity::doLogic(double delta)
{
    Q_UNUSED(delta);
    if(hit){
        if(currentFrag < 3){
            currentFrag++;
        }else{
            removeThis = true;
        }
    }
}
void ShotEntity::move(double delta)
{
    if(!hit){
        Entity::move(delta);
    }


    if(getY() < -150){
        removeThis = true;
    }
}

void ShotEntity::move(double delta, float xShift)
{
    Entity::move(delta, xShift);


    if(getY() < -150){
        removeThis = true;
    }
}

void ShotEntity::move(double delta, float xShift, float yShift)
{
    Entity::move(delta, xShift, yShift);
    if(getY() < -150){
        removeThis = true;
    }
}

bool ShotEntity::getHit() const
{
    return hit;
}

void ShotEntity::collidedWith(const e_ptr &other)
{
    if(hit){
        return;
    }

    if(other->getType() == ENEMY){
        if(qSharedPointerCast<EnemyEntity>(other)->isDead()){
            return;
        }
        hit = true;
//        removeThis = true;
//        qDebug()<<"Shot hit Enemy";
    }
}

ShotEntity::~ShotEntity()
{
//    qDebug()<<"Shot Destroyed: " <<x;
}




