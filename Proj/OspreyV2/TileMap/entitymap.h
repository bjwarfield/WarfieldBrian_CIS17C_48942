#ifndef ENTITYMAP_H
#define ENTITYMAP_H

#include "TileMap/tilemap.h"
#include "GameState/gamestate.h"
#include "Entity/entity.h"
#include "Entity/enemyentity.h"

#include <Container/tree.h>


struct EnemyEntry{
    int             spawnTrigger;
    QString         enemyClass;
    polarType       polarity;
    int             spawnX;
    int             spawnY;
    QVector<Point>  paths;
    QString         spawnRef;

    EnemyEntry():   spawnTrigger(0), enemyClass("EnemyProbe"),
        polarity(WHITE), spawnX(0), spawnY(0), spawnRef(""){}

    //copy constructor
    EnemyEntry(const EnemyEntry &entry):
    spawnTrigger(entry.spawnTrigger), enemyClass(entry.enemyClass),
    polarity(entry.polarity), spawnX(entry.spawnX),
    spawnY(entry.spawnY), paths(entry.paths),spawnRef(entry.spawnRef){}

    //assignment operator
    void operator =(const EnemyEntry &other){
        spawnTrigger = other.spawnTrigger;
        enemyClass = other.enemyClass;
        polarity = other.polarity;
        spawnX = other.spawnX;
        spawnY = other.spawnY;
        paths = other.paths;
        spawnRef = other.spawnRef;
    }

    //comparicon operators
    bool operator <(const EnemyEntry &other)const{
        if(spawnTrigger == other.spawnTrigger){
            if(spawnX == other.spawnX){
                return spawnY < other.spawnY;
            }
            return spawnX < other.spawnX;
        }
        return spawnTrigger < other.spawnTrigger;
    }

    bool operator >(const EnemyEntry &other)const{
        if(spawnTrigger == other.spawnTrigger){
            if(spawnX == other.spawnX){
                return spawnY < other.spawnY;
            }
            return spawnX > other.spawnX;
        }
        return spawnTrigger > other.spawnTrigger;
    }
    bool operator ==(const EnemyEntry &other){
        if(spawnTrigger == other.spawnTrigger){
            if(spawnX == other.spawnX){
                return spawnY == other.spawnY;
            }
        }
        return false;
    }
};

class EntityMap
{
public:
    EntityMap(GameState *game, QSharedPointer<TileMap> &map, QString ref);

    void update(double delta);

    float getX() const;
    float getY() const;
    GameState *getGame();
    int getMapHeight() const { return map->getHeight(); }
    int getMapWidth() const { return map->getWidth(); }


private:
    GameState *game;
    QSharedPointer<TileMap> map;
    float x;
    float y;
//    QMultiMap<int, QSharedPointer<EnemyEntry> > enemies;
    Tree<EnemyEntry> enemies;
    QJsonObject json;

    QJsonObject parseJSON(QString ref);
    void loadData(QString ref);
    e_ptr spawn(const EnemyEntry &entry);


};


#endif // ENTITYMAP_H
