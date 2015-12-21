#include "enemylaserentity.h"

EnemyLaserEntity::EnemyLaserEntity(GameState *game, int x, int y, polarType polarity):
    EnemyShotEntity(game, x,y,polarity)
{

}

void EnemyLaserEntity::init()
{
    type = ENEMYSHOT;
    trail = pos;
}

void EnemyLaserEntity::draw(QPainter *painter)
{
    painter->save();

    QColor whiteBeam(0,255,255,255);
    QColor blackBeam(255,0,0,255);

    QColor *currentColor = polarity == WHITE? &whiteBeam: &blackBeam;
    currentColor->setAlphaF(0.25f);
    QPen pen(*currentColor, 15, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawLine(trail.x(),trail.y(), pos.x(), pos.y());
    pen.setColor(*currentColor);
    currentColor->setAlphaF(0.5f);
    pen.setWidth(10);
    painter->setPen(pen);
    painter->drawLine(trail.x(),trail.y(), pos.x(), pos.y());
    pen.setColor(polarity == WHITE? Qt::white : Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawLine(trail.x(),trail.y(), pos.x(), pos.y());

//    painter->setPen(Qt::yellow);
//    painter->drawRect(hitBox);

    painter->restore();
}

void EnemyLaserEntity::doLogic(double delta)
{
    trail = pos - (dir * Point(delta,delta));
    hitBox.setRect(getX()-5, getY()-5,10, 10);
}

void EnemyLaserEntity::collidedWith(const e_ptr &other)
{
    EnemyShotEntity::collidedWith(other);
}

