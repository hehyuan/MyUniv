#include "reservecar.h"
#include "ui_reservecar.h"

reserveCar::reserveCar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reserveCar)
{
    ui->setupUi(this);
    setWindowTitle("预约车辆");
    connect(ui->size,SIGNAL(currentTextChanged(QString)),this,SLOT(onSizeChanged()));
    connect(ui->yesBtn,SIGNAL(clicked()),this,SLOT(onYesClick()));
    connect(ui->noBtn,SIGNAL(clicked()),this,SLOT(onNoClick()));
    onSizeChanged();
}

reserveCar::~reserveCar()
{
    delete ui;
}
void reserveCar::onNoClick(){
    QString pos = ui->position->currentText();
    int num = 0;
    QString str1, str2;
    bool douhao = false;
    //根据行列算出对应的id
    for (int i = 0; i < pos.length(); ++i)
    {
        if (pos[i] == "(" || pos[i] == ")")
        {
            continue;
        }
        if (pos[i] == ",")
        {
            douhao = true;
        }
        if (pos[i].isDigit())
        {
            if (douhao == false)
                str1.append(pos[i]);
            else
                str2.append(pos[i]);
        }
    }
    num = 10 * (str1.toInt() - 1) + str2.toInt();
    pos = QString::number(num);
    QMessageBox msgBox;
    database::updateParking(pos,"free");
    msgBox.setText("取消预约成功!");
    msgBox.exec();
    ui->position->clear();
    int flag = ui->size->currentIndex();
    QStringList list = database::queryVipEmptyPos(flag);
    for (int i = 0; i < list.length(); ++i)
    {
        ui->position->addItem(list[i]);
    }
}
void reserveCar::onYesClick(){
    QString pos = ui->position->currentText();
    int num = 0;
    QString str1, str2;
    bool douhao = false;
    //根据行列算出对应的id
    for (int i = 0; i < pos.length(); ++i)
    {
        if (pos[i] == "(" || pos[i] == ")")
        {
            continue;
        }
        if (pos[i] == ",")
        {
            douhao = true;
        }
        if (pos[i].isDigit())
        {
            if (douhao == false)
                str1.append(pos[i]);
            else
                str2.append(pos[i]);
        }
    }
    num = 10 * (str1.toInt() - 1) + str2.toInt();
    pos = QString::number(num);
    QMessageBox msgBox;
    database::updateParking(pos,"reserved");
    msgBox.setText("预约成功!");
    msgBox.exec();
    ui->position->clear();
    int flag = ui->size->currentIndex();
    QStringList list = database::queryVipEmptyPos(flag);
    for (int i = 0; i < list.length(); ++i)
    {
        ui->position->addItem(list[i]);
    }
};

void reserveCar::onSizeChanged(){
    ui->position->clear();
    int flag = ui->size->currentIndex();
    QStringList list = database::queryVipEmptyPos(flag);
    for (int i = 0; i < list.length(); ++i)
    {
        ui->position->addItem(list[i]);
    }
};
