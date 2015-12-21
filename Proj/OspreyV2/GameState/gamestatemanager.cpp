#include "GameState/gamestatemanager.h"
#include "GameState/menustate.h"

#include "level1state.h"

GameStateManager::GameStateManager(GameWidget *parent):
    gw(parent)
{
    gameStates.append(gs_ptr(new MenuState(this)));
    gameStates.append(gs_ptr(new Level1State(this)));
    currentState = MENUSTATE;

}

void GameStateManager::setState(GameStateManager::state s)
{
    gameStates.get(s)->init();
    currentState = s;
}

DList<gs_ptr> &GameStateManager::getGameStates()
{
    return gameStates;
}

void GameStateManager::gameUpdate(double delta)
{
    gameStates.get(currentState)->gameUpdate(delta);
}

void GameStateManager::gameDraw(QPainter *painter)
{
    gameStates.get(currentState)->gameDraw(painter);
}

void GameStateManager::keyPressed(int k)
{
    gameStates.get(currentState)->keyPressed(k);
}

void GameStateManager::keyReleased(int k)
{
    gameStates.get(currentState)->keyReleased(k);
}

int GameStateManager::rand(int min, int max)
{
    return gw->rand(min, max);
}


GameWidget *GameStateManager::getWidget() const
{
    return gw;
}

float GameStateManager::getFPS() const
{
    return gw->getFPS();
}
