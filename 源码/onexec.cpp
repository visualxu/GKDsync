#include"exec.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include "rmdir.h"
#include <utime.h>
void execlute::owexec(QSqlQuery sql_query, QString path1, QString path2,QString name,int a,QProgressDialog *dialog) {

    QFileInfo tmp_file("./share_dir");
    int c = 0;
    if(tmp_file.absoluteFilePath() == path2.mid(0,tmp_file.absoluteFilePath().length()))
    {
        qDebug()<<path1;
        c = 1;
    }
    qDebug()<<path2.mid(0,tmp_file.absoluteFilePath().length());
    QFile file("./log.txt");
    QString b;
    int count = 0;
    if (a == 0) {
        b = "右边";
    }
    else if (a == 1) {
        b= "左边";
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
         qDebug()<<file.errorString();
    }
    QString add = QString("select * from '%1' where time = -1").arg(name);
    sql_query.exec(add);
    while (sql_query.next()) {//delete
        QString name1 = sql_query.value(0).toString();
        QFileInfo fi(path2+name1);
        if  (fi.isFile()) {
            if (fi.exists()) {
                QFile::remove(path2+name1);
            }
        }
        else {
            if (fi.exists()) {
                rmd rmd1;
                QString path = path2+name1;
                rmd1.rmd_1(&path);
            }
        }
        file.write(b.toUtf8()+"删除"+name1.toUtf8()+"时间:"+fi.lastModified().toString().toUtf8()+'\n');
        count ++;
        dialog->setValue(count);
        QCoreApplication::processEvents();
        if(dialog->wasCanceled()) return;
    }
    QString add_1 = QString("select * from '%1' where time = -2").arg(name);
    sql_query.exec(add_1);
    while (sql_query.next()) {//modify
        QString name2 = sql_query.value(0).toString();
//        int time = sql_query.value(1).toInt();
        QFileInfo fi(path2+name2);
        QFileInfo fi1(path1+name2);
        if  (fi.isFile()) {
            if (fi.exists()) {
                QFile::remove(path2+name2);
                QFile::copy(path1+name2,path2+name2);
                utimbuf buf;
                buf.modtime = fi1.lastModified().toTime_t();
                QByteArray s = (path2+name2).toUtf8();
                char *filename;
                filename = s.data();
                utime(filename,&buf);
                if (c == 1) {
                    utimbuf buf;
                    buf.modtime = fi.lastModified().toTime_t();
                    QByteArray s = (path1+name2).toUtf8();
                    char *filename;
                    filename = s.data();
                    utime(filename,&buf);
                }
            }
        }
        file.write(b.toUtf8()+"修改"+name2.toUtf8()+"时间:"+fi.lastModified().toString().toUtf8()+'\n');
        count ++;
        dialog->setValue(count);
        QCoreApplication::processEvents();
        if(dialog->wasCanceled()) return;
    }
    QString add_2 = QString("select * from '%1' where time > 0").arg(name);
    sql_query.exec(add_2);
    while (sql_query.next()) {//add
        QString name3 = sql_query.value(0).toString();
        int time = sql_query.value(1).toInt();
        QFileInfo fi(path1+name3);
        if (fi.isFile()) {
            if (fi.exists()) {
//                QFile::remove(path2+name2);
                QFile::copy(path1+name3,path2+name3);
                utimbuf buf;
                buf.modtime = time;
                QByteArray s = (path2+name3).toUtf8();
                char *filename;
                filename = s.data();
                utime(filename,&buf);
                if (c == 1) {
                    QFileInfo fi1(path2+name3);
                    utimbuf buf;
                    buf.modtime = fi1.lastModified().toTime_t();
                    qDebug()<<fi1.lastModified().toString();
                    QByteArray s = (path1+name3).toUtf8();
                    char *filename;
                    filename = s.data();
                    utime(filename,&buf);
                }
            }
        }
        else {
            if (fi.exists()) {
//                rmd rmd1;
                QDir dir;
//                QString path = path2+name2;
//                rmd1.rmd_1(&path2);
                dir.mkpath(path2+name3);
                if (c == 1) {
                    QFileInfo fi1(path2+name3);
                    utimbuf buf;
                    buf.modtime = fi1.lastModified().toTime_t();
                    QByteArray s = (path1+name3).toUtf8();
                    char *filename;
                    filename = s.data();
                    utime(filename,&buf);
                }
            }
        }
        file.write(b.toUtf8()+"增加"+name3.toUtf8()+"时间:"+fi.lastModified().toString().toUtf8()+'\n');
        count ++;
        dialog->setValue(count);
        QCoreApplication::processEvents();
        if(dialog->wasCanceled()) return;
    }
    file.close();
    QString drop = QString("drop table '%1'").arg(name);
    if(!sql_query.exec(drop))
    {
        qDebug()<<sql_query.lastError();
    }
}
