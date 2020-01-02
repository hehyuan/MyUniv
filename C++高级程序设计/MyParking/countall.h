#ifndef COUNTALL_H
#define COUNTALL_H

#include <QWidget>
#include"dataBase.h"
namespace Ui {
class countAll;
}

class countAll : public QWidget
{
    Q_OBJECT

public:
    explicit countAll(QWidget *parent = nullptr);
    ~countAll();

private:
    Ui::countAll *ui;
};

#endif // COUNTALL_H
