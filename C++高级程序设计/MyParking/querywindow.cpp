#include "querywindow.h"
#include "ui_querywindow.h"

queryWindow::queryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::queryWindow)
{
    ui->setupUi(this);
    setWindowTitle("查询窗口");
    connect(ui->queryBtn,SIGNAL(clicked()),this,SLOT(onQueryClick()));
}

queryWindow::~queryWindow()
{
    delete ui;
}
void queryWindow::onQueryClick(){
    QString plate = ui->plate->text();
    QString size = ui->size->currentText();
    if(plate.length()!=7){
        QMessageBox msgBox;
        msgBox.setText("车牌号格式错误,按车型展示结果!");
        msgBox.exec();
    }
    QSqlTableModel * model = database::queryWithCondition(plate,size);
    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}
