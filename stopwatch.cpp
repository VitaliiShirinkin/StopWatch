#include "stopwatch.h"
#include <QTimer>

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{

    time.setHMS(0, 0, 0, 0);
    stopTime.setHMS(0, 0, 0, 0);
    circleTime = 0;
    count = 1;

    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &Stopwatch::updateTime);

}

Stopwatch::~Stopwatch()
{
    delete timer;
}

void Stopwatch::updateTime()
{
    time = time.addMSecs(100);
    strCurrentTime = time.toString("mm:ss.z");
    emit sig_updateTime(strCurrentTime);
}

void Stopwatch::startTimer()
{
    timer->start();
    updateTime();
}

void Stopwatch::stopTimer()
{
    timer->stop();
}

void Stopwatch::rcv_circleTime()
{
    circleTime = stopTime.secsTo(time);
    strCircleTime = "Круг " + QString::number(count) + " , время: " + QString::number(circleTime) + " сек";
    stopTime = time;
    count++;
}

void Stopwatch::rcv_clearTime()
{
    count = 1;
    time.setHMS(0, 0, 0, 0);
    stopTime.setHMS(0, 0, 0, 0);
}
