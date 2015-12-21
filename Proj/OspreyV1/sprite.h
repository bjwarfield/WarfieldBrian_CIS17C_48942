#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsEffect>
#include <QPainter>
#include <QPixMap>



class Sprite
{
public:
    Sprite(QString ref);
    Sprite(QString ref, QPixmap img);

    int getWidth();
    int getHeight();
    virtual void draw(QPainter * painter, int x, int y);

    void drawShaded(QPainter * painter, int x, int y, float alpha, QColor color);
    QString getRef() const;

    QPixmap getImage() const;



    virtual ~Sprite();

    void drawWithEffect(QPainter *painter, int x, int y,
                        QGraphicsEffect *effect, int ext = 0);
private:
    QString ref;
    QPixmap image;

};

#endif // SPRITE_H
