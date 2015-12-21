#include "tilemap.h"
#include "Main/gamewidget.h"

#include <QFile>
#include <QtCore>
#include <QDebug>
#include <QtGlobal>

#include <Util/spritestore.h>

int TileMap::getHeight() const
{
    return height;
}

int TileMap::getWidth() const
{
    return width;
}

float TileMap::getHorizontalMovement() const
{
    return dx;
}

float TileMap::getVerticalMovement() const
{
    return dy;
}

int TileMap::getNumCols() const
{
    return numCols;
}

int TileMap::getNumRows() const
{
    return numRows;
}

int TileMap::getTileWidth() const
{
    return xTileSize;
}

int TileMap::getTileHeight() const
{
    return yTileSize;
}

float TileMap::getX() const
{
    return x;
}

float TileMap::getY() const
{
    return y;
}

void TileMap::setPosition(float x, float y)
{
    //set map coords
    this->x = x;
    this->y = y;

    //check against boundaries
    fixBounds();

    //set drawing offset
    colOffset = -this->x / xTileSize;
    rowOffset = -this->y / yTileSize;


}

void TileMap::setHorizontalMovement(float value)
{
    dx = value;
}

void TileMap::setVerticalMovement(float value)
{
    dy = value;
}
void TileMap::fixBounds()
{
    if (x < xMin) {
        x = xMin;
    }
    if (x > xMax) {
        x = xMax;
    }
    if (y < yMin) {
        y = yMin;
    }
    if (y > yMax) {
        y = yMax;
    }
}

void TileMap::loadMap()
{
    QJsonObject layer = json["layers"].toArray()[0].toObject();
    QJsonArray data = layer["data"].toArray();

    numCols = layer["width"].toInt();
    numRows = layer["height"].toInt();

    map.resize(numCols * numRows +1);

    width = numCols * xTileSize;
    height = numRows * yTileSize;

    //set bounds
    xMin = -width + GameWidget::WIDTH;
    yMin = -height + GameWidget::HEIGHT;
    xMax = 0;
    yMax = 0;

    //parse map JSON data into mapArray
    int index;
    for (int rows = 0; rows < numRows; ++rows) {
        for (int cols = 0; cols < numCols; ++cols) {
            index = cols + (rows * numCols);
            map[index] = data[index].toInt();

        }

    }

}

void TileMap::loadTiles()
{
    QJsonArray array = json["tilesets"].toArray();
    tileSet = *SpriteStore::get().getImage(array[0].toObject()["image"].toString());

    numTilesAcross = tileSet.width() / xTileSize;
    numTilesDown = tileSet.height() / yTileSize;

    tiles.resize(numTilesAcross * numTilesDown);

    for(int row = 0; row < numTilesDown; row++){
        for(int col = 0; col < numTilesAcross; col++){
            tiles[col + (row * numTilesAcross)] = QSharedPointer<QPixmap>(
                        new QPixmap(tileSet.copy(xTileSize * col,
                        yTileSize * row, xTileSize, yTileSize)));
        }
    }
}

QJsonObject TileMap::parseJSON(QString ref)
{
    QFile jsonFile(ref);
    if(!jsonFile.open(QFile::ReadOnly | QFile::Text)){
        qCritical() << "Unable to read File: "<<ref;
        qApp->exit(EXIT_FAILURE);
    }
    QByteArray data = jsonFile.readAll();
    QJsonDocument jsonData(QJsonDocument::fromJson(data));

    return jsonData.object();

}

TileMap::TileMap(QString jsonRef)
{
    json = parseJSON(jsonRef);

    xTileSize = json["tilewidth"].toInt();
    yTileSize = json["tileheight"].toInt();
    numColsToDraw = GameWidget::WIDTH / xTileSize +2;
    numRowsToDraw = GameWidget::HEIGHT / yTileSize +2;

    loadTiles();
    loadMap();
}

void TileMap::move(double delta)
{
    //bound check
    if (dx > 0 && x + dx * delta >= xMax) {
        dx = 0;
        x = xMax;
    }
    if (dx < 0 && x + dx * delta <= xMin) {
        dx = 0;
        x = xMin;
    }
    if (dy > 0 && y + dy * delta >= yMax) {
        dy = 0;
        y = yMax;
    }
    if (dy < 0 && y + dy * delta <= yMin) {
        dy = 0;
        y = yMin;
    }

    //update location based on move speed
    x += (delta * dx);//shift horizontally
    y += (delta * dy);//shift vertically

    setPosition(x, y);

}

void TileMap::draw(QPainter *painter)
{
    for (int row = rowOffset; row < rowOffset + numRowsToDraw; ++row) {//for each row
        if(row >= numRows){//bound check
            break;
        }
        for (int col = colOffset; col < colOffset + numColsToDraw; ++col) {//for each column
            if(col >= numCols){
                break;
            }
            int idx = col + (row * numCols);
            if(map[idx] == 0){//0 is blank so dont draw it
                continue;
            }

            int t =  map[idx] -1;//get map tile value

            //draw each tile in the appropriate position
            painter->drawPixmap( (int)x + col * xTileSize,
                                 (int) y + row * yTileSize, *tiles[t]);
        }
    }
}

