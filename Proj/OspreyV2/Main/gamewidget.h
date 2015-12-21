#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "Main/window.h"
#include "GameState/gamestatemanager.h"

#include <QMainWindow>
#include <QWidget>
#include <QTimer>



class Window;
class GameStateManager;

class GameWidget: public QWidget
{
    Q_OBJECT

private:
    Window *window;

    QSharedPointer<GameStateManager> gsm;

    bool gameRunning;
    const int FPS;
    float averageFPS;

    bool paused;

public:
    enum {WIDTH = 800, HEIGHT = 600};
    GameWidget(Window *parent);

    void setTitle(QString title);
    void startGame();
    void endGame(){gameRunning = false;}

    void gameLoop();

    int rand(int min, int max);
    float getFPS() const;

protected:
    void paintEvent(QPaintEvent * e);
    void keyPressEvent(QKeyEvent *k);
    void keyReleaseEvent(QKeyEvent *k);


protected:
    void focusOutEvent(QFocusEvent *e);

};

#endif // GAMEWIDGET_H
