#include <QApplication>
#include <QtCore>

#include "window.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window window;

    window.gw->gameLoop();

    return a.exec();
}
