#ifndef HHH_H
#define HHH_H

#include <QMainWindow>

namespace Ui {
class hhh;
}

class hhh : public QMainWindow
{
    Q_OBJECT

public:
    explicit hhh(QWidget *parent = nullptr);
    ~hhh();

private:
    Ui::hhh *ui;
};

#endif // HHH_H
