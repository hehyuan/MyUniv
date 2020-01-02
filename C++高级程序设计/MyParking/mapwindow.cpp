#include "mapwindow.h"
#include "ui_mapwindow.h"

MapWindow::MapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapWindow)
{
    ui->setupUi(this);
    connect(ui->returnBtn,SIGNAL(clicked()),this,SLOT(onClickedBack()));
}

MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::onClickedBack(){
    MainWindow * m = new MainWindow();
    this->close();
    m->show();
}

void MapWindow::onClickedMap(){

}

void MapWindow::paintEvent(QPaintEvent *event){
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };
    QPen pen;
    QBrush brush;
    QRect rect(10, 20, 80, 60);
    QPainterPath path;
    path.moveTo(20, 80);
    path.lineTo(20, 30);
    path.cubicTo(80, 0, 50, 50, 80, 80);
    int startAngle = 20 * 16;
    int arcLength = 120 * 16;
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
}
