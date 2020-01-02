#include "hhh.h"
#include "ui_hhh.h"

hhh::hhh(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hhh)
{
    ui->setupUi(this);
}

hhh::~hhh()
{
    delete ui;
}
