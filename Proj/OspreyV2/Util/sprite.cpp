#include "sprite.h"
#include "spritestore.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


Sprite::Sprite(QString ref):
    ref(ref), image(*SpriteStore::get().getImage(ref))
{

}

Sprite::Sprite(QString ref, QPixmap img):
    ref(ref), image(img)
{

}

int Sprite::getWidth()
{
    return image.width();
}

int Sprite::getHeight()
{
    return image.height();
}

void Sprite::draw(QPainter *painter, int x, int y)
{
    painter->drawPixmap(x-image.width()/2, y-image.height()/2, image);
}

void Sprite::drawShaded(QPainter *painter, int x, int y, float alpha, QColor color)
{
    QPixmap shaded = image;
    QPainter shader(&shaded);
    shader.setCompositionMode(QPainter::CompositionMode_SourceIn);
    shader.setOpacity(alpha);
    shader.fillRect(shaded.rect(), color);
    shader.end();

    painter->drawPixmap(x-image.width()/2, y-image.height()/2, shaded);
}

void Sprite::drawWithEffect(QPainter *painter, int x, int y,
                            QGraphicsEffect *effect, int ext){
    if(image.isNull()){return;}
    if(!effect){return;}

    QGraphicsScene  scene;
    QGraphicsPixmapItem item;
    item.setPixmap(image);
    item.setGraphicsEffect(effect);
    scene.addItem(&item);

    QImage result(image.size()+QSize(ext*2, ext *2), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter ptr(&result);
    scene.render(&ptr, QRectF(),QRectF(-ext, -ext, image.width()+ext*2, image.height()+ext*2 ));

    painter->drawImage(x-image.width()/2, y-image.height()/2,result);
}

QString Sprite::getRef() const
{
    return ref;
}
QPixmap Sprite::getImage() const
{
    return image;
}

Sprite::~Sprite()
{

}




