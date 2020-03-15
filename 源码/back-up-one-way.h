#ifndef BACKUPONEWAY_H
#define BACKUPONEWAY_H
#endif // BACKUPONEWAY_H
#include <QString>
#include <QProgressDialog>
#include <QtSql>
class one_way {
public:
    void oneway(QString name,QSqlQuery sql_query,QString path1,QStringList namefile,QStringList namedir,int count,QProgressDialog *dialog);
};
