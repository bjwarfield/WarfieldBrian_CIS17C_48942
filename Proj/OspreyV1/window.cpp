#include "window.h"
#include <QtCore>
#include <QGridLayout>
#include <QtGui>

Window::Window()
{
    setWindowTitle("Osprey Assault");



    gw = new GameWidget(this);

    QGridLayout *layout =  new QGridLayout;

    layout->addWidget(gw,0,0);
    setLayout(layout);
    show();

}



void Window::closeEvent(QCloseEvent * e)
{
    gw->endGame();
    e->accept();
    //this is a sloppy way to close the app before qApp.exec() is called
    QTimer::singleShot(250,qApp,SLOT(quit()));
}





