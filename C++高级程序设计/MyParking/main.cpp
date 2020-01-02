#include "mainwindow.h"
#include"dataBase.h"
#include<ctime>
#include<iostream>
#include <QApplication>
#include <QtWidgets>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    database *db = new database;
//    db->init();
    MainWindow w;
    w.show();
    return app.exec();

}
