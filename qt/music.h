#ifndef MUSIC_H
#define MUSIC_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QDebug>
#include <QListWidget>
#include <QTimer>
#include <QFile>
#include <QStringList>

namespace Ui {
class Music;
}

class Music : public QMainWindow
{
    Q_OBJECT

public:
    explicit Music(QWidget *parent = 0);
    ~Music();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_horizontalSlider_3_sliderPressed();

    void on_horizontalSlider_3_sliderReleased();

private:
    Ui::Music *ui;

    QProcess *process;
    QTimer *timer;

    QFile *lrc_file_ljj;
    QFile *lrc_file_zjl;

    QStringList lrc_ljj_stringlist;
    QStringList lrc_zjl_stringlist;

};

#endif // MUSIC_H
