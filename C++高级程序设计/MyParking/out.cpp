#include "out.h"
#include "ui_out.h"

out::out(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::out)
{
    ui->setupUi(this);
    setWindowTitle("Taking");
    QTimer* timer = new QTimer(this);
    showTime();
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer ->start(1000);
    connect(ui->returnBtn,SIGNAL(clicked()),this,SLOT(onBackClicked()));
    connect(ui->takeBtn,SIGNAL(clicked()),this,SLOT(onTakeCar()));
}

out::~out()
{
    delete ui;
}
void out:: showTime() {
    QDateTime dt;
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    QString currentDate = dt.toString("yyyy-MM-dd hh:mm:ss");
    ui->timeLabel->setText(currentDate);
}
void out::onBackClicked(){
    MainWindow * m = new MainWindow();
    this->close();
    m->show();
}

void out::onTakeCar(){
    if(ui->plate->isEnabled()){
        int row,col;
        QString plate = ui->plate->text(); //车牌号
        QString outTime = ui->timeLabel->text();//入场时间
        QMessageBox msgBox;
        QString plateId = database::queryPos(plate);
        QSqlQuery qry;
        QString sql;
        msgBox.setText(plateId);
        msgBox.exec();
        if(plateId=="false"){
            msgBox.setText("You are not in, please recheck your plate!");
            msgBox.exec();
            return;
        }else{// 开始取车
            sql = "SELECT `in_time` FROM `records` WHERE  `is_out` = 0  and `plate` = '"+(plate)+ "';";
            qry.prepare(sql);
            if( !qry.exec() )
                qDebug() << qry.lastError();
            QDateTime begin;
            while(qry.next())
                 begin = qry.value(0).toDateTime();
            msgBox.setText("begin:"+begin.toString("yyyy-MM-dd hh:mm:ss"));
            msgBox.exec();
            QDateTime end;
            QTime time;
            QDate date;
            end.setTime(time.currentTime());
            end.setDate(date.currentDate());
            msgBox.setText("end:"+end.toString("yyyy-MM-dd hh:mm:ss"));
            msgBox.exec();
            uint hours = (end.toTime_t()-begin.toTime_t())/(60*60); // minutes
            msgBox.setText("Your total parking time is "+ QString::number(hours)+" h"+"\ntotal cost:"+QString::number(hours*fee)+"$");
            msgBox.exec();
        }
            row = plateId.toInt()/11+1;
            col = plateId.toInt()%11;
            sql = "UPDATE `parking` SET `status` = 'free' WHERE `id` = \""+plateId+"\"";
            qry.prepare(sql);
            if( !qry.exec() )
                qDebug() << qry.lastError();
            sql = "UPDATE `records` SET `is_out`=1 WHERE `plate`=\""+plate+"\"";
            qry.prepare(sql);
            if( !qry.exec() )
                qDebug() << qry.lastError();
            msgBox.setText("Take successfully!");
            msgBox.exec();
    }
}
