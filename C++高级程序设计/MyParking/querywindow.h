#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <QWidget>
#include"dataBase.h"
namespace Ui {
class queryWindow;
}

class queryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit queryWindow(QWidget *parent = nullptr);
    ~queryWindow();
private slots:
    void onQueryClick();
private:
    Ui::queryWindow *ui;
};

#endif // QUERYWINDOW_H
