#include "font.h"
#include "Util/spritestore.h"
Font::Font(QString ref):
    map(*SpriteStore::get().getImage(ref))
{

    //get dimentions
    tileWidth = map.width()/16;
    tileHeight = map.height() /16;

    //split map into tiles array
    for (int row = 0; row< 16; ++row) {
        for (int col = 0; col < 16; ++col) {
            tiles[col + (row*16)] = map.copy(col * tileWidth, row * tileHeight,
                                             tileWidth, tileHeight);
            metrics[col + (row*16)] = tileWidth;//set metrics value to tilewidth

        }
    }

}

Font::Font(QString ref, QString met):
     map(*SpriteStore::get().getImage(ref))
{
    //correct tile metrics values

    //open metrics file
    QFile file(met);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        file.close();
        fail("Unable to load ref: "+met);
    }

    QTextStream stream(&file);
    stream.setIntegerBase(16);

    // parse metrics file into array
    for (int i = 0; i < 16; ++i) {

        for (int j = 0; j < 8; ++j) {
            int value  = stream.read(5).trimmed().toInt(0,16);

            metrics[(2*j)+(i*16)] = value / 0x100;
            metrics[(2*j)+(i*16)+1] = value % 0x100;

        }
        stream.flush();
    }
    file.close();

    tileWidth = map.width()/16;
    tileHeight = map.height() /16;

    //split map into tiles array with metrics widths
    for (int row = 0; row< 16; ++row) {
        for (int col = 0; col < 16; ++col) {
            tiles[col + (row*16)] = map.copy(col * tileWidth, row * tileHeight,
                                             metrics[col + (row*16)], tileHeight);
        }
    }
 }

void Font::getTiles()
{

}

int Font::getStringWidth(QString &text) const{
    int len = 0;
    for (int i = 0; i < text.length(); ++i) {
        len +=  metrics[(int) text[i].toLatin1()];
    }
    return len;
}

int Font::getHeight() const{
    return tileHeight;
}

void Font::draw(QPainter *painter, QString text, int x, int y){
    //track pixel span
    int len = 0;

    for (int i = 0; i < text.length(); ++i) {
        //get ascii value
        int c = text[i].toLatin1();

        //skip out of range chars
        if (c < 0 || c > 255) {
            continue;
        }

        painter->drawPixmap(x+len,y, tiles[c]);
        len += metrics[c];

    }
}

void Font::fail(QString mes){
    qCritical() << mes;
    QCoreApplication::exit(EXIT_FAILURE);
}


