#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "stopwatch.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    stopwatch = new Stopwatch(this);
    ui->setupUi(this);

    ui->pb_start_stop->setCheckable(true);
    ui->pb_start_stop->setText("СТАРТ");
    ui->pb_circle->setText("КРУГ");
    ui->pb_clear->setText("ОЧИСТИТЬ");
    ui->pb_circle->setEnabled(false);

    connect(stopwatch, &Stopwatch::sig_updateTime, this, &MainWindow::rcv_updateTime);
    connect(this, &MainWindow::sig_circleTime, stopwatch, &Stopwatch::rcv_circleTime);
    connect(this, &MainWindow::sig_clearTime, stopwatch, &Stopwatch::rcv_clearTime);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rcv_updateTime(QString text)
{
    ui->lb_time->setText(text);
}

void MainWindow::on_pb_start_stop_clicked()
{
    if(ui->pb_start_stop->isChecked()){

        stopwatch->startTimer();
        ui->pb_start_stop->setText("СТОП");
        ui->pb_circle->setEnabled(true);
    }else
    {
        stopwatch->stopTimer();
        ui->pb_start_stop->setText("СТАРТ");
        ui->pb_circle->setEnabled(false);
    }
}

void MainWindow::on_pb_circle_clicked()
{
    emit sig_circleTime();
    QString text = stopwatch->strCircleTime;
    ui->tB_circles->append(text);
}

void MainWindow::on_pb_clear_clicked()
{
    ui->lb_time->setText("00:00.0");
    emit sig_clearTime();
}
