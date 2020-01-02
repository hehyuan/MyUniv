#include "in.h"
#include "ui_in.h"
#include <QString>

in::in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::in)
{
    ui->setupUi(this);
    setWindowTitle("Parking");
    this->initWindow();
    connect(ui->returnBtn,SIGNAL(clicked()),this,SLOT(onBackClicked()));
    connect(ui->enterBtn,SIGNAL(clicked()),this,SLOT(onEnterClicked()));
    connect(ui->Carsize, SIGNAL(currentTextChanged(QString)), this, SLOT(onSizeChanged()));
}

in::~in()
{
    delete ui;
}

void in::initWindow()
{
    QTimer* timer = new QTimer(this);
    showTime();
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer ->start(1000);
    ui->position->clear();
    int flag = ui->Carsize->currentIndex();
    QStringList list = database::queryAllEmptyPos(flag);
    for (int i = 0; i < list.length(); ++i)
    {
        ui->position->addItem(list[i]);
    }
}

QString in::queryEmptyPos(int flag)
{
    return database::queryEmptyPos(flag);
}

void in:: showTime() {
    QDateTime dt;
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    QString currentDate = dt.toString("yyyy-MM-dd hh:mm:ss");
    ui->timeLabel->setText(currentDate);
}

void in::onBackClicked(){
    MainWindow *m = new MainWindow();
    this->close();
    m->show();
}

void in::onEnterClicked(){
    if(ui->plate->isEnabled()){
        QString plate = ui->plate->text(); //车牌号
        QString inTime = ui->timeLabel->text();//入场时间
        int flag = ui->Carsize->currentIndex();
        QString size = ui->Carsize->currentText();
        QString pos = ui->position->currentText();
        QMessageBox msgBox;
        QString hasPlate = database::queryPos(plate);
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
         hasPlate = database::queryPos(plate);
        if (hasPlate.length() > 0 && hasPlate != "false")
        {
            msgBox.setText("已经存在这条记录!");
            msgBox.exec();
            return;
        }
        database::updateParking(pos,"full");
        database::insertRecords(plate,size,pos,inTime);
        ui->position->clear();
        flag = ui->Carsize->currentIndex();
        QStringList list = database::queryAllEmptyPos(flag);
        for (int i = 0; i < list.length(); ++i)
        {
            ui->position->addItem(list[i]);
        }
        msgBox.setText("添加记录成功!");
        msgBox.exec();
        this -> initWindow();
    }
}

void in::onSizeChanged()
{
    ui->position->clear();
    int flag = ui->Carsize->currentIndex();
    QStringList list = database::queryAllEmptyPos(flag);
    for (int i = 0; i < list.length(); ++i)
    {
        ui->position->addItem(list[i]);
    }
}
