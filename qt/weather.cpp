#include "weather.h"
#include "ui_weather.h"
#include "weather.h"
#include <QMouseEvent>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>
#include <QMap>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMenu>


Weather::Weather(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Weather)
{
    ui->setupUi(this);
    myMenu = new QMenu(this);
    myMenu->addAction(QIcon(":/res/close.png"),"关闭");

    connect(myMenu, &QMenu::triggered,this,[=]()
            {
        this->close();
    });
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &Weather::replyFinished);
    eageurl = "http://gfeljm.tianqiapi.com/api?unescape=1&version=v9&appid=56886465&appsecret=a4c7hIKT";


    netreplay= manager->get(QNetworkRequest(QUrl("http://gfeljm.tianqiapi.com/api?unescape=1&version=v9&appid=56886465&appsecret=a4c7hIKT")));


    //开始存储对应的city code

    QString search_name = ui->lineEdit_searchcity->text();
    //然后更新所有ui的值，首先查找json文件并解析
    QFile file(":/res/output.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QByteArray jsonData = in.readAll().toUtf8();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonObj = jsonDoc.object();
    for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
        QString key = it.key();
        QString value = it.value().toString();
        map_citycode.insert(key, value);
    }
}



Weather::~Weather()
{
    delete ui;
}

void Weather::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        myMenu->exec(QCursor::pos());
    }
    if(event->button() == Qt::LeftButton)
    {
        //得到当前位置的偏移量
        moveOffet = event->globalPos() - this->pos()  ;
    }
}

void Weather::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()-moveOffet);

}

void Weather::replyFinished(QNetworkReply *reply)
{
    netreplay = reply;
    int code = netreplay->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(code !=200&& netreplay->error()==QNetworkReply::NoError)
    {
        qDebug()<<netreplay->error();
    }
    //获得请求的数据
    QByteArray  getData =  netreplay->readAll();
    parseWeatherJsonData(getData);


}

void Weather::parseWeatherJsonData(QByteArray rawData)
{
    vect_weather.clear();
    WeatherData temp_day;
    QJsonDocument jsonobj = QJsonDocument::fromJson(rawData);
    if(!jsonobj.isNull() && jsonobj.isObject())
    {


        QJsonObject objRoot = jsonobj.object();
        ui->label_city->setText(objRoot["city"].toString());
        ui->label_9->setText(objRoot["aqi"].toObject()["pm25"].toString());


        QJsonArray qarray = objRoot["data"].toArray();
        for(int i=0;i<qarray.size();i++)
        {

            temp_day.data = qarray[i].toObject()["date"].toString();
            temp_day.wea_day = qarray[i].toObject()["wea"].toString();
            temp_day.tem =  qarray[i].toObject()["tem"].toString();
            temp_day.tem1 =  qarray[i].toObject()["tem1"].toString();
            temp_day.tem2 =  qarray[i].toObject()["tem2"].toString();
            temp_day.win_speed = qarray[i].toObject()["win_speed"].toString();
            temp_day.humidity = qarray[i].toObject()["humidity"].toString();
            temp_day.air_level = qarray[i].toObject()["air_level"].toString();
            temp_day.win = qarray[i].toObject()["win"].toArray()[0].toString();
            temp_day.air_tips =qarray[i].toObject()["air_tips"].toString();
            vect_weather.push_back(temp_day);
        }


        qDebug()<<vect_weather[0].data;
        qDebug()<<vect_weather[0].wea_day;
        qDebug()<<vect_weather[0].tem1;
        QString dataweek =objRoot["data"].toArray()[0].toObject()["week"].toString();
        ui->label_data->setText(vect_weather[0].data+" "+dataweek);
        //获取天气晴朗值
        ui->label_wea->setText(vect_weather[0].wea_day);
        //获取温度范围
        ui->label_17->setText(vect_weather[0].tem1+"~"+vect_weather[0].tem1);

        ui->label_15->setText(vect_weather[0].tem);
        ui->label_tempvalue->setText(vect_weather[0].humidity);

        ui->label_WindType->setText(vect_weather[0].win);
        ui->label_windlevel->setText(vect_weather[0].win_speed);

        ui->label_13->setText(vect_weather[0].air_level);


        ui->label->setText(vect_weather[0].air_tips);


    }





}






void Weather::on_pushButton_2_clicked()
{
    QString search_name = ui->lineEdit_searchcity->text();
    //然后更新所有ui的值，首先查找json文件并解析


    QString cityid = map_citycode[search_name];
    qDebug()<<cityid;
    if(cityid=="")
    {
        QString title = "警告";
        QString text = "查找失败请重新查找！！！";
        QMessageBox messageBox;
        messageBox.setWindowTitle(title);
        messageBox.setText(text);
        messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel); // 添加标准按钮
        messageBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
        messageBox.exec(); // 显示对话框并等待用户响应
    }
    eageurl+= "&cityid="+cityid;
    manager->get(QNetworkRequest(QUrl(eageurl)));

}

void Weather::on_pushButton_clicked()
{
    //back main page

    this->parentWidget()->show();

    delete this;   //返回直接删除掉这个页面


}
