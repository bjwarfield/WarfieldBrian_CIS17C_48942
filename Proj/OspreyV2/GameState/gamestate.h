#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameState/gamestatemanager.h"
#include "Entity/entity.h"

class GameStateManager;


class GameState
{
public:
    GameState(GameStateManager *gsm);
    virtual void init() = 0;
    virtual void gameUpdate(double delta) = 0;
    virtual void gameDraw(QPainter *painter) = 0;
    virtual void keyPressed(int k) = 0;
    virtual void keyReleased(int k) = 0;


    DList<e_ptr> &getPlayerEntities();
    DList<e_ptr> &getEnemyEntities();
    DList<e_ptr> &getPlayers();
    DList<e_ptr> &getEffects();

    void notifyPlayerDeath();

    bool getPlayerControl() const;

    virtual ~GameState();

   int height() const;
   int width() const;
   QHash<QString, bool> getKeys() const;
   int rand(int min, int max);
   void removeDeadEntities(DList<e_ptr> &list);

protected:
    GameStateManager *gsm;
    bool playerIsAlive;
    double respawnTimer;
    bool playerControl;
    double controlTimer;
    bool up, down, left, right, trigger, polarize, burst;

    //entity containers
    DList<e_ptr> playerEntities;
    DList<e_ptr> enemyEntities;
    DList<e_ptr> players;
    DList<e_ptr> effects;

};

#endif // GAMESTATE_H
