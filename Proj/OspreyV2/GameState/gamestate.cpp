#include "gamestate.h"
#include "Util/timer.h"
#include "Entity/bulletshield.h"

GameState::GameState(GameStateManager *gsm)
{
    this->gsm = gsm;
}

DList<e_ptr> &GameState::getPlayerEntities()
{
    return playerEntities;
}

DList<e_ptr> &GameState::getEnemyEntities()
{
    return enemyEntities;
}

DList<e_ptr> &GameState::getPlayers()
{
    return players;
}

DList<e_ptr> &GameState::getEffects()
{
    return effects;
}

void GameState::notifyPlayerDeath()
{
    playerControl = false;
    playerIsAlive = false;
    respawnTimer = Timer::getTime()+2;
    controlTimer = Timer::getTime()+4;
    e_ptr shield(new BulletShield(this, 7));
    playerEntities.append(shield);
}
bool GameState::getPlayerControl() const
{
    return playerControl;
}

GameState::~GameState(){

}

int GameState::height() const
{
    return gsm->getWidget()->height();
}

int GameState::width() const
{
    return gsm->getWidget()->width();
}

QHash<QString, bool> GameState::getKeys() const
{
    QHash<QString, bool> keys;
    keys["up"]=up;
    keys["down"] = down;
    keys["left"] = left;
    keys["right"] = right;
    keys["trigger"] = trigger;
    keys["polarize"] = polarize;
    keys["burst"] = burst;

    return keys;
}

int GameState::rand(int min, int max)
{
    return gsm->rand(min, max);
}

/**
 * @brief Remove entities marked for deletion
 * @param list
 */
void GameState::removeDeadEntities(DList<e_ptr> &list)
{
    DList<e_ptr>::iterator it = list.begin();
    while(it != list.end()){
        if((*it)->getRemoveThis()){
            it = list.erase(it);
        }else{
            it++;
        }
    }
}








