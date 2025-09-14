#include "form_daoche.h"
#include "ui_form_daoche.h"

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
Form_daoche::Form_daoche(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_daoche)
{
    ui->setupUi(this);

    m_worker = new DistanceWorker(this);
    connect(m_worker, &DistanceWorker::distanceUpdated, this, &Form_daoche::updateDistance);
    connect(m_worker, &DistanceWorker::errorOccurred, this, &Form_daoche::handleError);
    m_worker->start();
}

Form_daoche::~Form_daoche()
{
    m_worker->stop();
    m_worker->wait();
    delete ui;
}

void Form_daoche::updateDistance(int value)
{
    ui->daoche_label->setText(QString::number(value));
}

void Form_daoche::handleError(const QString &message)
{
    ui->daoche_label->setText(message);
}

void Form_daoche::on_pushButton_clicked()
{

        this->parentWidget()->show();

        delete this;   //返回直接删除掉这个页面


}
