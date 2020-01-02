#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtGui>
#include<QDialog>
#include <QButtonGroup>
#include"in.h"
#include"out.h"
#include"drawmap.h"
#include"login.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:

private slots:
    void onClickEnter();
    void onClickOut();
    void onClickMap();
    void onClickSignIn();
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
