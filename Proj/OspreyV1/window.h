#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include "gamewidget.h"

class Window: public QWidget
{


public:
    Window();
    GameWidget *gw;

protected slots:

    void closeEvent(QCloseEvent *e);




};

#endif // WINDOW_H
