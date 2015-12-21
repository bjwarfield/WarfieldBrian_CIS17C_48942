#include "level1state.h"
#include "Util/timer.h"
#include "Entity/entity.h"
#include "Entity/playerentity.h"
#include "Entity/enemyentity.h"
#include "Entity/enemypestilence.h"
#include "Entity/enemyscarab.h"

#include <Entity/enemycruiser.h>
#include <Entity/enemyprobe.h>
#include <Entity/enemyscout.h>



/**
 * @brief Constructor
 * @param gsm parent GameStateManager
 */
Level1State::Level1State(GameStateManager *gsm):
    GameState(gsm)
{
    init();
}

/**
 * @brief Level1State Destructor
 */
Level1State::~Level1State()
{

}


/**
 * @brief Build TileMap, clear entity lists, reset key statuses, create player,
 * init event parameters.
 */
void Level1State::init()
{
    //initialize Tilemap
    tileMap = QSharedPointer<TileMap>(new TileMap(":/maps/level_1.JSON"));
    //Set beginning positoin to bottom of map
    tileMap->setPosition((width() - tileMap->getWidth())/2 ,
                         -tileMap->getHeight() + height());


    //create entity map
    entityMap = QSharedPointer<EntityMap>(
                new EntityMap(this, tileMap,":/maps/level_1.enemies" ));

    //clear out existing entitylists
    getPlayerEntities().clear();
    getEnemyEntities().clear();
    getPlayers().clear();
    getEffects().clear();

    //reset input states
    up = down = left = right = trigger = polarize = burst = false;

    //add player
    e_ptr ship = e_ptr(new PlayerEntity(this, width()/2, height()-100));
    getPlayers().append(ship);
    respawnTimer = 0;
    playerIsAlive = true;
    //event tracker
    events.resize(32);
    for(bool &e: events) {
        e = true;
    }

    //timer params
    timeStart = Timer::getTime();
    playerControl = true;
    controlTimer = Timer::getTime() + 5;
    levelEnd = false;

    //debug params
    spawn = enemyTrigger = false;

}

/**
 * @brief update coordinats gameMap and all entities. Perform associated logic,
 * check entity collisions and remove entitied marked for removal.
 *
 * @param delta timeslice interpolation factor. Time since last update
 */
void Level1State::gameUpdate(double delta)
{
    double clockTimer = Timer::getTime() - timeStart;

    //entityMap.update(delta)

    //parallaxer
    float xShift = 0;
    playerEnergy = 0;
    playerPolarity = WHITE;
    if(getPlayers().size() > 0){
        int num = 0;

        for (int i = 0; i < getPlayers().size(); ++i) {
            PlayerEntity *pe = &*(getPlayers().at(i).staticCast<PlayerEntity>());
            num+= pe->getHorizontalMovement();
            playerEnergy = pe->getEnergy();
            playerPolarity = pe->getPolarity();

        }
        xShift = num / (float) getPlayers().size();
    }
    tileMap->setHorizontalMovement(xShift * -0.6f);
    //move map
    tileMap->move(delta);
    moveEntities(delta);
    entityMap->update(delta);


    //respawn player when dead
    if(!playerIsAlive){
        if(Timer::getTime() > respawnTimer){
            e_ptr ship(new PlayerEntity(this, width() / 2, height() + 100));
            ship->setVerticalMovement(-100);
            qSharedPointerCast<PlayerEntity>(ship)->setFlinching(6);
            getPlayers().append(ship);

            playerIsAlive = true;
        }
    }

    //restore player control and assign temporary invincibility
    if(!playerControl && Timer::getTime() > controlTimer && !levelEnd){
        playerControl = true;
        for(e_ptr player: getPlayers()){
            qSharedPointerCast<PlayerEntity>(player)->setFlinching(3);
        }
    }


//    if(spawn)spawnEnemy();//debug
//    //all active enemies fire at ship (debugging)
//    if(enemyTrigger){
//        int lMax = getEnemyEntities().size();

//        for(int i = 0; i < lMax; i++){

//            if(getEnemyEntities().at(i)->getType() == ENEMY
//                    && getPlayers().size() >0 ){
//                qSharedPointerCast<EnemyEntity>(getEnemyEntities().at(i))
//                        ->shoot(300, getPlayers().at(0) ,rand(-20,20)/5.0f);
//            }
//        }

//    }

    //TODO: levelScripts
    (void) clockTimer;
    if( events[0]){
        events[0]= false;
        tileMap->setVerticalMovement(80);
    }

    //check entity collisions
    checkCollisions();

}


/**
 * @brief Cycle through all active entities
 * @param painter
 */
void Level1State::gameDraw(QPainter *painter)
{
    //draw map
    tileMap->draw(painter);

    //draw map entities
    //entityMap.draw(painter);

    //for debuggin
    //remove after entityMap implemtation
    for(e_ptr enemy: getEnemyEntities()){
        enemy->draw(painter);
    }

    //draw player bullets
    for(e_ptr shot: getPlayerEntities()){
        shot->draw(painter);
    }


    //draw player
    for(e_ptr player: getPlayers()){
        player->draw(painter);
    }

    //draw effects
    for(e_ptr effect: getEffects()){
        effect->draw(painter);
    }

    //draw Energy bar
    painter->save();
    painter->setPen(Qt::white);
    for(int i = 0; i < 8; i++){
        int n = 3 * playerEnergy - 30 * i;
        painter->fillRect(10, (height() - 5 - 35*i)-(qMin(n,30)-qMin(n,0)) , 10, qMin(n,30)-qMin(n,0),
                          playerPolarity == WHITE ? Qt::cyan : Qt::red);
        if(qMin(n,30)-qMin(n,0) == 30 && qRound(Timer::getTime()*16)%2==0 ){
            painter->fillRect(10, (height() - 5 - 35*i)-(qMin(n,30)-qMin(n,0)) , 10, qMin(n,30)-qMin(n,0),
                              playerPolarity == WHITE ? QColor(255,255,255,192) : QColor(0,0,0,192));
        }
        painter->drawRect(10, height() - 35 - 35*i, 10, 30);

    }

    painter->restore();


    //deebug info
    painter->setPen(Qt::red);
    painter->drawText(15, 15, "Average FPS: " + QString::number(gsm->getFPS()));
    painter->drawText(15, 30, "Players: " + QString::number(getPlayers().size()));
    painter->drawText(15, 45, "PlayerEntities: " + QString::number(getPlayerEntities().size()));
    painter->drawText(15, 60, "Player Energy: " + QString::number(playerEnergy));
    painter->drawText(15, 75, "EnemyEntities: " + QString::number(getEnemyEntities().size()));
    painter->drawText(15, 90, "MapPos: " + QString::number(tileMap->getX()) +
                      " ," +QString::number(tileMap->getY() + tileMap->getHeight()));


}

/**
 * @brief notify of keyPressed event
 * @param k Qt::Key value
 */
void Level1State::keyPressed(int k)
{
    if(playerControl){
        switch(k){
        case Qt::Key_Left:
            left = true;
            break;
        case Qt::Key_Down:
            down = true;
            break;
        case Qt::Key_Right:
            right = true;
            break;
        case Qt::Key_Up:
            up = true;
            break;
        case Qt::Key_Z:
            trigger = true;
            break;
        case Qt::Key_X:
            polarize = true;
            break;
        case Qt::Key_C:
            burst = true;
            break;
        case Qt::Key_Shift:
            spawn = true;
            break;
        case Qt::Key_Control:
            enemyTrigger = true;
            break;
        }
    }
}

/**
 * @brief notify of keyReleased event
 * @param k Qt::Key value
 */
void Level1State::keyReleased(int k)
{
    switch(k){
    case Qt::Key_Left:
        left = false;
        break;
    case Qt::Key_Down:
        down = false;
        break;
    case Qt::Key_Right:
        right = false;
        break;
    case Qt::Key_Up:
        up = false;
        break;
    case Qt::Key_Z:
        trigger = false;
        break;
    case Qt::Key_X:
        polarize = false;
        break;
    case Qt::Key_C:
        burst = false;
        break;
    case Qt::Key_Shift:
        spawn = false;
        break;
    case Qt::Key_Control:
        enemyTrigger = false;
        break;
    }
}

/**
 * @brief cycle through all active game entities, updating coordinates and
 * applying individual logic functions. Remove entites that move out of bounds
 * @param delta timeslice movement interpolation factor. Time in seconds since
 * last entity movement
 */
void Level1State::moveEntities(double delta)
{
    float xShift = tileMap->getHorizontalMovement();
    float yShift = tileMap->getVerticalMovement();

    //cycle round asking eash EnemyEntity ro move itself
    for(e_ptr enemyEntity: getEnemyEntities() ){
        enemyEntity->move(delta, xShift);
        enemyEntity->doLogic(delta);//do associated logic
        enemyEntity->boundCheck();
    }//end enemyEntity

    //cycle through each player entity asking it to move itsef
    for(e_ptr playerEntity: getPlayerEntities()){
        if(playerEntity->getType() == SHIP){
            playerEntity->move(delta, xShift, yShift);
        }else{
            playerEntity->move(delta, xShift);
        }

        playerEntity->doLogic(delta);
        playerEntity->boundCheck();
    }//end playerEntity

    //move effects
    for(e_ptr effect:getEffects()){
        effect->move(delta, xShift);
        effect->doLogic(delta);

    }

    //move player
    for(e_ptr player: getPlayers()){
        player->move(delta);
        player->doLogic(delta);
    }
}

/**
 * @brief Brute force collision detection. Compare every playerEntity against
 * every enemyEntity.  If any of them collide, notify both entities that a
 * collision has occured.
 */
void Level1State::checkCollisions()
{
    //enemy -> playerBullets
    for(e_ptr pe: getPlayerEntities()){
        for(e_ptr ee: getEnemyEntities()){
            if(pe->collidesWith(ee)){
                pe->collidedWith(ee);
                ee->collidedWith(pe);
            }
        }
    }

    //player -> enemyEntities
    for(e_ptr pe: getPlayers()){
        for(e_ptr ee: getEnemyEntities()){
            if(ee->collidesWith(pe)){
                pe->collidedWith(ee);
                ee->collidedWith(pe);
            }
        }
    }

    // remove any entity that has been marked for clear up
    removeDeadEntities(getEnemyEntities());
    removeDeadEntities(getPlayerEntities());
    removeDeadEntities(getPlayers());
    removeDeadEntities(getEffects());

}

/**
 * @brief Level1State::spawnEnemy
 * for testing different enemy classes
 */
void Level1State::spawnEnemy()
{
    int xPop = rand(static_cast<int>(width()*.05f),
                        static_cast<int>(width()*0.95f));

    e_ptr enemyShip(new EnemyScarab(this, xPop, 700, rand(0,1)== 0 ? WHITE: BLACK));
//    enemyShip->setVerticalMovement(rand(100,250));
    getEnemyEntities().append(enemyShip);
    spawn = false;
}

