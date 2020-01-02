#include "addcar.h"
#include "ui_addcar.h"

addCar::addCar(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::addCar)
{
    ui->setupUi(this);
    setWindowTitle("管理员添加车辆");
    connect(ui->yesBtn, SIGNAL(clicked()), this, SLOT(onYesClick()));
    connect(ui->size, SIGNAL(currentTextChanged(QString)), this, SLOT(onSizeChange()));
    onSizeChange();
}

addCar::~addCar()
{
    delete ui;
}

void addCar::onSizeChange()
{
    ui->position->clear();
    int flag = ui->size->currentIndex();
    QStringList list = database::queryVipEmptyPos(flag);
    for (int i = 0; i < list.length(); ++i)
    {
        ui->position->addItem(list[i]);
    }
}
void addCar::onYesClick()
{
    if (ui->plate->isEnabled())
    {
        QMessageBox msgBox;
        QString plate = ui->plate->text();
        QString size = ui->size->currentText();
        int flag = ui->size->currentIndex();
        QString pos = ui->position->currentText();
        QString inTime  = ui->dateTimeEdit->text();
        if(plate.length()!=7){
            msgBox.setText("不规范的车牌号!");
            msgBox.exec();
            return;
        }
        if (pos.length() < 2)
        {
            return; //出错
        }
        else
        {
            int num = 0;
            QString str1, str2;
            bool douhao = false;
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
        }
        QString hasPlate = database::queryPos(plate);
        if (hasPlate.length() > 0 && hasPlate != "false")
        {
            msgBox.setText("已经存在这条记录!");
            msgBox.exec();
            return;
        }
        database::updateParking(pos,"full");
        database::insertRecords(plate,size,pos,inTime);
        ui->position->clear();
        flag = ui->size->currentIndex();
        QStringList list = database::queryVipEmptyPos(flag);
        for (int i = 0; i < list.length(); ++i)
        {
            ui->position->addItem(list[i]);
        }
        msgBox.setText("添加记录成功!");
        msgBox.exec();
    }
}
