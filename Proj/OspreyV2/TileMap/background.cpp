#include "background.h"
#include <cmath>

Background::Background(QString ref, float ms):
image(ref), moveScale(ms)
{

}

int Background::getX() const
{
    return static_cast<int>(x);
}

int Background::getY() const
{
    return static_cast<int>(y);
}

void Background::setPosition(float x, float y)
{
    this->x = fmod((x * moveScale), image.getWidth());
    this->y = fmod((y * moveScale), image.getHeight());
}

void Background::setMovement(float dx, float dy)
{
    this->dx = dx;
    this->dy = dy;
}

void Background::gameUpdate(double delta)
{
    x += (dx*delta);
    y += (dy*delta);
    //bounds check
    x = fmod( x , image.getWidth());
    y = fmod(y , image.getHeight());
}

void Background::gameRender(QPainter *painter)
{
    image.draw(painter, getX(), getY() );
    int width = 800;
    int height = 600;

    int px = getX();
    int py = getY();


    //draw image tile
    if(image.getHeight() > 0 && image.getWidth() > 0){
        while(px > 0) px -= image.getWidth();
        while(px < width + image.getWidth()){
            while(py > 0) py -= image.getHeight();
            while(py < height + image.getHeight()){
                image.draw(painter, px, py);
                py+= image.getHeight();
            }
            px += image.getWidth();
        }
    }





    //repeat image if it extents beyond bounds
//    if (x + image.getWidth() < width) {
//        image.draw( painter, getX() + image.getWidth(), getY());
//        if (y + image.getHeight() < height) {
//            image.draw(painter, getX() + image.getWidth(), getY() + image.getHeight());
//        }
//        if (y > 0) {
//            image.draw(painter, getX() + image.getWidth(), getY() - image.getHeight());
//        }
//    }
//    if (x > 0) {
//        image.draw( painter, getX() - image.getWidth(), getY());
//        if (y + image.getHeight() < height) {
//            image.draw( painter, getX() - image.getWidth(), getY() + image.getHeight());
//        }
//        if (y > 0) {
//            image.draw( painter, getX() - image.getWidth(), getY() - image.getHeight());
//        }
//    }
//    if (y + image.getHeight() < height) {
//        image.draw( painter, getX(), getY() + image.getHeight());
//        if (x + image.getWidth() < width) {
//            image.draw( painter, getX() + image.getWidth(), getY() + image.getHeight());
//        }
//        if (x > 0) {
//            image.draw( painter, getX() - image.getWidth(), getY() + image.getHeight());
//        }
//    }
//    if (y > 0) {
//        image.draw( painter, getX(), getY() - image.getHeight());
//        if (x + image.getWidth() < width) {
//            image.draw( painter, getX() + image.getWidth(), getY() - image.getHeight());
//        }
//        if (x > 0) {
//            image.draw( painter, getX() - image.getWidth(), getY() - image.getHeight());
//        }
//    }
}

