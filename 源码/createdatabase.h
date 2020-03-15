#ifndef CREATEDATABASE_H
#define CREATEDATABASE_H
#include <QtSql>
#endif // CREATEDATABASE_H
class database{
public:
    QSqlQuery create(QSqlDatabase db,int a,QString path1,QString path2);
};
