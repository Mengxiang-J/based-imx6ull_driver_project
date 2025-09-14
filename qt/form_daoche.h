#ifndef FORM_DAOCHE_H
#define FORM_DAOCHE_H
#include "distanceworker.h"
#include <QWidget>

namespace Ui {
class Form_daoche;
}

class Form_daoche : public QWidget
{
    Q_OBJECT

public:

    explicit Form_daoche(QWidget *parent = nullptr);
    ~Form_daoche();
    void updateDistance(int value);

    void handleError(const QString &message);

private slots:
    void on_pushButton_clicked();

private :
    DistanceWorker * m_worker;
private:
    Ui::Form_daoche *ui;
};

#endif // FORM_DAOCHE_H
