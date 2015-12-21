#include "enemybeam.h"
#include "enemycruiser.h"


EnemyCruiser::EnemyCruiser(GameState *game, int x, int y, polarType polarity, Path *path, QString ref):
    EnemyEntity(game, x, y, polarity, path, ":/sprites/enemy/cruiser.png" )
{
    Q_UNUSED(ref);
    init();
}

void EnemyCruiser::init()
{
//    this->path = new Path;
//    this->path->addNode(Point(100,200));
//    this->path->addNode(Point(700,300));
//    this->path->addNode(Point(100,400));
//    this->path->addNode(Point(700,500));
//    this->path->addNode(Point(400,1000));
    maxHealth = health = 200;
    maxSpeed = 225;
    value = 150;

    int cols = 4;
    int rows = 2;
    parseFrames(cols, rows);

    currentFrame = 0;
    sprite = frames.at(currentFrame + polarity*4);
    lastFrameChange = 0;

    //set Gun pos
    gun.setPoint(getX(), getY() + sprite->getHeight() /2);
}

void EnemyCruiser::shoot()
{
    gun.setPoint(getX(), getY() + sprite->getHeight() /2);
    e_ptr beam(new EnemyBeam(game, gun.x(), gun.y(), polarity));
    beam->setVerticalMovement(400);
    game->getEnemyEntities().append(beam);
}



void EnemyCruiser::doLogic(double delta)
{
    //frams animation
    if(elapsed - lastFrameChange > 0.04){
        lastFrameChange = elapsed;
        currentFrame++;
        currentFrame = currentFrame%4;
        sprite = frames[currentFrame + polarity*4];
    }

    //fire da CANON
    if(shotTicks > lastShot){
        lastShot = shotTicks;
        if(shotTicks > 45){
            shoot();
        }

    }


    EnemyEntity::doLogic(delta);
    angle = 0;
}

