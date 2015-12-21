#include "Main/window.h"
#include <QtCore>
#include <QGridLayout>
#include <QtGui>
#include <QMenuBar>

Window::Window()
{
    setWindowTitle("Osprey Assault V2");

    QGridLayout *layout =  new QGridLayout;

    QMenuBar *menubar  = new QMenuBar(this);
    gw = new GameWidget(this);
//    connect(gw,SIGNAL(gameUpdated()),gw,SLOT(update()));

    layout->addWidget(menubar,0,0);
    layout->addWidget(gw,0,1);
    setLayout(layout);
    show();

    gw->startGame();
}

void Window::closeEvent(QCloseEvent * e)
{
    gw->endGame();
    e->accept();
    //this is a sloppy way to close the app before qApp.exec() is called
    QTimer::singleShot(250,qApp,SLOT(quit()));
}
