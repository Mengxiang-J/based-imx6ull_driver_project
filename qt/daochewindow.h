#ifndef DAOCHEWINDOW_H
#define DAOCHEWINDOW_H
#include "distanceworker.h"
#include <QMainWindow>

namespace Ui {
class daocheWindow;
}

class daocheWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit daocheWindow(QWidget *parent = nullptr);
    ~daocheWindow();
    void updateDistance(int value);

    void handleError(const QString &message);

private slots:
    void on_pushButton_clicked();

private:
    Ui::daocheWindow *ui;
    DistanceWorker * m_worker;
};

#endif // DAOCHEWINDOW_H
