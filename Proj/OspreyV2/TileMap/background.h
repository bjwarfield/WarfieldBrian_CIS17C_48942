#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <Util/sprite.h>



class Background
{
private:
    Sprite image;

    float x;
    float y;

    float dx;
    float dy;

    float moveScale;


public:
    Background(QString ref, float ms);

    int getX() const;
    int getY() const;

    void setPosition(float x, float y);
    void setMovement(float dx, float dy);
    void gameUpdate(double delta);
    void gameRender(QPainter *painter);
};

#endif // BACKGROUND_H
