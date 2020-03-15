#include<QFileInfo>
#include<QQueue>
#include<QDir>
#include<QtDebug>
#include "sync.h"
#include<QDateTime>
#include "mainwindow.h"
void back_up:: BfsCollectFiles(const QString& filepath,QString *display,int count,QString *path2,QSqlQuery sql_query,
                               QStringList namefile,QStringList namedir,QProgressDialog *dialog)  {   // bfs traverse
    QString paths = filepath;
    QFileInfo cur_fileinfo(filepath);
    sync dbinfo;
    QQueue<QFileInfo> fileinfo_queue;    // queue
    QDir cur_dir(filepath);
    cur_dir.setFilter(QDir::Hidden | QDir::Dirs | QDir::Files | QDir::NoSymLinks);
    QStringList test = namefile;
    QStringList dir_test = namedir;
    fileinfo_queue.enqueue(cur_fileinfo);
    while (!fileinfo_queue.isEmpty()) {
        cur_dir = fileinfo_queue.head().absoluteFilePath();
        //cur_dir.setNameFilters(filters);//guo lv qi de she zhi
        fileinfo_queue.dequeue();
        QFileInfoList cur_fileinfolist = cur_dir.entryInfoList();//QDir::Hidden

        QFileInfoList::const_iterator it;
        for (it = cur_fileinfolist.cbegin(); it != cur_fileinfolist.cend(); ++it) {
//            qDebug()<<it->fileName();
            if (it->isDir() && it->fileName() != "." && it->fileName() != "..") {    // jump "." and ".."
                int i = 0;
                //Files logical
                for(i = 0; i < dir_test.length(); i ++) {
                    //                    qDebug() << test.at(i);
                    QRegExp rx3(dir_test.at(i));
                    rx3.setPatternSyntax(QRegExp::Wildcard);
                    if(rx3.exactMatch(it -> filePath().mid(filepath.length() + 1, it -> absolutePath().length())) == true)
                    {
                        break;
                    }
                }
                if(i >= dir_test.length()) {
                    fileinfo_queue.enqueue(it->absoluteFilePath()); // enqueue unresolved directories
//                    display->append(it->absoluteFilePath() + '\n');
                    dialog->setValue(0);
                    dialog->setLabelText(it->absoluteFilePath().remove(paths));
                    dbinfo.syncfun(it->absoluteFilePath().remove(paths),0,it -> size(),sql_query,count,dialog);
                    dialog->setValue(99);
                    QCoreApplication::processEvents();
                    if(dialog->wasCanceled()) return;
                }
            } else if (!it->isDir()){
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
                    int modify_time = it->lastModified().toTime_t();
//                    display->append(it->absoluteFilePath() + '\n');
                    dialog->setValue(0);
                    dialog->setLabelText(it->absoluteFilePath().remove(paths));
                    dbinfo.syncfun(it->absoluteFilePath().remove(paths),modify_time,it -> size(),sql_query,count,dialog);
                    dialog->setValue(99);
                    QCoreApplication::processEvents();
                    if(dialog->wasCanceled()) return;
                }
            }
        }
    }
    QString flag1,flag2;
    if (count == 1) {
        flag1 = "yes";
        flag2 = "no";
    }
    else {
        flag1 = "no";
        flag2 = "yes";
    }
    QSqlQuery sql_query2 = sql_query;
    sql_query.prepare("select * from fileinfo where comp = ?");
    sql_query.bindValue(0,flag2);
    sql_query.exec();
    while (sql_query.next()) {
        QString name_1 = sql_query.value(0).toString();
        int status_1 = sql_query.value(1).toInt();
//        qDebug()<<name_1<<flag2<<status_1<<sql_query.value(3).toString();
//        int source_1 = sql_query.value(1).toInt();
        if (status_1 != -1 && status_1 != 0) {//notice
//            qDebug()<<name_1<<flag2<<count;
            if (status_1 == 1) {//modify and delete =>add
                int timeend = sql_query.value(5).toInt();
                sql_query2.prepare("update fileinfo set status = ?,time = ?, source = ?, size = 0 where name = ?");
                sql_query2.bindValue(0,0);
                sql_query2.bindValue(1,timeend);
                sql_query2.bindValue(2,1);
                sql_query2.bindValue(3,name_1);
                sql_query2.exec();
            }
            else {
                sql_query2.prepare("update fileinfo set status = ?, source = ? where name = ?");
                sql_query2.bindValue(0,-1);
                sql_query2.bindValue(1,count);
                sql_query2.bindValue(2,name_1);
                sql_query2.exec();
            }
        }
        else if (status_1 == -1){
            sql_query2.prepare("delete from fileinfo where name = ?");
            sql_query2.bindValue(0,name_1);
            sql_query2.exec();
        }
    }
    sql_query.prepare("update fileinfo set comp = ? where comp = ?");
    sql_query.bindValue(0,flag1);
    sql_query.bindValue(1,flag2);
    sql_query.exec();
//    execlute exec_1;
//    if (count == 2) {
//        exec_1.exec(sql_query,&paths,path2);
//    }
//    db.close();
}
