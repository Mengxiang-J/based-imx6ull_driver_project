#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    //设置背景图片
//    QPalette palette;
//    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/bg.jpg")));
//    this->setPalette(palette);

    //cancel border line when on focus
    this->ui->pushButton->setFocusPolicy(Qt::NoFocus);
    this->ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
    this->ui->pushButton_3->setFocusPolicy(Qt::NoFocus);
    this->ui->pushButton_4->setFocusPolicy(Qt::NoFocus);


     //map = new Map(this);
     //video = new Video(this);
     //music = new Music(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//weather
void MainWindow::on_pushButton_clicked()
{
    //点击按钮才创建weather对象
    weather = new Weather(this);
    qDebug() << "weather";
    this->hide();
    weather->show();

}

//map
void MainWindow::on_pushButton_2_clicked()
{
    //点击按钮才创建map对象
    map = new Map(this);
    qDebug() << "map";
    this->hide();
    map->show();
}

//music
void MainWindow::on_pushButton_3_clicked()
{
    //点击按钮才创建music对象
    music = new Music(this);
    qDebug() << "music";
    this->hide();
    music->show();
}


//video
void MainWindow::on_pushButton_4_clicked()
{
    video = new Video(this);
    //点击按钮才创建video对象
    qDebug() << "video";
    this->hide();
    video->show();
}



void MainWindow::on_daochepushButton_5_clicked()
{
    daoche = new daocheWindow(this);
    this->hide();
     daoche->show();

}
