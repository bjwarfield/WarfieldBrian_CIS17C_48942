
#include "Main/gamewidget.h"
#include "Util/timer.h"

#include <QLayout>
#include <QPainter>
#include <QDebug>
#include <QPaintEvent>
#include <QtCore>
#include <QTime>
#include <QtGlobal>



/**
 * @brief Object constructor
 * @param parent
 * @param wParent
 */
GameWidget::GameWidget(Window *parent):
    QWidget(parent), gameRunning(true), FPS(60), paused(false)
{
    window = parent;

    qsrand((uint)QTime::currentTime().msec());

    setFixedSize(WIDTH, HEIGHT);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    Timer::startTimer();

    gsm = QSharedPointer<GameStateManager>(new GameStateManager(this));


}

/**
 * @brief Set Window Title
 * @param title desired window title
 */
void GameWidget::setTitle(QString title)
{
    window->setWindowTitle(title);
}

/**
 * @brief Random Number Gerator
 * @param min lowest desired number
 * @param max highest desired number
 * @return random integer between min and max (inclusive)
 */
int GameWidget::rand(int min, int max)
{
    return qrand() % ((max +1) -min) + min;
}


/**
 * @brief starts the main game loop
 */
void GameWidget::startGame(){
    gameRunning = true;
    gameLoop();
}

/**
 * @brief Main Game Loop, calls update on GameStateManager, qApp->ProcessEvents,
 * updates(repaints) widget and sleeps the thread to sync to desired framerate
 */
void GameWidget::gameLoop()
{
    double lastLoopTime;
    lastLoopTime = Timer::getTime();

    double delta = 0;

    double totalTime = 0;
    int frameCount = 0;
    int maxFrameCount = 10;

    //main game loop
    while(gameRunning){
        delta = Timer::getTime() - lastLoopTime;
        lastLoopTime = Timer::getTime();


        qApp->processEvents();

        if(!paused){
            gsm->gameUpdate(delta);
        }

        update();
//        emit gameUpdated();

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

/**
 * @brief Paint event override. Creates Qpainter object for this widget and
 *  passes it to the GameStateManager
 * @param e paint event
 */
void GameWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(e->rect(),QBrush(QColor(45, 45, 75)));

    if(!paused){
        gsm->gameDraw(&painter);

    }else{
        painter.setPen(Qt::white);
        painter.drawText((WIDTH - painter.fontMetrics().width("Game Paused"))/2,
                         HEIGHT/2, "Game Paused");

        painter.drawText((WIDTH - painter.fontMetrics()
                          .width("Press Any Key to start"))/2,
                         static_cast<int>(HEIGHT * 0.45),
                         "Press Any Key to start");

    }

    painter.end();
}

/**
 * @brief Override KeyPress event and pass params to GameStateMagager
 * @param k key event
 */
void GameWidget::keyPressEvent(QKeyEvent * k){
    if(k->isAutoRepeat()){
        return;
    }
    if(!gameRunning){
        startGame();
    }
    if(paused){
        QWidget::keyPressEvent(k);
        return;
    }else{
        gsm->keyPressed(k->key());
    }


}

/**
 * @brief Override KeyRelease event and pass params to GameStateMagager
 * @param k key event
 */
void GameWidget::keyReleaseEvent(QKeyEvent *k){
    if(k->isAutoRepeat()){
        return;
    }
    if(!paused){
        switch (k->key()) {
        case Qt::Key_Pause:
            paused = true;
            break;
        default:
            gsm->keyReleased(k->key());
        }
    }else{
            paused = false;
    }
}

/**
 * @brief GameWidget::getFPS
 * @return Average frames per second in main game loop
 */
float GameWidget::getFPS() const
{
    return averageFPS;
}

/**
 * @brief Pause game when widget focs is lost
 * @param e
 */
void GameWidget::focusOutEvent(QFocusEvent *e)
{
    paused = true;
    (void)e;
}
