#include "createdatabase.h"
QSqlQuery database::create(QSqlDatabase db,int a,QString path1,QString path2) {
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fileinfo.dat");
    if (!db.open()) {
       qDebug()<<"dfopen failed";
    }
    else {
        qDebug()<< "open";
    }
//    qDebug()<<name;
    QString name;
    QSqlQuery sql_query;
    if (a == 2) {
        sql_query.prepare("select * from sqlite_master where type = 'table' and name = ?");
        sql_query.bindValue(0,path1+path2);
        sql_query.exec();
        if (sql_query.next()) {
            name = path1+path2;
        }
        else {
            sql_query.prepare("select * from sqlite_master where type = 'table' and name = ?");
            sql_query.bindValue(0,path2+path1);
            sql_query.exec();
            if (sql_query.next()) {
                name = path2+path1;
            }
            else {
                name = path1+path2;
            }
        }
        QString add = QString("create table '%1' (name text primary key,status int,time int,source int,comp text,size int)").arg(name);
        if (!sql_query.exec(add)) {//create failed
            qDebug()<<"create table failed";
            QString add = QString("create table fileinfo as select * from '%1'").arg(name);
            if (!sql_query.exec(add)) {
                sql_query.exec("drop table fileinfo");
                sql_query.exec(add);
            }
        }//动态创建表
        else {
            qDebug()<<"create table failed";
            QString add = QString("create table fileinfo as select * from '%1'").arg(name);
            if (!sql_query.exec(add)) {
                sql_query.exec("drop table fileinfo");
                sql_query.exec(add);
            }
        }
    }
    else {
        if (!sql_query.exec("create table owfile (name text primary key,time int)")) {
            qDebug()<<"create table failed";
            sql_query.exec("drop table owfile");
            sql_query.exec("create table owfile (name text primary key,time int)");
        }
    }
    return sql_query;
}
