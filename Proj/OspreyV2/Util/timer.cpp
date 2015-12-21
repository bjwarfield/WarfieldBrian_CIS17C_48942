#include "timer.h"

QElapsedTimer Timer::timer;
double Timer::lastTime;
double Timer::variableYieldTime;

void Timer::startTimer(){
    timer.start();
}

double Timer::getTime(){
    if (!timer.isValid())startTimer();
    return timer.nsecsElapsed() * 1.0e-9;
}

void Timer::sync(int fps){
    if(fps<0)return;
    if (!timer.isValid())startTimer();

    //time in seconcs to sleep this frame
    double sleepTime = 1.0/fps;

    // yieldTime + remainder micro & nano seconds if smaller than sleepTime
    double yieldTime = qMin(sleepTime,
                            variableYieldTime + fmod(sleepTime , 0.001));

    //time the sync goes over by
    double overSleep = 0;

    //calculate and sleep the desired sleepTime
    while(true){
        //check time elapsed
        double t = getTime() - lastTime;

        //if ellapsed is less than wait interval
        if(t < sleepTime - yieldTime){
            QThread::msleep(1);//sleep for 1 msec
        } else if(t < sleepTime){
            QThread::yieldCurrentThread();//yield remaining time
        } else {
            overSleep = t - sleepTime;
            break;//exit loop
        }
    }

    //set end of loop time
    lastTime = getTime() - qMin(overSleep, sleepTime);

    //auto tune the time sync should yield
    if(overSleep > variableYieldTime){
        //increase by 100 microsecs (1/10ms)
        variableYieldTime = qMin(variableYieldTime + 0.0001, sleepTime);
    }else if(overSleep < variableYieldTime - 0.0001){
        //decrease by 100 microsecs
        variableYieldTime = qMax(variableYieldTime - 0.0001, 0.0);
    }

}
