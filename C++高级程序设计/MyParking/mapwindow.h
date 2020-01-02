#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QMainWindow>
#include"mainwindow.h"
#include<QPainter>
namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    ~MapWindow();
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onClickedBack();
    void onClickedMap();
private:
    Ui::MapWindow *ui;
};

#endif // MAPWINDOW_H
