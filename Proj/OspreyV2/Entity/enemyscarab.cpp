#include "enemylaserentity.h"
#include "enemyscarab.h"
#include "shotentity.h"
#include "Util/timer.h"

EnemyScarab::EnemyScarab(GameState *game, int x, int y, polarType polarity,
                         Path *path, QString ref):
    EnemyEntity(game, x, y, polarity, path, ":/sprites/enemy/scarab.png")
{
    Q_UNUSED(ref);
    maxSpeed = 200;
    maxHealth = health = 2000;
    init();
}

EnemyScarab::~EnemyScarab()
{
    for(e_ptr probe: probeList){
        probe->setRemoveThis(true);
    }
    game->removeDeadEntities(probeList);

}


void EnemyScarab::init()
{
    //create path

    path = new Path;
    path->addNode(Point(400,600));
    path->addNode(Point(100,600));
    path->addNode(Point(700,600));
    path->addNode(Point(400,600));
    path->addNode(Point(400,125));
    path->addNode(Point(150,125));
    path->addNode(Point(650,125));

    for (int i = 0; i < 4; ++i) {

        probeOrbits.append(QSharedPointer<Point>( new Point(getX(), getY())));
    }

    orbitRadius = 0;
    orbitSpeedMod = 0.04;
    parseFrames(5,1);
    wings = CLOSED;
    currentFrame = 0;
    sprite = frames.at(currentFrame);
}


void EnemyScarab::draw(QPainter *painter)
{
    EnemyEntity::draw(painter);

}

void EnemyScarab::doLogic(double delta)
{
    //check for dead probes
    game->removeDeadEntities(probeList);

    //do base class logic
    EnemyEntity::doLogic(delta);

    //aim core towards player
    angle = pos.angleTo(targetPlayer);

    //frame animations
    //transition from closed to open and viceversa
    if(Timer::getTime() - lastFrameChange > .04){
        if(wings == CLOSED && currentFrame > 0){
            currentFrame--;
        }else if(wings == OPEN && currentFrame < 4){
            currentFrame++;
        }
        sprite = frames.at(currentFrame);

        lastFrameChange = Timer::getTime();;
    }

    //when center of top center of screen is reahed
    if(currentNode > 4 && wings == CLOSED){
        //open wings
        wings = OPEN;
        //deploy orbital probes
        for(int i = 0; i < 4; i++){
            e_ptr probe = e_ptr(new OrbitalProbe(game, getX(), getY(),
                                           i%2==0? WHITE:BLACK, probeOrbits[i]));
            //add probes to entity lists
            probeList.append(probe);
            game->getEnemyEntities().append(probe);
        }
    }
    //when center of top center of screen is reahed
    //increase orbit radius to target size
    if(currentNode > 4 && orbitRadius < 125 ){
        orbitRadius += 125 * delta;
    }

    //set target positoion for probes
    for(int i = 0; i < 4; i++){
        probeOrbits[i]->setPoint(getX() + qSin(moveTicks*orbitSpeedMod+(1.5708*i)) * orbitRadius,
                                 getY() + qCos(moveTicks*orbitSpeedMod+(1.5708*i)) * orbitRadius);

    }


    //core shot stages
    //shot more when probes die
    if(shotTicks > lastShot){
        lastShot = shotTicks;
        if(shotTicks % 24 == 0){
            //swap polarity at regular intervals
            polarity = polarity == WHITE ? BLACK : WHITE;
        }
        if(currentNode > 4){
            switch(probeList.size()){
            case 4:
                if(shotTicks%24 == 0){
                    orbitSpeedMod = 0.02;
                    shoot(250, Point(getX(), getY()+400),0);
                }
                break;
            case 3:
                if(shotTicks%12 == 0){
                    orbitSpeedMod = 0.04;
                    shoot(250, Point(getX(), getY()+400),0);
                }
                break;
            case 2:
                if(shotTicks%8 == 0){
                    orbitSpeedMod = 0.06;
                    shoot(250, Point(getX(), getY()+400),0);
                }
                break;
            case 1:
                if(shotTicks%4 == 0){
                    orbitSpeedMod = 0.08;
                    shoot(250, Point(getX(), getY()+400),0);
                }
                break;
            case 0:
                if(shotTicks%2 == 0){
                    shoot(250, Point(getX(), getY()+400),0);
                }
                break;
            }

        }
    }

    //speedup when dashing up from bottom of screen. Slowdown when engaged
    maxSpeed = currentNode == 4 ? 800 : currentNode > 4 ? 175 : 300;
}



void EnemyScarab::followPath(double delta)
{
    float dist;
    Point target;
    if(path != NULL){
        target = (path->getNodes().data()[currentNode]);
        dist = pos.distanceTo(target);
        if(dist <= 40){
            currentNode++;

            if(currentNode >= path->getNodes().size()){
                currentNode = path->getNodes().size() -2;
            }
        }
        seek(target,dist, delta);
        return;
    }
    seek(Point(getX(),getY()+1000), 1000, delta);
}

void EnemyScarab::move(double delta, float xShift)
{
    Entity::move(delta, xShift);
    for(e_ptr probe: probeList){
        probe->move(delta, xShift);
    }
}

bool EnemyScarab::collidesWith(const e_ptr &other)
{
    return EnemyEntity::collidesWith(other);
}

void EnemyScarab::collidedWith(const e_ptr &other)
{
    if(!dead && currentNode > 4){
        if(other->getType() == SHOT || other->getType() == BURST){

            hit = true;
            int dmg = qSharedPointerCast<ShotEntity>(other)->getDmg();
            health -= dmg;

            if(health <= 0){
                dead = true;
                removeThis = true;
                if(other->getPolarity() == polarity){
                    for (int i = 0; i < 5; ++i) {
                        shoot(200 +game->rand(-10,10) , targetPlayer, 0);
                    }
                }
            }
        }
    }
}


/*******************************************************************************
 * orbitalProbe
 ******************************************************************************/



OrbitalProbe::OrbitalProbe(GameState *game, int x, int y, polarType polarity,
                           QSharedPointer<Point> &orbit, QString ref):
    EnemyEntity(game,x,y,polarity, NULL, ":/sprites/enemy/probe.png")
{
    Q_UNUSED(ref);
    this->orbit = orbit.data();
    init();
}

void OrbitalProbe::init()
{
    parseFrames(1,2);
    sprite = frames.at(polarity);
    maxSpeed = 0;
    health = maxHealth = 300;

}
OrbitalProbe::~OrbitalProbe()
{

}

void OrbitalProbe::move(double delta, float xShift)
{
    Q_UNUSED(delta);
    Q_UNUSED(xShift);
    pos = *orbit;
}

void OrbitalProbe::draw(QPainter *painter)
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
        sprite->drawShaded(painter, 0, 0, 0.8f, Qt::white);
        hit = false;
    }
//        sprite->drawShaded(painter, 0, 0, 1.0f, Qt::white);
    painter->setPen(Qt::white);
    painter->drawEllipse(QPoint(0,0),10,10);
    painter->restore();
}

void OrbitalProbe::doLogic(double delta)
{
    Q_UNUSED(delta);
    //set target to random player position if one exists, else target is straight down
    targetPlayer.setPoint(getX(), getY()+500);

    elapsed = Timer::getTime() - startTime;

    if(Timer::getTime() - ticker > 0.04){//approx 25ticks/sec
        moveTicks++;
        shotTicks++;
        ticker = Timer::getTime();
    }

   //update hitBox
    hitBox.setCoords(getX() - sprite->getWidth()/2, getY() - sprite->getHeight()/2,
                     getX() + sprite->getWidth()/2, getY() + sprite->getHeight()/2);


    if(shotTicks > lastShot){
        lastShot = shotTicks;
        if(shotTicks > 25){
//            shoot(500,targetPlayer,0);
            float rads = qDegreesToRadians(angle);
            gun.setX(getX() + qSin(rads)*sprite->getHeight()/2);
            gun.setY(getY() + qCos(rads)*sprite->getHeight()/2);


            e_ptr shot(new EnemyLaserEntity(game, gun.x(), gun.y(), polarity));
            shot->setHorizontalMovement(1000 * sin( qDegreesToRadians(gun.angleTo(targetPlayer))));
            shot->setVerticalMovement(1000 * cos( qDegreesToRadians(gun.angleTo(targetPlayer))));

            game->getEnemyEntities().append(shot);
        }
    }

}





