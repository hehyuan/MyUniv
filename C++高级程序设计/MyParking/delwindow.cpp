#include "delwindow.h"
#include "ui_delwindow.h"

delWindow::delWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delWindow)
{
    ui->setupUi(this);
    setWindowTitle("删除车辆");
    connect(ui->delBtn,SIGNAL(clicked()),this,SLOT(onDelClick()));
}

delWindow::~delWindow()
{
    delete ui;
}

void delWindow::onDelClick(){
    QString plate = ui->plate->text();
    QString size = ui->size->currentText();
    QSqlTableModel * model = database::queryWithCondition(plate,size);
    QTableView *view = new QTableView;
    QMessageBox msgBox;
    if(model->rowCount()==0){
        msgBox.setText("没有这条记录!");
        msgBox.exec();
        return;
    }else if(model->rowCount()>1){
        msgBox.setText("具有多条记录,请小心操作!");
        msgBox.exec();
    }
    view->setModel(model);
    view->show();
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Question"),
                                                  tr("是否删除这条记录?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes)) {
        database::delWithCondition(plate);
        msgBox.setText("删除成功");
        msgBox.exec();
    }
}
