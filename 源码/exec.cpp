#include "exec.h"
#include "end.h"
#include "mainwindow.h"
#include <QFile>
#include <sys/types.h>
#include <utime.h>
#include <QTextCodec>
void execlute::exec(QSqlQuery sql_query,QString *path2,QString *path1, QProgressDialog *dialog) {
    QFileInfo tmp_file("./share_dir");
    int c = 0;
    if(tmp_file.absoluteFilePath() == (*path1).mid(0,tmp_file.absoluteFilePath().length()))
    {
        qDebug()<<*path1;
        c = 1;
    }
    int count = 0;
    QSqlQuery sql_query1 = sql_query;
    QFile file("./log.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug()<<file.errorString();
    }
    QDir dir;
    QString d;
    sql_query.prepare("select * from fileinfo where status = ?");//add
    sql_query.bindValue(0,0);
    sql_query.exec();
    while (sql_query.next()) {
        QString name = sql_query.value(0).toString();
        int source = sql_query.value(3).toInt();
        int time = sql_query.value(2).toInt();
        QDateTime dtime = QDateTime::fromTime_t(time);
        if (source == 1) {
            QFileInfo fi = (*path1+name);
            if (time == 0) {
                if (!dir.exists(*path2+name)) {
                    dir.mkpath(*path2+name);
                }
            }
            else {
//                QFileInfo fi = (*path1+name);
                utimbuf timekkk;
                timekkk.modtime = time;
                QFile::copy(fi.absoluteFilePath(),*path2+name);
                QByteArray s = (*path2+name).toUtf8();
                char *filename;
                filename = s.data();
                utime(filename,&timekkk);
                sql_query1.prepare("update fileinfo set time = ? where name = ?");
                sql_query1.bindValue(0,fi.lastModified().toTime_t());
                sql_query1.bindValue(1,name);
                sql_query1.exec();

            }
            file.write("右边新增 "+name.toUtf8()+"时间:"+fi.lastModified().toString().toUtf8()+'\n');
        }
        else if (source == 2){
            QFileInfo fi = (*path2+name);
            if (time == 0) {
                if (!dir.exists(*path1+name)) {
                    dir.mkpath(*path1+name);
                }
            }
            else {
//                QFileInfo fi = (*path2+name);
                utimbuf timekkk;
                timekkk.modtime = time;
                QFile::copy(fi.absoluteFilePath(),*path1+name);
                QByteArray s = (*path1+name).toUtf8();
                char *filename;
                filename = s.data();
                utime(filename,&timekkk);
                sql_query1.prepare("update fileinfo set time = ? where name = ?");
                sql_query1.bindValue(0,fi.lastModified().toTime_t());
                sql_query1.bindValue(1,name);
                sql_query1.exec();
                if (c == 1) {
                    QFileInfo file1(*path1+name);
                    utimbuf buf;
                    buf.modtime = file1.lastModified().toTime_t();
                    QByteArray s = (path2+name).toUtf8();
                    char *filename;
                    filename = s.data();
                    utime(filename,&buf);
                    sql_query1.prepare("update fileinfo set time = ? where name = ?");
                    sql_query1.bindValue(0,file1.lastModified().toTime_t());
                    sql_query1.bindValue(1,name);
                    sql_query1.exec();
                }
            }
             file.write("左边新增 "+name.toUtf8()+"时间:"+fi.lastModified().toString().toUtf8()+'\n');
        }
        count++;
        dialog->setValue(count);
        QCoreApplication::processEvents();
        QCoreApplication::processEvents();
        if(dialog->wasCanceled()) return;
    }
    sql_query.prepare("select * from fileinfo where status = ?");//delete
    sql_query.bindValue(0,-1);
    sql_query.exec();
    while (sql_query.next()) {
        QString name_1 = sql_query.value(0).toString();
        int source = sql_query.value(3).toInt();
        int time = sql_query.value(2).toInt();
        if (source == 1) {
            QFileInfo fi(*path2+name_1);
            if (time == 0) {
                if (dir.exists(*path2+name_1)){
                    QString rdpath = *path2+name_1;
                    rmd rmd1;
                    rmd1.rmd_1(&rdpath);
                }
            }
            else {
//                QFileInfo fi(*path2+name_1);
                QFile::remove(fi.absoluteFilePath());
            }
           file.write("右边删除 "+name_1.toUtf8()+"最后修改时间:"+fi.lastModified().toString().toUtf8()+'\n');
        }
        if (source == 2) {
             QFileInfo fi(*path1+name_1);
              file.write("左边删除 "+name_1.toUtf8()+"最后修改时间:"+fi.lastModified().toString().toUtf8()+'\n');
            if (time == 0) {
                if (dir.exists(*path1+name_1)) {
//                dir.rmpath(*path1+name_1);
                    QString rdpath = *path1+name_1;
                    rmd rmd1;
                    rmd1.rmd_1(&rdpath);
                }
            }
//            if(!file
            else {
//                QFileInfo fi(*path1+name_1);
                QFile::remove(fi.absoluteFilePath());
            }
//            file.write("左边删除 "+name_1.toUtf8()+"时间:"+fi.lastModified().toString().toUtf8()+'\n');
        }
        count ++;
        dialog->setValue(count);
        QCoreApplication::processEvents();
        QCoreApplication::processEvents();
        if(dialog->wasCanceled()) return;
    }
    sql_query.prepare("select * from fileinfo where status = ?");//modify
    sql_query.bindValue(0,1);
    sql_query.exec();
//    QSqlQuery sql_query1 = sql_query;
    while (sql_query.next()) {
        QString name = sql_query.value(0).toString();
//        qDebug()<<name<<"modfify";
        int time = sql_query.value(2).toInt();
        int source = sql_query.value(3).toInt();
        if (time != 0) {
            if (source == 1) {
                QFileInfo fi = (*path1+name);
                QFileInfo fi1 = (*path2+name);
                QFile::remove(fi1.absoluteFilePath());
                QFile::copy(fi.absoluteFilePath(),*path2+name);
                utimbuf timekkk;
                timekkk.modtime = fi.lastModified().toTime_t();
                QByteArray s = (*path2+name).toUtf8();
                char *filename;
                filename = s.data();
                utime(filename,&timekkk);
                file.write("右边修改 "+name.toUtf8()+"时间:"+fi.lastModified().toString().toUtf8()+'\n');
                sql_query1.prepare("update fileinfo set time = ? where name = ?");
                sql_query1.bindValue(0,fi.lastModified().toTime_t());
                sql_query1.bindValue(1,name);
                sql_query1.exec();
            }
            else {
                QFileInfo fi = (*path1+name);
                QFileInfo fi1 = (*path2+name);
                QFile::remove(fi.absoluteFilePath());
                QFile::copy(fi1.absoluteFilePath(),*path1+name);
                utimbuf timekkk;
                timekkk.modtime = fi1.lastModified().toTime_t();
                QByteArray s = (*path1+name).toUtf8();
                char *filename;
                filename = s.data();
                utime(filename,&timekkk);
                file.write("左边修改 "+name.toUtf8()+"时间:"+fi1.lastModified().toString().toUtf8()+'\n');
                sql_query1.prepare("update fileinfo set time = ? where name = ?");
                sql_query1.bindValue(0,fi1.lastModified().toTime_t());
                sql_query1.bindValue(1,name);
                sql_query1.exec();
                if (c == 1) {
                    QFileInfo file1(*path1+name);
                    utimbuf buf;
                    buf.modtime = file1.lastModified().toTime_t();
                    QByteArray s = (*path2+name).toUtf8();
                    char *filename;
                    filename = s.data();
                    utime(filename,&buf);
                    sql_query1.prepare("update fileinfo set time = ? where name = ?");
                    sql_query1.bindValue(0,file1.lastModified().toTime_t());
                    sql_query1.bindValue(1,name);
                    sql_query1.exec();
                }
            }
        }
        count ++;
        dialog->setValue(count);
        QCoreApplication::processEvents();
        if(dialog->wasCanceled()) return;
    }
}
