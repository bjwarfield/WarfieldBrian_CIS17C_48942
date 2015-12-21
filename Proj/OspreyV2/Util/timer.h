#ifndef TIMER_H
#define TIMER_H
#include <QElapsedTimer>
#include <QThread>
#include <cmath>

class Timer
{
private:
    Timer(){}
    Timer(Timer const&) = delete;
    void operator=(Timer const&) = delete;

    static QElapsedTimer timer;
    static double variableYieldTime;
    static double lastTime;

public:
    static void startTimer();
    static double getTime();
    static void sync(int fps);
};

#endif // TIMER_H
