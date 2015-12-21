#ifndef QMYAPP_H
#define QMYAPP_H
#include <QApplication>
#include <QtCore>

class QMyApp:public QApplication
{
public:
    QMyApp(int argc, char *argv[]);

    // QCoreApplication interface
public:
    bool notify(QObject *receiver, QEvent *event);
};

#endif // QMYAPP_H
