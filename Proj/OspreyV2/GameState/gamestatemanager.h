#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <QPainter>
#include <QSharedPointer>
#include "Container/DoubleLinkedList.h"
#include "Main/gamewidget.h"
#include "GameState/gamestate.h"


class GameState;
class GameWidget;
typedef QSharedPointer<GameState> gs_ptr;

class GameStateManager
{
public:
    enum state {MENUSTATE, LEVEL1STATE};

private:
    state currentState;
    DList<gs_ptr> gameStates;

public:
    GameStateManager(GameWidget *parent);

    GameWidget *gw;
    void setState(state s);
    DList<gs_ptr> &getGameStates();
    void gameUpdate(double delta);
    void gameDraw(QPainter *painter);
    void keyPressed(int k);
    void keyReleased(int k);
    int rand(int min, int max);


    GameWidget *getWidget() const;
    float getFPS()const;
};

#endif // GAMESTATEMANAGER_H
