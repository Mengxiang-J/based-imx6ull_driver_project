#ifndef WEATHER_H
#define WEATHER_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QLabel>
#include "weatherdata.h"
namespace Ui {
class Weather;
}

class Weather : public QMainWindow
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = 0);
    ~Weather();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void replyFinished(QNetworkReply *reply);
    void parseWeatherJsonData(QByteArray rawData);
private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Weather *ui;
    QMenu * myMenu;
    QPoint moveOffet;
    QString eageurl;
    QMap<QString,QString> map_citycode;

    QNetworkAccessManager *manager;
    QNetworkReply *netreplay;
    //用vector存储WeatherData 对象
    QVector<WeatherData> vect_weather;
};





#endif // WEATHER_H
