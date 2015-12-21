#ifndef FONT_H
#define FONT_H

#include <QPixMap>





class Font
{
public:
    Font(QString ref);
    Font(QString ref, QString met);
    int getStringWidth(QString &text) const;
    int getHeight() const;
    void draw(QPainter *painter, QString text, int x, int y);
private:
    int tileWidth;
    int tileHeight;

    QPixmap map;
    QPixmap tiles[256];
    int metrics[256];

    void getTiles();

    void fail(QString mes);
};

#endif // FONT_H
