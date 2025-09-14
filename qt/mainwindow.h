#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QBrush>
#include <QDebug>
#include "music.h"
#include "video.h"
#include "map.h"
#include "weather.h"
#include "daochewindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_daochepushButton_5_clicked();
    
private:
    Ui::MainWindow *ui;

    Weather *weather;
    Map *map;
    Video *video;
    Music *music;
    daocheWindow * daoche;
};

#endif // MAINWINDOW_H
