#include "map.h"
#include "ui_map.h"

map::map(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::map)
{
    ui->setupUi(this);
}

map::~map()
{
    delete ui;
}
