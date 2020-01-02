#ifndef DATABASE_H
#define DATABASE_H
#include<Car.h>
#include <QMessageBox>
#include <qsqldatabase.h>
#include<QString>
#include<QSqlTableModel>
#include <QTableView>
class database
{
public:
    database();
    ~database();
    void init();
   static QString queryEmptyPos(int flag);
   static QString queryPos(QString plate);
   static QSqlTableModel * queryAll();
   static QSqlTableModel * edit();
   static QSqlTableModel * queryWithCondition(QString plate,QString size);
   static bool delWithCondition(QString plate);
   static QStringList queryAllPos(int flag);
   static QStringList queryAllEmptyPos(int flag);
   static QStringList queryVipEmptyPos(int flag);
   static void insertRecords(QString plate,QString size,QString place_id,QString inTime);
   static void updateParking(QString pos,QString status);
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
