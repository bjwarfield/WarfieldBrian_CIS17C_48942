//#include <QApplication>
//#include <QtCore>
#include "Main/qmyapp.h"
#include "Main/window.h"



int main(int argc, char *argv[])
{
    QMyApp a(argc, argv);

    Window window;

    return a.exec();
}
