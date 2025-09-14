#include "daochewindow.h"
#include "ui_daochewindow.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <sys/ioctl.h>
#define CMD_TRIG  100
daocheWindow::daocheWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::daocheWindow)
{
    ui->setupUi(this);
    m_worker = new DistanceWorker(this);
    connect(m_worker, &DistanceWorker::distanceUpdated, this, &daocheWindow::updateDistance);
    connect(m_worker, &DistanceWorker::errorOccurred, this, &daocheWindow::handleError);
    m_worker->start();
}

daocheWindow::~daocheWindow()
{
    m_worker->stop();
    m_worker->wait();
    delete ui;
    delete ui;
}
void daocheWindow::updateDistance(int value)
{
    ui->daoche_label->setText(QString::number(value));
}

void daocheWindow::handleError(const QString &message)
{
    ui->daoche_label->setText(message);
}
void daocheWindow::on_pushButton_clicked()
{
    this->parentWidget()->show();

    this->hide();
}
