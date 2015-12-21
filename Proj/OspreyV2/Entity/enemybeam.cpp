#include "blasteffect.h"
#include "enemybeam.h"

EnemyBeam::EnemyBeam(GameState *game, int x, int y, polarType polarity):
    EnemyShotEntity(game, x,y,polarity)
{
    init();
}


void EnemyBeam::init()
{
    type = ENEMYBEAM;
    trail = pos;

    whiteBlast.setColorAt(0, QColor(255,255,255,0));
    whiteBlast.setColorAt(0.25, QColor(192,255,255,0));
    whiteBlast.setColorAt(0.5, QColor(127,255,255,127));
    whiteBlast.setColorAt(0.75, QColor(63,255,255,255));
    whiteBlast.setColorAt(0.9, QColor(0,255,255,127));
    whiteBlast.setColorAt(1, QColor(0,255,255,0));

    blackBlast.setColorAt(0, QColor(0,0,0,0));
    blackBlast.setColorAt(0.25, QColor(63,0,0,0));
    blackBlast.setColorAt(0.5, QColor(127,0,0,127));
    blackBlast.setColorAt(0.75, QColor(192,0,0,255));
    blackBlast.setColorAt(0.9, QColor(255,0,0,127));
    blackBlast.setColorAt(1, QColor(255,0,0,0));

    currentRadius  = 20;
    targetRadius  = 60;
}

void EnemyBeam::draw(QPainter *painter)
{
    painter->save();

    if(!hit){
        QColor whiteBeam(0,255,255,255);
        QColor blackBeam(255,0,0,255);

        QColor *currentColor = polarity == WHITE? &whiteBeam: &blackBeam;
        currentColor->setAlphaF(0.25f);
        QPen pen(*currentColor, 50, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(pen);
        painter->drawLine(trail.x(),trail.y(), pos.x(), pos.y());
        pen.setColor(*currentColor);
        currentColor->setAlphaF(0.5f);
        pen.setWidth(25);
        painter->setPen(pen);
        painter->drawLine(trail.x(),trail.y(), pos.x(), pos.y());
        pen.setColor(polarity == WHITE? Qt::white : Qt::black);
        pen.setWidth(10);
        painter->setPen(pen);
        painter->drawLine(trail.x(),trail.y(), pos.x(), pos.y());
    }else{
        whiteBlast.setCenter(getX(), getY());
        whiteBlast.setFocalPoint(getX(), getY());
        whiteBlast.setRadius(currentRadius);

        blackBlast.setCenter(getX(), getY());
        blackBlast.setFocalPoint(getX(), getY());
        blackBlast.setRadius(currentRadius);

        painter->setBrush(QBrush(polarity == WHITE ? whiteBlast : blackBlast));
        painter->setPen(Qt::transparent);
        painter->drawEllipse(QPoint(getX(), getY()), currentRadius, 20);

    }

//    painter->setPen(Qt::yellow);
//    painter->drawRect(hitBox);

    painter->restore();
}

void EnemyBeam::doLogic(double delta)
{
    if(hit){
        dir.setPoint(0,0);
        if(currentRadius < targetRadius){
            currentRadius += 8;
        }else{
            removeThis = true;
        }
    }

    trail = pos - (dir * Point(delta,delta));
    hitBox.setRect(getX()-20, getY()-20,40, 40);
}


void EnemyBeam::collidedWith(const e_ptr &other)
{
    if(hit){
        return;
    }
    if(other->getType() == PLAYER){
        hit = true;
        if(other->getPolarity() == polarity){
            e_ptr blast(new BlastEffect(game,  getX(), getY(), polarity, width()/2,0));

            game->getEffects().append(blast);
        }else{
            e_ptr blast(new BlastEffect(game,  getX(), getY(), polarity, width()/2,width()));

            game->getEffects().append(blast);
        }
    }
}
