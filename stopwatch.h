#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDebug>

class Stopwatch : public QObject
{
    Q_OBJECT

public:

    QString strCurrentTime;
    QString strCircleTime;

    explicit Stopwatch(QObject *parent = nullptr);

    ~Stopwatch();

    void updateTime();
    void startTimer();
    void stopTimer();

public slots:

    void rcv_circleTime();
    void rcv_clearTime();

signals:

    void sig_updateTime(QString &strCurrentTime);

private:

    QTimer *timer;
    QTime time;
    QTime stopTime;
    int circleTime;
    int count;

};

#endif // STOPWATCH_H
