#ifndef IN_H
#define IN_H

#include <QMainWindow>
#include"dataBase.h"
#include<qtimer.h>
#include<qdatetime.h>
#include<QtSql>
#include<QString>
#include"mainwindow.h"
namespace Ui {
class in;
}

class in : public QMainWindow
{
    Q_OBJECT

public:
    explicit in(QWidget *parent = nullptr);
    ~in();
    void initWindow();
    QString queryEmptyPos(int flag);
private slots:
    void onBackClicked();
    void showTime();
    void onEnterClicked();
    void onSizeChanged();
private:
    Car car;
    Ui::in *ui;
};

#endif // IN_H
