#include "login.h"
#include "ui_login.h"


login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    connect(ui->btn,SIGNAL(clicked()),this,SLOT(onClickBtn()));
}

login::~login()
{
    delete ui;
}

void login::onClickBtn(){
    QString username = ui->username->text();
    QString password = ui->password->text();
    qDebug() << username;
    QSqlQuery qry;
    qry.prepare( "SELECT * FROM `user` WHERE `username` = '"+username+"' and `password` = '"+password+"' LIMIT 1" );
    if(!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        if(qry.next()){
            admin * AdminWindow;
            AdminWindow = new admin();
            this->close();
            AdminWindow->show();
        }else{
            QMessageBox msgBox;
            msgBox.setText("用户名密码错误!");
            msgBox.exec();
        }
    }
}
