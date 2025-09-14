#include "map.h"
#include "ui_map.h"

int zoom = 10;
int zoom_prev;
//QString center_markers;

Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    this->ui->pushButton->setFocusPolicy(Qt::NoFocus);



    //创建网络请求管理器
    manager= new QNetworkAccessManager(this);

    request = new QNetworkRequest();

    request->setUrl(QUrl(QString("http://api.map.baidu.com/staticimage?center="
                         "%1&markers=%2&width=800&height=480&zoom=%3").
                 arg(ui->comboBox->currentText()).arg(ui->comboBox->currentText()).arg(10)));  //获取资源url

    reply = manager->get(*request);  //请求资源
    //关联网络返回的可读信号
    connect(reply,&QIODevice::readyRead, this, &Map::slot_ready_read);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(slot_download(qint64,qint64)));




    //打开文件
    file = new QFile("./static.png");

    if(file->open(QIODevice::ReadWrite))
    {
         qDebug() << "文件打开成功";
    }
    else
    {
        qDebug() << "文件打开失败";
    }
}

Map::~Map()
{
    delete ui;
}

//back main page
void Map::on_pushButton_clicked()
{
    this->hide();
    this->parentWidget()->show();
}

//用户选择不同定位地点
void Map::on_comboBox_currentTextChanged(const QString &arg)
{
    zoom = 10;

    request->setUrl(QUrl(QString("http://api.map.baidu.com/staticimage?center="
                         "%1&markers=%2&width=800&height=480&zoom=%3").
                 arg(arg).arg(arg).arg(10)));  //获取资源url

    reply = manager->get(*request);  //请求资源

    connect(reply,&QIODevice::readyRead, this, &Map::slot_ready_read);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(slot_download(qint64,qint64)));

    //打开文件
    file = new QFile("./static.png");

    if(file->open(QIODevice::ReadWrite))
    {
         qDebug() << "文件打开成功";
    }
    else
    {
        qDebug() << "文件打开失败";
    }
}

void  Map::slot_ready_read()
{
    file->write(reply->readAll());  //把图片数据写到写到文件中

}
void  Map::slot_download(qint64 current, qint64 total)
{
    if(total < 100)
    {
       zoom  = zoom_prev;
        return;
    }
     qDebug() << "总大小"<<total << "当前下载：" << current;

//   ui->progressBar->setRange(0,total);
//   ui->progressBar->setValue(current);

   if(current == total)
   {

       qDebug() << "文件下载完成!";
       file->close();

       //显示图片到背景上
       QPalette palette;
       palette.setBrush(QPalette::Background,QBrush(QPixmap("./static.png")));
       this->setPalette(palette);

   }
}

//放大图片
void Map::on_pushButton_2_clicked()
{
    zoom_prev = zoom;
    zoom +=3;
    if(zoom > 19)
    {
        zoom = 19;
        return;
    }
    qDebug() << "放大数:" << zoom;
    request->setUrl(QUrl(QString("http://api.map.baidu.com/staticimage?center="
                         "%1&markers=%2&width=800&height=480&zoom=%3").
                 arg(ui->comboBox->currentText()).arg(ui->comboBox->currentText()).arg(zoom)));  //获取资源url

    reply = manager->get(*request);  //请求资源

    connect(reply,&QIODevice::readyRead, this, &Map::slot_ready_read);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(slot_download(qint64,qint64)));

    //打开文件
    file = new QFile("./static.png");

    if(file->open(QIODevice::ReadWrite))
    {
         qDebug() << "文件打开成功";
    }
    else
    {
        qDebug() << "文件打开失败";
    }
}

//缩小图片
void Map::on_pushButton_3_clicked()
{
    zoom_prev = zoom;
    zoom -=3;
    if(zoom < 10)
    {
        zoom =10;
        return;
    }
    qDebug() << "放大数:" << zoom;
    request->setUrl(QUrl(QString("http://api.map.baidu.com/staticimage?center="
                         "%1&markers=%2&width=800&height=480&zoom=%3").
                 arg(ui->comboBox->currentText()).arg(ui->comboBox->currentText()).arg(zoom)));  //获取资源url

    reply = manager->get(*request);  //请求资源

    connect(reply,&QIODevice::readyRead, this, &Map::slot_ready_read);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(slot_download(qint64,qint64)));

    //打开文件
    file = new QFile("./static.png");

    if(file->open(QIODevice::ReadWrite))
    {
         qDebug() << "文件打开成功";
    }
    else
    {
        qDebug() << "文件打开失败";
    }
}
