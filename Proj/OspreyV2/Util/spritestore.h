#ifndef SPRITESTORE_H
#define SPRITESTORE_H

#include "sprite.h"
#include "Container/hash.h"
#include <iostream>
#include <QHash>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDebug>


typedef QSharedPointer<QPixmap> p_ptr;
class SpriteStore
{

public:
    static SpriteStore& get(){
        static SpriteStore store;
        return store;
    }
    QPixmap *getImage(QString ref){
        if(!images[ref].isNull()){
            return images[ref].data();
        }


        QFileInfo file(ref);
        if(!file.exists()) fail("Unable to find ref: "+ref);

        p_ptr image(new QPixmap(ref));
        if (image.isNull()) fail("Unable to load ref: "+ref);

        images[ref]=image;

        return images[ref].data();
    }


private:
    //maintain singleton status
    SpriteStore():images(255){}


    SpriteStore(SpriteStore const&) = delete;
    void operator=(SpriteStore const&) = delete;

    Hash<p_ptr> images;
//    QHash<QString,p_ptr> images;

    void fail(QString mes){
        qCritical() << mes;
        QCoreApplication::exit(EXIT_FAILURE);
    }


};

#endif // SPRITESTORE_H
