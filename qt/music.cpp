#include "music.h"
#include "ui_music.h"

bool music_playing_flag = 0;
bool music_start_once = 1;

QString music_total_length; //music总时长
QString music_current_pos; //music当前进度

Music::Music(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Music)
{
    ui->setupUi(this);
    this->ui->pushButton->setFocusPolicy(Qt::NoFocus);
    this->ui->horizontalSlider->setFocusPolicy(Qt::NoFocus);
    this->ui->horizontalSlider_3->setFocusPolicy(Qt::NoFocus);

    this->setStyleSheet("background-image: url(:/img/ljj.jpg);");   //set backgroung as jj

    process = new QProcess(this);

    ui->listWidget->addItem("ljj-jj.mp3");
    ui->listWidget->addItem("zjl-yq.mp3");
    ui->listWidget->setCurrentRow(0);

    //set volume range
    ui->horizontalSlider->setRange(0,100);
    //se default volume
    ui->horizontalSlider->setValue(5);
    ui->label_volume_percent->setText(QString("%1%").arg(ui->horizontalSlider->value()));

    //获取总时长
    connect(process,&QProcess::readyRead,[=](){

        QString msg = QString(process->readAll());
        QString tmp = msg;

        // qDebug() << "[--------------all---------------]" <<tmp;

        if(tmp.indexOf("ANS_LENGTH=") != -1)
        {
            //qDebug() << "contains-----" <<tmp;
            int start = tmp.indexOf(QString("ANS_LENGTH="));
            //int end =
            QString len  = tmp.mid(start+11, 100);
            len.chop(4);
            //qDebug() << "right-----" <<  start <<":"<<tmp;

            music_total_length = len;

            QString minute; minute.sprintf("%02d", music_total_length.toInt()/60);
            QString second; second.sprintf("%02d", music_total_length.toInt()%60);

            //qDebug() << "label_total_length---------" << music_total_length;
            ui->label_total_length->setText(QString("%1:%2").arg(minute).arg(second));
            ui->horizontalSlider_3->setRange(0,music_total_length.toInt());
        }
        else if(msg.indexOf("ANS_TIME_POSITION=") != -1)
        {
            //qDebug() << "------contains-----" <<msg;
            int start = msg.indexOf(QString("ANS_TIME_POSITION="));
            QString pos  = msg.mid(start+18, 100);
            pos.chop(3);
            music_current_pos= pos;
            //qDebug() << "pos-----" <<":"<<pos;

            //QString minute = QString("%1").arg(music_current_pos.toInt()/60);
            //QString second = QString("%1").arg(music_current_pos.toInt()%60);

            QString minute; minute.sprintf("%02d", music_current_pos.toInt()/60);
            QString second; second.sprintf("%02d", music_current_pos.toInt()%60);


            //qDebug() << minute << ":"<<  second;

            //QString lrc_line = QString("lrc_file_ljj->readLine(64)");
            if(ui->listWidget->currentItem()->text() == "ljj-jj.mp3")
            {
                for(int i=0; i < lrc_ljj_stringlist.size(); i++)
                {
                    //qDebug() << lrc_ljj_stringlist.at(i);
                    QString tmp =  lrc_ljj_stringlist.at(i);
                    if(tmp.contains(QString("[%1:%2").arg(minute).arg(second)))
                    {
                        ui->label_lrc->setText(tmp.mid(10,100));
                    }

                }
            }
            else if(ui->listWidget->currentItem()->text() == "zjl-yq.mp3")
            {
                for(int i=0; i < lrc_zjl_stringlist.size(); i++)
                {
                    //qDebug() << lrc_ljj_stringlist.at(i);
                    QString tmp =  lrc_zjl_stringlist.at(i);
                    if(tmp.contains(QString("[%1:%2").arg(minute).arg(second)))
                    {
                        ui->label_lrc->setText(tmp.mid(10,100));
                    }

                }

            }





            ui->label_current_pos->setText(QString("%1:%2").arg(minute).arg(second));
            ui->horizontalSlider_3->setValue(music_current_pos.toInt());

            if(music_current_pos == QString("%1").arg(music_total_length.toInt()-2))
            {
                on_pushButton_3_clicked();//next song
            }

            //qDebug() << QString(lrc_file_ljj->readLine(64));
            //ui->label_lrc->setText(QString(lrc_file_ljj->readLine(64)).left(6));
        }
    });


    timer = new QTimer(this);

    connect(timer,&QTimer::timeout,[=](){

        process->write("get_time_pos\n");
    });

    lrc_file_ljj = new QFile("ljj-jj.lrc");  //jj
    lrc_file_zjl = new QFile("zjl-yq.lrc");

    if(lrc_file_ljj->open(QIODevice::ReadWrite) && lrc_file_zjl->open(QIODevice::ReadWrite))
    {
         qDebug() << "lrc file open success";
         lrc_ljj_stringlist = QString(lrc_file_ljj->readAll()).split("\r\n");
         lrc_zjl_stringlist = QString(lrc_file_zjl->readAll()).split("\r\n");
    }
    else
    {
        qDebug() << "lrc file open error";
    }

    //ui->label_lrc->setStyleSheet("QLabel {background-color: transparent;}");

}

Music::~Music()
{
    delete ui;
}

//back main page
void Music::on_pushButton_clicked()
{
    //this->hide();
    this->parentWidget()->show();

    delete this;   //返回直接删除掉这个页面

    music_start_once = 1;
}


//start or stop
void Music::on_pushButton_2_clicked()
{

    if(music_start_once)
    {
        music_start_once = 0;
        process->start(QString("mplayer -quiet -slave ./%1").arg(ui->listWidget->currentItem()->text()));
        process->write(QString("volume %1 1\n").arg(ui->horizontalSlider->value()).toStdString().c_str());

        music_playing_flag = 1;

        ui->pushButton_2->setStyleSheet("border-image: url(:/img/pause.png);");

        //获取总时长
        process->write("get_time_length\n");
        timer->start(1000); //ms

        return;
    }


    if(music_playing_flag)   //暂停
    {
        process->write("pause\n");
        music_playing_flag = 0;
        ui->pushButton_2->setStyleSheet("border-image: url(:/img/play.png);");

        timer->stop();
    }
    else
    {
        process->write("pause\n");   //播放
        music_playing_flag = 1;
        ui->pushButton_2->setStyleSheet("border-image: url(:/img/pause.png);");

        timer->start();
    }

}

//set volume
void Music::on_horizontalSlider_valueChanged(int value)
{
    ui->label_volume_percent->setText(QString("%1%").arg(value));

    if(music_playing_flag)
    {
        process->write(QString("volume %1 1\n").arg(value).toStdString().c_str());
    }
}

//fast-forward  10s
void Music::on_pushButton_5_clicked()
{
    process->write("seek +10\n");
}

//fast_backward 10s
void Music::on_pushButton_6_clicked()
{
    process->write("seek -10\n");
}



//skip-forward  next music
void Music::on_pushButton_3_clicked()
{
    timer->stop();
    if(process->state() == QProcess::Running)
    {
        //杀死当前进程
        process->kill();
        //回收资源
        process->waitForFinished();
    }
    int index = ui->listWidget->currentRow();
    index = (index+1)%2;
    ui->listWidget->setCurrentRow(index);
    process->start(QString("mplayer -quiet -slave ./%1").arg(ui->listWidget->currentItem()->text()));
    process->write(QString("volume %1 1\n").arg(ui->horizontalSlider->value()).toStdString().c_str());

    //set playing_flag
    music_playing_flag = 1;
    ui->pushButton_2->setStyleSheet("border-image: url(:/img/pause.png);");

    if(ui->listWidget->currentItem()->text() == "ljj-jj.mp3")
    {
        this->setStyleSheet("background-image: url(:/img/ljj.jpg);");
    }
    else if(ui->listWidget->currentItem()->text() == "zjl-yq.mp3")
    {
        this->setStyleSheet("background-image: url(:/img/zjl.jpeg);");
    }
    //获取总时长
    process->write("get_time_length\n");

    timer->start();

    ui->label_lrc->clear();
}

//skip-backward  prev music
void Music::on_pushButton_4_clicked()
{
    if(process->state() == QProcess::Running)
    {
        //杀死当前进程
        process->kill();
        //回收资源
        process->waitForFinished();
    }
    int index = ui->listWidget->currentRow();
    index = index - 1;
    if(index == -1)
    {
        index = 1;
    }
    ui->listWidget->setCurrentRow(index);
    process->start(QString("mplayer -quiet -slave ./%1").arg(ui->listWidget->currentItem()->text()));
    process->write(QString("volume %1 1\n").arg(ui->horizontalSlider->value()).toStdString().c_str());

    //set playing_flag
    music_playing_flag = 1;
    ui->pushButton_2->setStyleSheet("border-image: url(:/img/pause.png);");

    if(ui->listWidget->currentItem()->text() == "ljj-jj.mp3")
    {
        this->setStyleSheet("background-image: url(:/img/ljj.jpg);");
    }
    else if(ui->listWidget->currentItem()->text() == "zjl-yq.mp3")
    {
        this->setStyleSheet("background-image: url(:/img/zjl.jpeg);");
    }
    //获取总时长
    process->write("get_time_length\n");

    ui->label_lrc->clear();
}


//process bar press
void Music::on_horizontalSlider_3_sliderPressed()
{
    timer->stop();

}
//process bar release
void Music::on_horizontalSlider_3_sliderReleased()
{
    int pos = ui->horizontalSlider_3->value();

    if(music_playing_flag)
    {

        if(  pos >= music_current_pos.toInt())
        {
            process->write(QString("seek %1\n").arg((pos - music_current_pos.toInt())).toStdString().c_str());
        }
        else
        {
            process->write(QString("seek %1\n").arg((pos - music_current_pos.toInt())).toStdString().c_str());
        }

        music_current_pos = pos;
    }
    timer->start();
}
