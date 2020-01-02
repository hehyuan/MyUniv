#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include"dataBase.h"
#include<qtimer.h>
#include<qdatetime.h>
#include<QtSql>
#include<QString>
#include"mainwindow.h"
#include"querywindow.h"
#include"delwindow.h"
#include"addcar.h"
#include"reservecar.h"
#include"countall.h"
namespace Ui {
class admin;
}

class admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
private slots:
    void onReturnClicked();
    void onAddCarClicked();
    void onDelCarClicked();
    void onEditClicked();
    void onCountClicked();
    void onQueryClicked();
    void onReserveClicked();
    void onQueryAllClicked();
    void onExitClicked();
private:
    Ui::admin *ui;
};

#endif // ADMIN_H
