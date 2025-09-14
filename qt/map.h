#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QDebug>

namespace Ui {
class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = 0);
    ~Map();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void  slot_ready_read();
    void  slot_download(qint64, qint64);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Map *ui;

    QNetworkAccessManager *manager;
    //设置网络请求连接
    QNetworkRequest *request;
    QNetworkReply * reply;

    QFile *file;
};

#endif // MAP_H
