#ifndef VIDEO_H
#define VIDEO_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QDebug>
#include <QListWidget>
#include <QTimer>

namespace Ui {
class Video;
}

class Video : public QMainWindow
{
    Q_OBJECT

public:
    explicit Video(QWidget *parent = 0);
    ~Video();
    void initControls();
    void initSliders();
    QWidget *videoContainer;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //void on_listWidget_currentTextChanged(const QString &currentText);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    //void on_horizontalSlider_3_sliderMoved(int position);

    void on_horizontalSlider_3_sliderPressed();

    void on_horizontalSlider_3_sliderReleased();

private:
    Ui::Video *ui;

    QProcess *process;

    QTimer *timer;
};

#endif // VIDEO_H
