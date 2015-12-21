#include "TileMap/entitymap.h"

#include <QFile>
#include <QtCore>

#include <Entity/enemycruiser.h>
#include <Entity/enemypestilence.h>
#include <Entity/enemyprobe.h>
#include <Entity/enemyscarab.h>
#include <Entity/enemyscout.h>

EntityMap::EntityMap(GameState *game, QSharedPointer<TileMap> &map, QString ref):
    game(game)
{
    this->map = map;
    loadData(ref);
}

void EntityMap::update(double delta)
{
    Q_UNUSED( delta);
    x = map->getX();
    y = map->getY();

    //if enemyList isnt empty, scan min node for spawnTrigger
     while(!enemies.isEmpty() && enemies.min().spawnTrigger < y + map->getHeight()){

        game->getEnemyEntities().append(spawn(enemies.min()));
        enemies.remove(enemies.min());
        //game->getEnemyEntities().append( );//add constructed class to game
    }



}

QJsonObject EntityMap::parseJSON(QString ref)
{
    QFile jsonFile(ref);
    if(!jsonFile.open(QFile::ReadOnly | QFile::Text)){
        qCritical() << "Unable to read File: "<< ref;
        qApp->exit(EXIT_FAILURE);
    }
    QByteArray data = jsonFile.readAll();
    QJsonDocument jsonData(QJsonDocument::fromJson(data));

    return jsonData.object();
}


void EntityMap::loadData(QString ref)
{
    json = parseJSON(ref);
    QJsonArray enemyList = json["enemyList"].toArray();
    if(enemyList.size() > 0){
        for(int i = 0; i < enemyList.size(); i++){
            QJsonObject je = enemyList[i].toObject();

            EnemyEntry entry;
            entry.spawnTrigger = je["spawnTrigger"].toInt();
            entry.enemyClass = je["enemyClassName"].toString();
            entry.polarity = je["polarity"].toInt() % 2 == 0 ? WHITE : BLACK;
            entry.spawnX = je["spawnX"].toInt();
            entry.spawnY = je["spawnY"].toInt();

            QJsonArray pathList = je["paths"].toArray();
            for (int j = 0; j < pathList.size(); ++j) {
                QJsonArray path = pathList.at(j).toArray();
                entry.paths.append(Point(path.at(0).toInt(),path.at(1).toInt()));
            }

            entry.spawnRef = je["spawnRef"].toString();

            enemies.add(entry);

        }
    }
}

e_ptr EntityMap::spawn(const EnemyEntry &entry)
{
    int sx = entry.spawnX;
    int sy = entry.spawnY;
    polarType pol = entry.polarity;
    QString ref = entry.spawnRef;
    Path *p = new Path;

    for(Point pt: entry.paths){
        p->addNode(pt);
    }
    if(entry.enemyClass.compare("EnemyScout")==0){
        return e_ptr(new EnemyScout(game, sx, sy, pol, p ,ref));
    }else if(entry.enemyClass.compare("EnemyScarab")==0){
        return e_ptr(new EnemyScarab(game, sx, sy, pol, p ,ref));
    }else if(entry.enemyClass.compare("EnemyPestilence")==0){
        return e_ptr(new EnemyPestilence(game, sx, sy, pol, p ,ref));
    }else if(entry.enemyClass.compare("EnemyCruiser")==0){
        return e_ptr(new EnemyCruiser(game, sx, sy, pol, p ,ref));
    }else{
        return e_ptr(new EnemyProbe(game, sx, sy, pol, p ,ref));
    }
}



float EntityMap::getX() const
{
    return x;
}

float EntityMap::getY() const
{
    return y;
}

GameState *EntityMap::getGame()
{
    return game;
}





