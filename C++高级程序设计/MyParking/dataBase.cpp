#include "database.h"

#include <QSqlQuery>
#include <string>
#include <QDebug>
#include <QSqlError>
using namespace std;
database::database()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("127.0.0.1"); //数据库服务器IP
    this->db.setHostName("localhost");
    this->db.setDatabaseName("parking");
    this->db.setUserName("root");
    this->db.setPassword("hhy123456");
    bool conn = this->db.open();
    if (!conn)
    {
        QMessageBox msgBox;
        msgBox.setText("Connect Sql error!");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Success!");
        msgBox.exec();
    }
}

database::~database()
{
    this->db.close();
}

void database::init()
{ //对数据库初始化
    QString sql;
    QSqlQuery qry;
    // 创建 表parking 用于记录停车位的状态
    sql = "CREATE TABLE IF NOT EXISTS `parking` ( `id` int(11) NOT NULL,`status` varchar(45) NOT NULL,              `type` int4 NOT NULL,              `row` int(11) NOT NULL,              `col` int(11) NOT NULL) ENGINE=InnoDB AUTO_INCREMENT=39 DEFAULT CHARSET=latin1;";
    qry.prepare(sql);
    qry.exec();
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            int cnt = 10 * (i - 1) + j;
            QString sql = "INSERT INTO `parking` (`id`, `status`, `type`, `row`,`col`) VALUES(" +
                          QString::number(cnt) + "," + " 'free'" + "," + QString::number(cnt % 4) + "," + QString::number(i) + "," + QString::number(j) + ")";
            qry.prepare(sql);
            if (!qry.exec())
            {
                qDebug() << qry.lastError();
            }
        }
    }
    //创建 表records 用于记录车辆的位置
    sql = "CREATE TABLE IF NOT EXISTS `records` (`plate` varchar(255) CHARACTER SET utf8 NOT NULL,`size` varchar(105) CHARACTER SET utf8 NOT NULL,  `place_id` int(11) NOT NULL,  `in_time` datetime NOT NULL,  `is_out` int(1) NOT NULL default(0)) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=latin1;";
    qry.prepare(sql);
    if (!qry.exec())
    {
        qDebug() << qry.lastError();
    }
}

QString database::queryEmptyPos(int flag)
{
    QSqlQuery qry;
    QString sql = "SELECT * FROM `parking` WHERE `status` = 'free' and `type` = '" + QString::number(flag) + " ' LIMIT 1";
    qry.prepare(sql);
    if (!qry.exec())
    {
        qDebug() << qry.lastError();
        return "DB ERROR";
    }
    else
    {
        while (qry.next())
        {
            return qry.value(0).toString();
        }
        return "false";
    }
}
QStringList database::queryAllPos(int flag){
    QStringList list;
    QSqlQuery qry;
    QString sql = "SELECT `row`,`col` FROM `parking` WHERE `type` = '" + QString::number(flag) + " ' ";
    qry.prepare(sql);
    if (!qry.exec())
        qDebug() << qry.lastError();
        while (qry.next())
        {
            list.append("("+qry.value(0).toString()+","+qry.value(1).toString()+")");
        }
        return list;
 };
QStringList database::queryVipEmptyPos(int flag){
    QStringList list;
    QSqlQuery qry;
    QString sql = "SELECT `row`,`col` FROM `parking` WHERE (`status` = 'free' or `status` =  'reserved') and `type` = '" + QString::number(flag) + " ' ";
    qry.prepare(sql);
    if (!qry.exec())
        qDebug() << qry.lastError();
        while (qry.next())
        {
            list.append("("+qry.value(0).toString()+","+qry.value(1).toString()+")");
        }
        return list;
};
QStringList database::queryAllEmptyPos(int flag)
{
    QStringList list;
    QSqlQuery qry;
    QString sql = "SELECT `row`,`col` FROM `parking` WHERE `status` = 'free' and `type` = '" + QString::number(flag) + " ' ";
    qry.prepare(sql);
    if (!qry.exec())
        qDebug() << qry.lastError();
        while (qry.next())
        {
            list.append("("+qry.value(0).toString()+","+qry.value(1).toString()+")");
        }
        return list;
    };

    QString database::queryPos(QString plate)
    {
        QSqlQuery qry;
        //在记录中寻找进入该停车场的车的记录，并且还没离开停车场
        QString sql = "SELECT `place_id` FROM `records` WHERE  `is_out` = 0  and `plate` = '" + (plate) + "';";
        qry.prepare(sql);
        if (!qry.exec())
        {
            qDebug() << qry.lastError();
            return "DB ERROR";
        }
        else
        {
            while (qry.next())
            {
                return qry.value(0).toString();
            }
            return "false";
        }
    }

    QSqlTableModel *database::queryAll()
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("records");
        model->setFilter("is_out = 0");
        model->select();
        return model;
    }

    QSqlTableModel *database::edit()
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("records");
        model->setFilter("is_out = 0");
        model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        return model;
    }

    QSqlTableModel *database::queryWithCondition(QString plate, QString size)
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("records");
        if (plate.length() != 7)
        { //车牌无效
            model->setFilter("size = '" + size + "'");
        }
        else
        {
            model->setFilter("plate = '" + plate + "' and size = '" + size + "'");
        }
        model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        return model;
    }

    bool database::delWithCondition(QString plate)
    {
        QSqlQuery qry;
        //在记录中寻找进入该停车场的车的记录，并且还没离开停车场
        QString sql_s = "SELECT `place_id` FROM `records` WHERE plate ='" + (plate) + "';";
        qry.prepare(sql_s);
        if (!qry.exec())
        {
            return false;
        }
        QString pos;
        if(qry.next())
            pos = qry.value(0).toString();
        QString sql = "DELETE  FROM `records` WHERE   plate = '" + (plate) + "';";
        qry.prepare(sql);
        if (!qry.exec())
        {
            return false;
        }
        sql = "UPDATE `parking` SET `status` = `free` WHERE id = '"+pos+"'";
        qry.prepare(sql);
        if (!qry.exec())
        {
            return false;
        }
        return true;
    };

    void database::updateParking(QString pos, QString status){
        QSqlQuery qry;
        QString  sql_up = "UPDATE `parking` SET `status` = '"+status+"' WHERE id = '"+pos+"'";
        qry.prepare(sql_up);
        if (!qry.exec())
        {
            qDebug() << qry.lastError();
            return;
        }
    }

    void database::insertRecords(QString plate, QString size, QString pos, QString inTime){
        QSqlQuery qry;
        QString sql = "INSERT INTO `records` (`place_id`, `plate`, `in_time`,`size`) VALUES('"+
                pos+"','"+plate+"','"+inTime+"','"+size+"')";
        qry.prepare(sql);
        if (!qry.exec())
        {
            qDebug() << qry.lastError();
            return;
        }
    }
