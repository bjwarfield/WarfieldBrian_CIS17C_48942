#include "blasteffect.h"

#include <Util/timer.h>

BlastEffect::BlastEffect(GameState *game, int x, int y, polarType polarity,
                         int currentRadius, int targetRadius):
    Entity(game, x, y, ":/sprites/blank.png"),
    currentRadius(currentRadius), targetRadius(targetRadius)
{
    this->polarity = polarity;
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


}


void BlastEffect::doLogic(double delta)
{
    Q_UNUSED(delta);


    if(currentRadius != targetRadius){
        if(currentRadius > targetRadius){
            currentRadius--;
        }else{
            currentRadius++;
        }
    }else{
        removeThis = true;
    }

    whiteBlast.setCenter(getX(), getY());
    whiteBlast.setFocalPoint(getX(), getY());
    whiteBlast.setRadius(currentRadius);

    blackBlast.setCenter(getX(), getY());
    blackBlast.setFocalPoint(getX(), getY());
    blackBlast.setRadius(currentRadius);


}

void BlastEffect::draw(QPainter *painter)
{
    painter->save();

    painter->setBrush(QBrush(polarity == WHITE ? whiteBlast : blackBlast));
    painter->setPen(Qt::transparent);
    painter->drawEllipse(QPoint(getX(), getY()), currentRadius, currentRadius);

    painter->restore();
}
