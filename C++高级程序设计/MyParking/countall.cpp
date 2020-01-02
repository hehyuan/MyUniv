#include "countall.h"
#include "ui_countall.h"

countAll::countAll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::countAll)
{
    ui->setupUi(this);
    setWindowTitle("统计信息");
    QSqlTableModel * model = database::queryAll();
    int rowCnt = model->rowCount();
    int xqcNum = 0,xkNum=0,zkNum = 0,dkNum = 0;
    model->setFilter("size = '小汽车' and is_out = 0");
    xqcNum = model->rowCount();
    model->setFilter("size = '小卡' and is_out = 0");
    xkNum = model->rowCount();
    model->setFilter("size =  '中卡'and is_out = 0");
    zkNum = model->rowCount();
    model->setFilter("size =    '大卡' and is_out = 0");
    dkNum = model->rowCount();
    ui->carNum->setText(QString::number(rowCnt));
    ui->sizeCar->setText(QString::number(xqcNum)+","+QString::number(xkNum)+","+QString::number(zkNum)+","+QString::number(dkNum)+"辆");
    int dayNum = 0;
    model->setFilter("abs(DATEDIFF(in_time,now()))<1");
    dayNum = model->rowCount();
    ui->todayCar->setText(QString::number(dayNum));
}

countAll::~countAll()
{
    delete ui;
}
