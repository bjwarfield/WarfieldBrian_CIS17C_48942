#include "blasteffect.h"
#include "enemyshotentity.h"

EnemyShotEntity::EnemyShotEntity(GameState *game, int x, int y, polarType polarity):
    Entity(game, x,y,":/sprites/enemy/enemyShot.png"), hit(false)
{
    this->polarity = polarity;
    init();
}

void EnemyShotEntity::init()
{
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

void EnemyShotEntity::draw(QPainter *painter)
{
    Entity::draw(painter);
}

void EnemyShotEntity::doLogic(double delta)
{
    Q_UNUSED(delta);
}

void EnemyShotEntity::collidedWith(const e_ptr &other)
{
    if(hit){
        return;
    }
    if(other->getType() == PLAYER){
        hit = true;
        removeThis = true;
        if(other->getPolarity() == polarity){
            e_ptr blast(new BlastEffect(game,  getX(), getY(), polarity, width()/2,0));
//            blast->setHorizontalMovement(pos.x() - other->getHorizontalMovement());
//            blast->setVerticalMovement(pos.y() - other->getVerticalMovement());
            game->getEffects().append(blast);
        }else{
            e_ptr blast(new BlastEffect(game,  getX(), getY(), polarity, width()/2,width()));
//            blast->setHorizontalMovement(dir.x());
//            blast->setVerticalMovement(dir.y());
            game->getEffects().append(blast);
        }
    }

}

EnemyShotEntity::~EnemyShotEntity()
{

}


