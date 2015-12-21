#include "Entity/enemyentity.h"
#include "Entity/enemyshotentity.h"
#include "Entity/shotentity.h"
#include "Util/timer.h"


EnemyEntity::EnemyEntity(GameState *game, int x, int y, polarType polarity, Path *path, QString ref):
    Entity(game, x,y,ref)
{
    this->path = path;
    this->polarity = polarity;

    //init timers
    startTime = Timer::getTime();
    aDelta = 0;
    ticker = moveTicks = lastMove = shotTicks = lastShot = 0;

    currentNode = 0;
    targetPlayer.setPoint(x, y+10);

    //init status
    hit = false;
    dead = false;
    type = ENEMY;

    //init movement
    dir.setPoint(0,0);



}

void EnemyEntity::init()
{
    //    this->path = new Path;
    //    this->path->addNode(Point(700,500));
    //    this->path->addNode(Point(100,100));
    //    this->path->addNode(Point(100,500));
    //    this->path->addNode(Point(700,100));
    //    this->path->addNode(Point(1000,100));

        //enemy stats
        maxHealth = 20;
        health = 20;
        value = 100;
        maxSpeed = 250;

        //assume 2 frames: topDown White/Black polarity
        int cols = 1;
        int rows = 2;
        parseFrames(cols, rows);

        sprite = frames.at(polarity);

        //set Gun pos
        gun.setPoint(getX(), getY() + sprite->getHeight() /2);
}
void EnemyEntity::parseFrames(int cols, int rows)
{
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
}

void EnemyEntity::draw(QPainter *painter)
{
    painter->save();

    QTransform trans;
    trans.translate(getX(), getY());
    trans.rotate(-angle);

    painter->setTransform(trans);


    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    int xOffset = (20.0f/(game->width()/2.0f)*getX() - 20);
    int yOffset = (20.0f/(game->height()/2.0f)*getY() - 20);

    shadow->setBlurRadius(8);
    shadow->setOffset(xOffset, yOffset);
    shadow->setColor(QColor(0,0,0,115));
    sprite->drawWithEffect(painter, -20, -20, shadow,20);
    if(hit){
        sprite->drawShaded(painter, 0, 0, .8f, Qt::white);
        hit = false;
    }

    painter->restore();
    painter->save();

    //hitbox
//    painter->setPen(Qt::magenta);
//    painter->drawRect(hitBox);


//    //current velocity
//    painter->setPen(Qt::green);
//    painter->drawLine(getX(),
//                      getY(),
//                      getX() + dir.x(),
//                      getY() + dir.y()
//                      );
    //desired velocity
//    painter->setPen(Qt::blue);
//    painter->drawLine(getX(),
//                      getY(),
//                      getX() + tv.x(),
//                      getY() + tv.y());

//    //steering vector
//    painter->setPen(Qt::yellow);
//    painter->drawLine(getX() + dir.x(),
//                      getY() + dir.y(),
//                      getX() + dir.x() + (tv.x() - dir.x()) * 0.5f,
//                      getY() + dir.y() + (tv.y() - dir.y()) * 0.5f);


    painter->restore();
}

void EnemyEntity::doLogic(double delta)
{
     angle = fmodf((angle + 360) , 360);//bind range between 0 and 360

     //set target to random player position if one exists, else target is straight down
     if(game->getPlayers().size() > 0){
         int idx  = game->rand(0,game->getPlayers().size()-1);
         e_ptr player = game->getPlayers()[idx];
         targetPlayer = player->getPos();
     }else{
         targetPlayer.setPoint(getX(), getY()+30);
     }
     elapsed = Timer::getTime() - startTime;

     if(Timer::getTime() - ticker > 0.04){//approx 25ticks/sec
         moveTicks++;
         shotTicks++;
         ticker = Timer::getTime();
     }

    //update hitBox
     hitBox.setCoords(getX() - sprite->getWidth()/2, getY() - sprite->getHeight()/2,
                      getX() + sprite->getWidth()/2, getY() + sprite->getHeight()/2);


     aDelta += delta;
     if(aDelta > 0.1){
         followPath(aDelta);
         aDelta = 0;
     }
     angle = pos.angleTo(pos + dir);
}

void EnemyEntity::seek(const Point &trgt,float dist, double delta)
{
    tv = (trgt - pos).normalize() * Point(qMin(maxSpeed,dist) ,qMin(maxSpeed,dist));
    sv = (tv - dir) * Point(delta, delta);
    dir = dir + sv;
}


bool EnemyEntity::isDead()
{
    return dead;
}

void EnemyEntity::shoot(int speed, const e_ptr &target, float deg)
{

    shoot(speed,target->getPos(),deg );

}

void EnemyEntity::shoot(int speed, Point target, float deg){
    float rads = qDegreesToRadians(angle);
    gun.setX(getX() + qSin(rads)*sprite->getHeight()/2);
    gun.setY(getY() + qCos(rads)*sprite->getHeight()/2);


    e_ptr shot(new EnemyShotEntity(game, gun.x(), gun.y(), polarity));
    shot->setHorizontalMovement(speed * sin( qDegreesToRadians(gun.angleTo(target))
                                             + qDegreesToRadians(deg)));
    shot->setVerticalMovement(speed * cos( qDegreesToRadians(gun.angleTo(target))
                                           + qDegreesToRadians(deg)));

    game->getEnemyEntities().append(shot);
}

void EnemyEntity::collidedWith(const e_ptr &other)
{
    if(!dead){
        if(other->getType() == SHOT || other->getType() == BURST){

            hit = true;
            int dmg = qSharedPointerCast<ShotEntity>(other)->getDmg();
            if(other->getPolarity() == polarity){
                health -= dmg;
            }else{
                health -= dmg * 2;
            }

            if(health <= 0){
                dead = true;
                removeThis = true;
                if(other->getPolarity() == polarity){
                    for (int i = 0; i < 15; ++i) {
                        shoot(200 +game->rand(-30,30) , targetPlayer, game->rand(-20,20)/5.0);
                    }
                }
            }
        }
    }
}

void EnemyEntity::boundCheck()
{
    //bound check. Remove entity if it strays too far off entity map
    if (getX() + (width() / 2) <  -50
            || getX() - (width() / 2) > game->width()+ 50
            || getY() - (height() / 2) > game->height() + 50
            || getY() + (height() / 2) < - 400) {
        removeThis = true;
    }
}

EnemyEntity::~EnemyEntity()
{
    if(path != NULL){
        delete path;
    }
}




void EnemyEntity::followPath(double delta)
{
    float dist;
    Point target;
    if(path != NULL){
        target = (path->getNodes().data()[currentNode]);
        dist = pos.distanceTo(target);
        if(dist <= 40){
            currentNode++;

            if(currentNode >= path->getNodes().size()){
                currentNode = path->getNodes().size() -1;
            }
        }
        seek(target,dist, delta);
        return;
    }
     seek(Point(getX(),getY()+1000), 1000, delta);
}


