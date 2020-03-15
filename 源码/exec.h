#include <QtSql>
#include "rmdir.h"
#include <QProgressDialog>
#include <QProgressDialog>
#ifndef EXEC_H
class execlute {
public:
    void exec(QSqlQuery sql_query,QString *path1,QString *path2,QProgressDialog* dialog);
    void owexec(QSqlQuery sql_query,QString path1,QString path2,QString name,int a,QProgressDialog *dialog);
};
#define EXEC_H
#endif // EXEC_H

