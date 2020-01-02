#ifndef OUT_H
#define OUT_H
#include"mainwindow.h"
#include <QMainWindow>
#define fee 1
namespace Ui {
class out;
}

class out : public QMainWindow
{
    Q_OBJECT

public:
    explicit out(QWidget *parent = nullptr);
    ~out();
private slots:
    void onBackClicked();
    void onTakeCar();
    void showTime();
private:
    Ui::out *ui;
};

#endif // OUT_H
