#ifndef SYNC_H
#define SYNC_H
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QProgressDialog>
#endif // SYNC_H
class sync{
public:
    int n;
    void syncfun(QString name,int time,int size,QSqlQuery sql_query,int count,QProgressDialog* dialog);
};
