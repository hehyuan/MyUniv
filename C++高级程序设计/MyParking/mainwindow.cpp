#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSpinBox>
#include <qboxlayout.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Parking System");
    connect(ui->enterParking,SIGNAL(clicked()),this,SLOT(onClickEnter()));
    connect(ui->takeCarBtn,SIGNAL(clicked()),SLOT(onClickOut()));
    connect(ui->mapBtn,SIGNAL(clicked()),this,SLOT(onClickMap()));
    connect(ui->signInBtn,SIGNAL(clicked()),this,SLOT(onClickSignIn()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickEnter(){
    in * inWindow;
    inWindow = new in();
    this->close();
    inWindow->show();
}

void MainWindow::onClickOut(){
    out* outWindow;
    outWindow = new out();
    this->close();
    outWindow->show();
}

void MainWindow::onClickMap(){
    drawMap* mapWindow;
    mapWindow  = new drawMap();
//    this->close();
    mapWindow->show();
}

void MainWindow::onClickSignIn(){
    login * logWindow;
    logWindow = new login();
//    this->close();
    logWindow->show();
}
