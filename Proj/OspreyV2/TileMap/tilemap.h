#ifndef TILEMAP_H
#define TILEMAP_H

#include <QJsonObject>
#include <QPixMap>

#include <Container/simplevector.h>



class TileMap
{
private:
    float x;
    float y;
    float dx;
    float dy;

    int xMin;
    int yMin;
    int xMax;
    int yMax;

    QJsonObject json;
    Vector<int> map;
    int xTileSize;
    int yTileSize;
    int numCols;
    int numRows;
    int width;
    int height;

    QPixmap tileSet;
    int numTilesAcross;
    int numTilesDown;
    Vector<QSharedPointer<QPixmap> > tiles;

    int rowOffset;
    int colOffset;
    int numRowsToDraw;
    int numColsToDraw;

    void fixBounds();
    void loadMap();
    void loadTiles();
    QJsonObject parseJSON(QString ref);


public:
    TileMap(QString jsonRef);


    void move(double delta);
    void draw(QPainter *painter);

    int getHeight() const;
    int getWidth() const;
    float getHorizontalMovement() const;
    float getVerticalMovement() const;
    int getNumCols() const;
    int getNumRows() const;
    int getTileWidth() const;
    int getTileHeight() const;
    float getX() const;
    float getY() const;

    void setPosition(float x, float y);
    void setHorizontalMovement(float value);
    void setVerticalMovement(float value);
};

#endif // TILEMAP_H
