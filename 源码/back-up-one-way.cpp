#include "back-up-one-way.h"
#include<QFileInfo>
#include<QQueue>
#include<QDir>
#include<QtDebug>
#include<QDateTime>
void one_way::oneway(QString name,QSqlQuery sql_query,QString path1,QStringList namefile,QStringList namedir,int count,QProgressDialog *dialog) {
    QStringList test = namefile;
    QStringList dir_test = namedir;
    QFileInfo cur_fileinfo(path1);
    QQueue<QFileInfo> fileinfo_queue;
    QDir cur_dir(path1);
    cur_dir.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks);
    fileinfo_queue.enqueue(cur_fileinfo);
    while (!fileinfo_queue.isEmpty()) {
        cur_dir = fileinfo_queue.head().absoluteFilePath();
        //cur_dir.setNameFilters(filters);//guo lv qi de she zhi
        fileinfo_queue.dequeue();
        QFileInfoList cur_fileinfolist = cur_dir.entryInfoList();

        QFileInfoList::const_iterator it;

        for (it = cur_fileinfolist.cbegin(); it != cur_fileinfolist.cend(); ++it) {
            if (it->isDir() && it->fileName() != "." && it->fileName() != "..") {    // jump "." and ".."
                int i = 0;
                //Files logical
                for(i = 0; i < dir_test.length(); i ++) {
                    //                    qDebug() << test.at(i);
                    QRegExp rx3(dir_test.at(i));
                    rx3.setPatternSyntax(QRegExp::Wildcard);
                    if(rx3.exactMatch(it -> filePath().mid(path1.length() + 1, it -> absolutePath().length())) == true)
                    {
                        break;
                    }
                }
                if(i >= dir_test.length()) {
                    dialog->setValue(0);
                    dialog->setLabelText(it->absoluteFilePath().remove(path1));
                    fileinfo_queue.enqueue(it->absoluteFilePath()); // enqueue unresolved directories
                    dialog->setValue(20);
                    if (count == 1) {
                       dialog->setValue(50);
                       QString add = QString("insert into '%1' "
                                             "values"
                                             "(?,?)").arg(name);
                        sql_query.prepare(add);
//                        sql_query.bindValue(0,name);
                        sql_query.bindValue(0,it->filePath().remove(path1));
                        sql_query.bindValue(1,it->lastModified().toTime_t());
                        sql_query.exec();
                        dialog->setValue(90);
                    }
                    else {
                        QString add = QString("select * from '%1' where name = ?").arg(name);
//                        QSqlQuery sql_query2 = sql_query;
                        sql_query.prepare(add);
//                        sql_query.bindValue(0,name);
                        sql_query.bindValue(0,it->absoluteFilePath().remove(path1));
                        sql_query.exec();
                        int initialPos = sql_query.at();
                        int pos = 0;
                        if (sql_query.last()){
                            pos = sql_query.at() + 1;
                        }else{
                            pos = 0;
                        }
                        sql_query.seek(initialPos);
                        if (pos >= 1) {
                            while (sql_query.next()) {
                                QString name_1 = sql_query.value(0).toString();
                                uint time = sql_query.value(1).toInt();
                                if (it->lastModified().toTime_t() != time) {
                                    dialog->setValue(50);
//                                    qDebug()<<name_1;
                                    QSqlQuery sql_query2 = sql_query;
                                    QString add = QString("update '%1' set time = -2 where name = ?").arg(name);
                                    sql_query2.prepare(add);
//                                    sql_query2.bindValue(0,name);
                                    sql_query2.bindValue(0,name_1);
                                    sql_query2.exec();
                                    dialog->setValue(90);
                                }
                                else {
                                    dialog->setValue(50);
//                                    qDebug()<<name_1;
                                    QSqlQuery sql_query2 = sql_query;
                                    QString add = QString("update '%1' set time = 0 where name = ?").arg(name);
                                    sql_query2.prepare(add);
                                    sql_query2.bindValue(0,name_1);
                                    sql_query2.exec();
                                    dialog->setValue(90);
                                }
                            }
                        }
                        else {
                            dialog->setValue(50);
                            QString add = QString("insert into '%1' values(?,?)").arg(name);
                            sql_query.prepare(add);
                            sql_query.bindValue(0,it->filePath().remove(path1));
                            sql_query.bindValue(1,-1);
                            sql_query.exec();
                            dialog->setValue(90);
                        }
                    }
                }
                dialog->setValue(99);
                QCoreApplication::processEvents();
                if(dialog->wasCanceled()) return;
            } else if (!it->isDir()){
                dialog->setValue(0);
                dialog->setLabelText(it->absoluteFilePath().remove(path1));
                int i = 0;
                //Files logical
                for(i = 0; i < test.length(); i ++)
                {
                    QRegExp rx3(test.at(i));
                    rx3.setPatternSyntax(QRegExp::Wildcard);
                    if(rx3.exactMatch(it -> fileName()) == true)
                    {
                        break;
                    }
                }
                if(i >= test.length())
                {
                    dialog->setValue(20);
//                    int modify_time = it->lastModified().toTime_t();
                    if (count == 1) {
                        dialog->setValue(50);
                       QString add = QString("insert into '%1' "
                                             "values"
                                             "(?,?)").arg(name);
                        sql_query.prepare(add);
//                        sql_query.bindValue(0,name);
                        sql_query.bindValue(0,it->filePath().remove(path1));
                        sql_query.bindValue(1,it->lastModified().toTime_t());
                        sql_query.exec();
                        dialog->setValue(90);
                    }
                    else {
                        QString add = QString("select * from '%1' where name = ?").arg(name);
//                        QSqlQuery sql_query2 = sql_query;
                        sql_query.prepare(add);
//                        sql_query.bindValue(0,name);
                        sql_query.bindValue(0,it->absoluteFilePath().remove(path1));
                        sql_query.exec();
                        int initialPos = sql_query.at();
                        int pos = 0;
                        if (sql_query.last()){
                            pos = sql_query.at() + 1;
                        }else{
                            pos = 0;
                        }
                        sql_query.seek(initialPos);
                        if (pos >= 1) {
                            while (sql_query.next()) {
                                QString name_1 = sql_query.value(0).toString();
                                uint time = sql_query.value(1).toInt();
                                if (it->lastModified().toTime_t() != time) {
                                    dialog->setValue(50);
                                    qDebug()<<name_1;
                                    QSqlQuery sql_query2 = sql_query;
                                    QString add = QString("update '%1' set time = -2 where name = ?").arg(name);
                                    sql_query2.prepare(add);
//                                    sql_query2.bindValue(0,name);
                                    sql_query2.bindValue(0,name_1);
                                    sql_query2.exec();
                                    dialog->setValue(90);
                                }
                                else {
                                    dialog->setValue(50);
//                                    qDebug()<<name_1;
                                    QSqlQuery sql_query2 = sql_query;
                                    QString add = QString("update '%1' set time = 0 where name = ?").arg(name);
                                    sql_query2.prepare(add);
                                    sql_query2.bindValue(0,name_1);
                                    sql_query2.exec();
                                    dialog->setValue(90);
                                }
                            }
                        }
                        else {
                            dialog->setValue(50);
                            QString add = QString("insert into '%1' values(?,?)").arg(name);
                            sql_query.prepare(add);
                            sql_query.bindValue(0,it->filePath().remove(path1));
                            sql_query.bindValue(1,-1);
                            sql_query.exec();
                            dialog->setValue(90);
                        }
                    }

                }
                dialog->setValue(99);
                QCoreApplication::processEvents();
                if(dialog->wasCanceled()) return;
            }
        }
    }
}
