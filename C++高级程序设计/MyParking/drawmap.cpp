#include "drawmap.h"
#include "ui_drawmap.h"

drawMap::drawMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drawMap)
{
    col = 0;
    row = 0;
    ui->setupUi(this);
    setWindowTitle("地图");
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    this->updatesEnabled();
    connect(ui->drawBtn,SIGNAL(clicked()),this,SLOT(onDrawClick()));
}

drawMap::~drawMap()
{
    delete ui;
}

void drawMap::paintEvent(QPaintEvent *event){
    QRect rect(width()/3,10,100,100);
    this->maximumSize();
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(QColor(0, 160, 90));
    for(int i = width()/5,cnti=1;i<width()&&cnti<=10;i+=width()/15,cnti++){
        for(int j = height()/4,cntj=1;j<height()&&cntj<=10;j+=height()/15,cntj++){
            if(cnti==row&&cntj==col){
                painter.setBrush(QColor(255,0,0));
                painter.drawRect(QRect(i,j,30,40));
                painter.drawText(QRect(i,j,30,40),"your car");
                painter.setBrush(QColor(0, 160, 90));
                continue;
            }
             painter.drawRect(QRect(i,j,30,40));
        }
    }
}

void drawMap::onDrawClick(){
    QString plate = ui->plate->text();
    QMessageBox msgBox;
    QString pos = database::queryPos(plate);
    if(pos=="false"){
        msgBox.setText("不存在这辆车!");
        msgBox.exec();
        return;
    }else{
        int num = pos.toInt();
        row = (num-1)/10+1;
        col = num - (row-1)*10;
        msgBox.setText("第"+QString::number(row)+"行,第"+QString::number(col)+"列");
        msgBox.exec();
    }
}
