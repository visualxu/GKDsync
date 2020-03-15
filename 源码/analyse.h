#ifndef ANALYSE_H
#define ANALYSE_H
#include <QtSql>
#include <ui_mainwindow.h>
#include <QTreeWidgetItem>
#include <QDateTime>
#endif // ANALYSE_H
class analyse {
public:
    void  analy(QSqlQuery sql_query,Ui::MainWindow *ui,QString path1,QString path2);
    void owanaly(QSqlQuery sql_query,Ui::MainWindow *ui,QString path1,QString path2,QString name,int a);
};
