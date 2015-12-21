#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include "entity.h"
#include "playerentity.h"

#include <QMainWindow>
#include <QWidget>
#include <QTimer>

class PlayerEntity;


class GameWidget: public QWidget
{
    Q_OBJECT

private:

    enum {WIDTH = 800, HEIGHT = 600};



    bool gameRunning;
    const int FPS;
    const long TARGETTIME;
    float averageFPS;

    QSharedPointer<PlayerEntity> ship;



    QList<e_ptr> entities;

    int pressCount;

    bool spawn;
    bool enemyTrigger;

    bool waitingForKeyPressed;

    QString message;

    void initEntities();

    void spawnEnemy();
public:
    GameWidget(QWidget *parent = 0);

    void endGame(){gameRunning = false;}

    void gameLoop();

//    void removeEntity(Entity *entity);
    void notifyDeath();
    void startGame();
    void trigger();
    QList<e_ptr> &getEntities();

    int rand(int low, int high);


protected:
    void paintEvent(QPaintEvent * e);


    void keyPressEvent(QKeyEvent *k);
    void keyReleaseEvent(QKeyEvent *k);
};

#endif // GAMEWIDGET_H
