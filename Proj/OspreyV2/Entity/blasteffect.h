#ifndef BLASTEFFECT_H
#define BLASTEFFECT_H

#include "entity.h"



class BlastEffect : public Entity
{
public:
    BlastEffect(GameState *game, int x, int y, polarType polarity,
               int currentRadius, int targetRadius);

    // Entity interface
public:
    void draw(QPainter *painter);
    void doLogic(double delta);

protected:
    QRadialGradient whiteBlast;
    QRadialGradient blackBlast;
    int currentRadius;
    int targetRadius;
};

#endif // BLASTEFFECT_H
