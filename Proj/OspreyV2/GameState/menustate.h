#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState/gamestate.h"
#include "TileMap/background.h"
#include "Util/font.h"
#include "LevelEditor/leveleditor.h"
#include "Users/usercontrolpanel.h"


class MenuState:public GameState
{
public:
    MenuState(GameStateManager *gsm);

    // GameState interface
public:
    void init();
    void gameUpdate(double delta);
    void gameDraw(QPainter *painter);
    void keyPressed(int k);
    void keyReleased(int k);
    ~MenuState();

private:
    QSharedPointer<Background> bg;
    UserControlPanel *ucp;

    levelEditor *le;
    int currentChoice;

    Vector<QString> option;
    Sprite logo;

    Font grayFont;
    Font redFont;
    Font *selectedFont;

    void select();
};

#endif // MENUSTATE_H
