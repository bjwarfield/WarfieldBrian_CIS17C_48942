#include "Entity/burstshot.h"
#include "blasteffect.h"
#include "enemyentity.h"
#include <QtMath>

BurstShot::BurstShot(GameState *game, int x, int y, float angle,
                     polarType polarity): ShotEntity(game,x,y,polarity)
{
//    this->game = game;
//    this->x = x;
//    this->y = y;
//    this->polarity = polarity;
    this->angle = angle;
    this->dmg = 10;
    shotSpeed = 750;
    rotatesSpeed = 1080;

    type = BURST;
//    ticker = 0;
//    ticks = 0;
//    lastTick = 0;
//    angle = 90;

    trail.prepend(Point(x,y));
    target.rx() = getX();
    target.ry() = getY()-1000;
    targetAngle = qRadiansToDegrees(qAtan2(target.x()-getX(),target.y()-getY()));
    angleDistance = targetAngle - angle;
    if (angleDistance > 180) {
        angleDistance -= 360;
    } else if (angleDistance < -180) {
        angleDistance += 360;
    }

}

BurstShot::~BurstShot()
{

}


void BurstShot::doLogic(double delta)
{
    Q_UNUSED(delta);
    //set target to point directly above shot
    target.rx() = getX();
    target.ry() = getY()-1000;
    targetDistance = pos.distanceTo(target);
    //target closest enemy if exists
    if(game->getEnemyEntities().size() > 0){
        for(e_ptr enemy: game->getEnemyEntities()){
            if(enemy->getType() == ENEMY){//if the target is not a bullet
                if(pos.distanceTo(enemy->getPos()) < targetDistance){
                    //if distance to enemy is shorter than current target
                    //set it as new target
                    target.rx() = enemy->getX();
                    target.ry() = enemy->getY();
                    targetDistance = pos.distanceTo( target);
                }
            }
        }
    }
    angle = fmod((angle + 360),360.0f);//bind range between 0 and 360
    targetAngle = qRadiansToDegrees(qAtan2(target.x()-getX(),target.y()-getY()));
    angleDistance = targetAngle - angle;
    if (angleDistance > 180) {
        angleDistance -= 360;
    } else if (angleDistance < -180) {
        angleDistance += 360;
    }


}


void BurstShot::move(double delta)
{
    steerShot(delta);

    if(!hit){
        //move
        pos.rx() += (delta * dir.x());
        pos.ry() += (delta * dir.y());

    }

   setTrail();
}

void BurstShot::move(double delta, float xShift)
{
    steerShot(delta);

    if(!hit){
        //move
        pos.rx() += (delta * (dir.x() + xShift));
        pos.ry() += (delta * dir.y());
    }


    setTrail();
}

void BurstShot::move(double delta, float xShift, float yShift)
{
    steerShot(delta);

    if(!hit){
        //move
        pos.rx() += (delta * (dir.x() + xShift));
        pos.ry() += (delta * (dir.y() + yShift));
    }


    setTrail();

}

void BurstShot::steerShot(double delta)
{
    if(angleDistance > 0){
        angle = angle + (rotatesSpeed * delta) > angleDistance + angle ?
                    targetAngle :
                    angle + (rotatesSpeed * delta);
    }else{
        angle = angle - (rotatesSpeed * delta) < angleDistance + angle ?
                    targetAngle :
                    angle - (rotatesSpeed * delta);
    }
//    angle = angleDistance > 0? angle + (rotatesSpeed * delta) :
//                               angle - (rotatesSpeed * delta);

    setHorizontalMovement(qSin(qDegreesToRadians(angle)) * shotSpeed);
    setVerticalMovement(qCos(qDegreesToRadians(angle)) * shotSpeed);

//    rotatesSpeed += 90*delta;
    shotSpeed += 2000*delta;
}

void BurstShot::setTrail(){
    hitBox.setCoords(getX()-5, getY()-5,getX()+5,getY()+5);

    Point currentPos(getX(),getY());
    if(currentPos.distanceTo( trail.first()) > 3){
        trail.prepend(currentPos);
    }

    while (trail.size() > 15) {
       trail.pop_back();
    }
    if(hit){
        trail.pop_back();
    }

    if(getX() < -100 || getX() > game->width()+100 || getY() < -100 || getY() > game->height()+100){
        hit = true;
    }
    if(trail.isEmpty()){
        removeThis = true;

    }
}

void BurstShot::draw(QPainter *painter)
{
    painter->save();
    QColor whiteBeam(0,255,255,255);
    QColor blackBeam(255,0,0,255);

    QColor *currentColor = polarity == WHITE? &whiteBeam: &blackBeam;
    currentColor->setAlphaF(0.25f);
    QPen pen(*currentColor, 15, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    drawLines(painter, 15);
    currentColor->setAlphaF(0.5f);
    pen.setColor(*currentColor);
    pen.setWidth(4);
    painter->setPen(pen);
    drawLines(painter, 10);
    pen.setColor(polarity == WHITE? Qt::white : Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    drawLines(painter, 5);


    //debug
//    pen.setColor(Qt::green);
//    painter->setPen(pen);
//    painter->drawRect(hitBox);

    painter->restore();
}

void BurstShot::drawLines(QPainter *painter, int maxSegments){
    painter->drawLine(getX(),getY(), trail[0].x(),trail[0].y());

    for(int i = 0; i < trail.size()-1 && i < maxSegments; i++){
        painter->drawLine(trail[i].x(), trail[i].y(), trail[i+1].x(), trail[i+1].y());
    }
}



//bool BurstShot::collidesWith(e_ptr other)
//{
//    for(int i = 0; i < trail.size()-1; i++){
//        int x1, x2, y1, y2;
//        if(trail[i].x() < trail[i+1].x()){
//            x1 = trail[i].x();
//            x2 = trail[i+1].x();
//            y1 = trail[i].y();
//            y2 = trail[i+1].y();
//        }else{
//            x1 = trail[i+1].x();
//            x2 = trail[i].x();
//            y1 = trail[i+1].y();
//            y2 = trail[i].y();
//        }
//        for(int xq = x1; xq < x2; x++){
//            int yq = y1 + ((y2-y1)/(x2-x1)) *(xq -x1);
//            if(other->getHitBox().contains(xq, yq)){
//                return true;
//            }
//        }
//    }
//    return false;
//}





void BurstShot::collidedWith(const e_ptr &other)
{
    if(other->getType() == ENEMY){
        if(!(static_cast<EnemyEntity *>(other.data())->isDead())){
            hit = true;
            e_ptr blast(new BlastEffect(game,  getX(), getY(), polarity, width()/2,width()));
            game->getEffects().append(blast);
        }
    }
}


//float BurstShot::getDistance(QPoint a, QPoint b)
//{
//    return qSqrt(qPow((b.x() - a.x()), 2) + qPow((b.y() - a.y()),2));
//}


