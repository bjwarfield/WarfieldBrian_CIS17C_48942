#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include "Main/gamewidget.h"
class GameWidget;

class Window: public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    GameWidget *gw;


protected slots:
    void closeEvent(QCloseEvent *e);
};

#endif // WINDOW_H
