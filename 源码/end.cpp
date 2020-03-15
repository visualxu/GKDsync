#include "end.h"
#include <QString>
void end_1::end(QSqlQuery sql_query,QString name) {
//    sql_query.exec("select * from fileinfo where status = -1");
//    while (sql_query.next()) {
//        QString name = sql_query.value(0).toString();
//        qDebug()<<name;
//    }
    sql_query.exec("delete from fileinfo where status = -1");
    sql_query.exec("update fileinfo set status = 9 where status != 9");
    sql_query.exec("update fileinfo set source = 0 where source !=0");
    sql_query.exec("update fileinfo set size = 0 where size !=0");
    QString drop = QString("drop table '%1'").arg(name);
    sql_query.exec(drop);
    QString add = QString("create table '%1' as select * from fileinfo").arg(name);
    sql_query.exec(add);
    sql_query.exec("drop table fileinfo");
}
