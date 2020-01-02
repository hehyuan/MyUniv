#ifndef RESERVECAR_H
#define RESERVECAR_H

#include <QWidget>
#include"dataBase.h"
namespace Ui {
class reserveCar;
}

class reserveCar : public QWidget
{
    Q_OBJECT

public:
    explicit reserveCar(QWidget *parent = nullptr);
    ~reserveCar();
private slots:
    void onYesClick();
    void onSizeChanged();
    void onNoClick();
private:
    Ui::reserveCar *ui;
};

#endif // RESERVECAR_H
