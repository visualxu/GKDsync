#ifndef BACKUP_H
#define BACKUP_H
#include <QString>
#include <QtSql>
#include <QProgressDialog>
#endif // BACKUP_H
class back_up{
public:
    void BfsCollectFiles(const QString& filepath,QString *display,int count,QString *path2,QSqlQuery sql_query,
                         QStringList namedir,QStringList namefile,QProgressDialog *dialog);
};
