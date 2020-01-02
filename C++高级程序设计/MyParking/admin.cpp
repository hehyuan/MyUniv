#include "admin.h"
#include "ui_admin.h"


admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    setWindowTitle("管理员管理界面");
    connect(ui->returnBtn,SIGNAL(clicked()),this,SLOT(onReturnClicked()));
    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(onExitClicked()));
    connect(ui->addCarBtn,SIGNAL(clicked()),this,SLOT(onAddCarClicked()));
    connect(ui->delBtn,SIGNAL(clicked()),this,SLOT(onDelCarClicked()));
    connect(ui->countBtn,SIGNAL(clicked()),this,SLOT(onCountClicked()));
    connect(ui->queryAllBtn,SIGNAL(clicked()),this,SLOT(onQueryAllClicked()));
    connect(ui->queryCarBtn,SIGNAL(clicked()),this,SLOT(onQueryClicked()));
    connect(ui->reserveBtn,SIGNAL(clicked()),this,SLOT(onReserveClicked()));
}

admin::~admin()
{
    delete ui;
}
void admin:: onReturnClicked(){
    MainWindow*  window = new MainWindow();
    window->show();
    this->close();
};
void admin::onAddCarClicked(){
    addCar * ac = new addCar();
    ac->show();
};
void admin::onDelCarClicked(){
    delWindow *dw = new delWindow();
    dw->show();
};
void admin::onEditClicked(){};
void admin:: onCountClicked(){
    countAll * ca = new countAll();
    ca->show();
};
void admin:: onQueryClicked(){
    queryWindow *qw = new queryWindow();
    qw->show();
};
void admin:: onReserveClicked(){
    reserveCar * rc = new reserveCar();
    rc->show();
};
void admin:: onQueryAllClicked(){
    QSqlTableModel * model = database::edit();
    QTableView *view = new QTableView;
            view->setModel(model);
//            view->setSelectionMode(QAbstractItemView::SingleSelection);
//            view->setSelectionBehavior(QAbstractItemView::SelectRows);
//            view->setColumnHidden(0, true);
//            view->resizeColumnsToContents();
//            QHeaderView *header = view->horizontalHeader();
//            header->setStretchLastSection(true);
            view->setWindowTitle("所有车辆记录");
            view->show();
};

void admin::onExitClicked(){
    this->close();
}
