
#include "enemyentity.h"
#include "gamewidget.h"
#include "playerentity.h"
#include "timer.h"

#include <QLayout>
#include <QPainter>
#include <QThread>
#include <QDebug>
#include <QPaintEvent>
#include <QtCore>
#include <QTime>
#include <QtGlobal>


GameWidget::GameWidget(QWidget *parent):
    QWidget(parent),
    gameRunning(true), FPS(60), TARGETTIME(1000/FPS), pressCount(1),
    waitingForKeyPressed(true),message("")
{

    qsrand((uint)QTime::currentTime().msec());

    setFixedSize(WIDTH, HEIGHT);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    initEntities();

    Timer::startTimer();

    spawn = enemyTrigger = false;
}

void GameWidget::initEntities(){

    ship = QSharedPointer<PlayerEntity>(new PlayerEntity(this, WIDTH/2, HEIGHT-100) );

    entities << ship;
}

void GameWidget::spawnEnemy()
{
    int xPop = rand(static_cast<int>(WIDTH*.05f),static_cast<int>(WIDTH*.95f));
    e_ptr enemyShip (new EnemyEntity(
                         this, xPop, -80, qrand()%2 == 0 ? WHITE : BLACK));
    enemyShip->setVerticalMovement(rand(150,225));
    entities.append(enemyShip);

    spawn = false;
}


//void GameWidget::removeEntity(Entity * entity)
//{

//    e_ptr e(entity);
//    int idx = entities.indexOf(e);
//    removeList.append(entities.at(idx));

//}

QList<e_ptr> &GameWidget::getEntities(){
    return entities;
}

int GameWidget::rand(int low, int high)
{
    return qrand() % ((high +1) -low) + low;
}

void GameWidget::notifyDeath(){
    message = "You have Died!";
    ship->setHorizontalMovement(0);
    ship->setVerticalMovement(0);
    waitingForKeyPressed = true;
}

void GameWidget::trigger()
{

}

void GameWidget::startGame(){
    entities.clear();
    initEntities();
}

void GameWidget::gameLoop()
{
    double lastLoopTime;
    lastLoopTime = Timer::getTime();

    double delta = 0;

    double totalTime = 0;
    int frameCount = 0;
    int maxFrameCount = FPS;

    QList<e_ptr>::iterator it;

    //main game loop
    while(gameRunning){
        delta = Timer::getTime() - lastLoopTime;
        lastLoopTime = Timer::getTime();
        qApp->processEvents();

        if(!waitingForKeyPressed){


            if(spawn){
                spawnEnemy();
            }

            //move and do logic for all active entities
            foreach (e_ptr e, entities) {
               e->doLogic();
               e->move(delta);
            }

//            for(int i = 0; i < entities.size(); i++){
//                entities.at(i)->doLogic();
//                entities.at(i)->move(delta);
//            }


            //brute force collision detection
            for (int i = 0; i < entities.size(); i++){
                for (int j = i+1; j< entities.size(); j++){
                    e_ptr e1 = entities.at(i);
                    e_ptr e2 = entities.at(j);

                    if(e1->collidesWith(e2)){
                        e1->collidedWith(e2);
                        e2->collidedWith(e1);
                    }
                }

            }


            //all active enemies fire at ship (debugging)
            if(enemyTrigger){
                int lMax = entities.size();

                for(int i = 0; i < lMax; i++){
                    if(entities.at(i)->getType() == ENEMY){
                        qSharedPointerCast<EnemyEntity>(entities.at(i))
                                ->shoot(300, ship,0);
                    }
                }

            }


            //remove entities marked for removal
            it = entities.begin();
            while (it != entities.end()) {
                if((*it)->getRemoveThis()){
                    it = entities.erase(it);
                }else{
                    it++;
                }
            }


        }

        update();
//        ms sleepTime = TARGETTIME - delta/1000;
//        QThread::msleep(sleepTime);
        Timer::sync(FPS);

        totalTime += Timer::getTime() - lastLoopTime;
        frameCount++;
        if(frameCount ==maxFrameCount){
            averageFPS=1/(totalTime/static_cast<float>(frameCount));
//            qDebug()<<"Average FPS: "<<averageFPS;
            frameCount = 0;
            totalTime = 0;
        }
    }
}

void GameWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(e->rect(),QBrush(QColor(45, 10, 97)));

    if(!waitingForKeyPressed){
        for(int i = 0; i < entities.size(); i++){
            e_ptr entity = entities.at(i);

            entity->draw(&painter);
//            qDebug() << "Entity Size: " <<entities.size();
        }

        painter.setPen(Qt::red);
        painter.drawText(15,15, "Average FPS: " + QString::number(averageFPS));
        painter.drawText(15,30, "Entities: " + QString::number(entities.size()));
        painter.drawText(15,45, "Player Energy: " + QString::number(ship->getEnergy()));


//        painter.setPen(Qt::white);
//        for (int i = 0; i < 8; ++i) {
//            int n = 3*ship->getEnergy()-30*i;
//            painter.fillRect(10 + 35*i,HEIGHT-25,qMin(n,30)-qMin(n,0),10, ship->getPolarity()==WHITE?  Qt::cyan :  Qt::red );
//            painter.drawRect(10 + 35*i,HEIGHT-25,30,10);
//        }

    }else{
        painter.setPen(Qt::white);
        painter.drawText((WIDTH - painter.fontMetrics().width(message))/2,
                         HEIGHT/2, message);

        painter.drawText((WIDTH - painter.fontMetrics()
                          .width("W, A, S, D, for controls, Space to fire"))/2,
                         static_cast<int>(HEIGHT * 0.55),
                         "W, A, S, D, for controls, Space to fire");

    }

    painter.end();
}

void GameWidget::keyPressEvent(QKeyEvent * k){
    if(k->isAutoRepeat()){
        return;
    }
    if(waitingForKeyPressed){
        QWidget::keyPressEvent(k);
        return;
    }

    switch (k->key()) {
    case Qt::Key_A:
        ship->setLeft(true);
        break;
    case Qt::Key_D:
        ship->setRight(true);
        break;
    case Qt::Key_W:
        ship->setUp( true);
        break;
    case Qt::Key_S:
        ship->setDown(true);
        break;
    case Qt::Key_Space:
        ship->setTrigger(true);
        break;
    case Qt::Key_Comma:
        ship->setPolarize(true);
        break;
    case Qt::Key_Enter:
        spawn = true;
        break;
    case Qt::Key_0:
        enemyTrigger = true;
        break;
    default:
        QWidget::keyPressEvent(k);
        break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *k){
    if(k->isAutoRepeat()){
        return;
    }
    if(!waitingForKeyPressed){
        switch (k->key()) {
        case Qt::Key_A:
            ship->setLeft(false);
            break;
        case Qt::Key_D:
            ship->setRight(false);
            break;
        case Qt::Key_W:
            ship->setUp(false);
            break;
        case Qt::Key_S:
            ship->setDown(false);
            break;
        case Qt::Key_Space:
            ship->setTrigger(false);
            break;
        case Qt::Key_Comma:
            ship->setPolarize(false);
            break;
        case Qt::Key_Enter:
            spawn = false;
            break;
        case Qt::Key_0:
            enemyTrigger = false;
            break;
        default:
            QWidget::keyReleaseEvent(k);
            break;
        }
    }else{
        if(pressCount == 1){
            waitingForKeyPressed = false;
            startGame();
            pressCount = 0;
        }else{
            pressCount ++;
        }
    }
}

