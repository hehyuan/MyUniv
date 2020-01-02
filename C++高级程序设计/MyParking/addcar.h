#ifndef ADDCAR_H
#define ADDCAR_H

#include <QWidget>
#include<QMessageBox>
#include"dataBase.h"
namespace Ui {
class addCar;
}

class addCar : public QWidget
{
    Q_OBJECT

public:
    explicit addCar(QWidget *parent = nullptr);
    ~addCar();
private slots:
    void onYesClick();
    void onSizeChange();
private:
    Ui::addCar *ui;
};

#endif // ADDCAR_H
