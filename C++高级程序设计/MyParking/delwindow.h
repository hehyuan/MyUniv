#ifndef DELWINDOW_H
#define DELWINDOW_H

#include <QWidget>
#include"dataBase.h"
namespace Ui {
class delWindow;
}

class delWindow : public QWidget
{
    Q_OBJECT

public:
    explicit delWindow(QWidget *parent = nullptr);
    ~delWindow();
private slots:
    void onDelClick();
private:
    Ui::delWindow *ui;
};

#endif // DELWINDOW_H
