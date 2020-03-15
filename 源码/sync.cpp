#include "sync.h"
#include "exec.h"
#include "mainwindow.h"
void sync::syncfun(QString name,int time,int size,QSqlQuery sql_query,int count,QProgressDialog* dialog) {
    QString flag1,flag2;
    QSqlQuery sql_query1 = sql_query;
    dialog->setValue(20);///////////////////////////////
    if (count == 1) {
        flag1 = "yes";
        flag2 = "no";
    }
    else {
        flag1 = "no";
        flag2 = "yes";
    }
    sql_query.prepare("SELECT * FROM fileinfo WHERE name =?");
    sql_query.bindValue(0,name);
    sql_query.exec();
    int initialPos = sql_query.at();
    int pos = 0;
    if (sql_query.last()){
        pos = sql_query.at() + 1;
    }else{
        pos = 0;
    }
    sql_query.seek(initialPos);
    dialog->setValue(50);
    if (pos < 1) {//add
        dialog->setValue(60);
        sql_query.prepare("insert into fileinfo "
                          "values"
                          "(?,?,?,?,?,?)");
        sql_query.bindValue(0,name);
        sql_query.bindValue(1,0);
        sql_query.bindValue(2,time);
        sql_query.bindValue(3,count);
        sql_query.bindValue(4,flag1);
        sql_query.bindValue(5,0);
        sql_query.exec();
        dialog->setValue(90);
    }
    else {
        while (sql_query.next()) {//modify
            QString name_1 = sql_query.value(0).toString();
            int time_1 = sql_query.value(2).toInt();
            int status_1 = sql_query.value(1).toInt();
//            int source_1 = sql_query.value(3).toInt();
            int timeleft = sql_query.value(5).toInt();
            if (time == 0 && time_1 != 0 || time != 0 && time_1 == 0) {//file and category confilct
                sql_query1.prepare("update fileinfo set source = -2, comp = ? where name = ?");
                sql_query1.bindValue(0,flag1);
//                sql_query1.bindValue(1,0);
                sql_query1.bindValue(1,name_1);
                sql_query1.exec();
//                  qDebug()<<time<<time_1<<name_1;
            }
            else if (time != time_1 && status_1 == 1) {//file and file conflict
//                qDebug()<<"config";
                 dialog->setValue(60);
                if (time != timeleft) {
                    sql_query1.prepare("update fileinfo set source = -1, comp = ? ,time = ? where name = ?");
                    sql_query1.bindValue(0,flag1);
                    sql_query1.bindValue(1,time);
                    sql_query1.bindValue(2,name_1);
                    sql_query1.exec();
                }
                else {
                    sql_query1.prepare("update fileinfo set status = 9, source = 0, comp = ? ,time = ? where name = ?");
                    sql_query1.bindValue(0,flag1);
                    sql_query1.bindValue(1,time);
                    sql_query1.bindValue(2,name_1);
                    sql_query1.exec();
                }
            }
            else if (status_1 == 0) {//add file confilct if time not equal
                dialog->setValue(60);
                sql_query1.prepare("update fileinfo set status = ? ,source = ?, comp = ? ,time = ? where name = ?");
//                sql_query1.bindValue(1,flag1);
                if (time == 0) {
                    sql_query1.bindValue(0,9);
                    sql_query1.bindValue(1,0);
                    sql_query1.bindValue(2,flag1);
                    sql_query1.bindValue(3,0);
                }
                else {
                     if (time_1 != time) {
                         sql_query1.bindValue(0,1);
                         sql_query1.bindValue(1,-1);
                     }
                     else {
                         sql_query1.bindValue(0,9);
                         sql_query1.bindValue(1,0);
                     }
                    sql_query1.bindValue(2,flag1);
                    sql_query1.bindValue(3,time);
                }
//                sql_query1.bindValue(1,time);
                sql_query1.bindValue(4,name_1);
                sql_query1.exec();
            }
            else if (time_1 < time) {
                dialog->setValue(60);
//               qDebug()<<time_1<<time<<name_1<<status_1;
                if (count == 2) {
                    if (status_1 == -1) {//modify and delete =>add
                        qDebug()<<"cao";
                        sql_query1.prepare("update fileinfo set status = ? ,source = ?, time = ?, comp = ? where name = ?");
         //               sql_query.bindValue(0,time);
                        sql_query1.bindValue(0,0);
                        sql_query1.bindValue(1,count);
                        sql_query1.bindValue(2,time);
                        sql_query1.bindValue(3,flag1);
                        sql_query1.bindValue(4,name_1);
                        sql_query1.exec();
                    }
                    else {
                        sql_query1.prepare("update fileinfo set status = ? ,source = ?, time = ?, comp = ? where name = ?");
//                                    sql_query.bindValue(0,time);
                        sql_query1.bindValue(0,1);
                        sql_query1.bindValue(1,count);
                        sql_query1.bindValue(2,time);
                        sql_query1.bindValue(3,flag1);
                        sql_query1.bindValue(4,name_1);
                        sql_query1.exec();
                    }
                }
                else if (count == 1){
                    qDebug()<<name+"1";
                    sql_query1.prepare("update fileinfo set status = ? ,source = ? ,comp = ? ,size = ? where name = ?");
                    //               sql_query.bindValue(0,time);
                    sql_query1.bindValue(0,1);
                    sql_query1.bindValue(1,count);
                    sql_query1.bindValue(2,flag1);
                    sql_query1.bindValue(3,time);
                    sql_query1.bindValue(4,name_1);
                    //               sql_query.bindValue(5,name_1);
                    sql_query1.exec();
                }
                dialog->setValue(90);
            }
            else if (timeleft > time ) {//left modify right no
                dialog->setValue(60);
                qDebug()<<name_1<<count<<status_1;
                sql_query1.prepare("update fileinfo set comp = ?, time = ?, size = ? where name = ?");
                sql_query1.bindValue(0,flag1);
                sql_query1.bindValue(1,timeleft);
                sql_query1.bindValue(2,0);
                sql_query1.bindValue(3,name_1);
                sql_query1.exec();
                dialog->setValue(90);
            }
            else if (time == time_1) {
                dialog->setValue(60);
//                qDebug()<<name_1<<count<<status_1;
                int sta;
                int sou;
                if (status_1 != -1) {
                    sta = 9;
                    sou = 0;
                }
                else {
                    sta = -1;
                    sou = 1;
                }
                sql_query1.prepare("update fileinfo set status = ?, source = ?, comp = ? where name = ? ");
                sql_query1.bindValue(0,sta);
                sql_query1.bindValue(1,sou);
                sql_query1.bindValue(2,flag1);
                sql_query1.bindValue(3,name_1);
                sql_query1.exec();
                dialog->setValue(90);
            }
        }
    }
}
