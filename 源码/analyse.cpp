#include "analyse.h"
#include <QFile>
#include <QPixmap>
void analyse::analy(QSqlQuery sql_query,Ui::MainWindow *Ui,QString path1,QString path2){
    int i = 1;
//    QFile file("/home/wangxu/1.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        qDebug()<<file.errorString();
//    }
    sql_query.exec("select * from fileinfo");
    QSqlQuery sql_query1 = sql_query;
    while (sql_query.next()) {
        QString name = sql_query.value(0).toString();
        int status = sql_query.value(1).toInt();
        int time = sql_query.value(2).toInt();
        int source = sql_query.value(3).toInt();
        QString comp = sql_query.value(4).toString();
//        int size = sql_query.value(5).toInt();
        if (status != 9) {
        QDateTime dtime = QDateTime::fromTime_t(time);
        QTreeWidgetItem *newltem = new QTreeWidgetItem();
        QString p = QString("%1").arg(i);
        QIcon qicon1 = QIcon(":/iconPicture/copy_to_right.png");
        QIcon qicon2 = QIcon(":/iconPicture/copy_to_left.png");
        QIcon qicon3 = QIcon(":/iconPicture/so_delete_left.png");
        QIcon qicon4 = QIcon(":/iconPicture/so_delete_right.png");
        QIcon qicon5 = QIcon(":/iconPicture/so_update_right_small.png");
        QIcon qicon6 = QIcon(":/iconPicture/so_update_left.png");
        QIcon qicon7 = QIcon(":/iconPicture/conflict.png");
        QIcon qicon8 = QIcon(":/iconPicture/msg_warning.png");
        QFileInfo file1(path1+name);
        QFileInfo file2(path2+name);
        QPixmap pixmap1(file1.isDir() ? ":/iconPicture/dir.png":":/iconPicture/file.png");
        QPixmap pixmap2(file2.isDir() ? ":/iconPicture/dir.png":":/iconPicture/file.png");
        if (source == 1) {
            if (status == 0) {
//                QFileInfo file1(path1+name);
//                QPixmap pixmap(file1.isDir() ? ":/iconPicture/dir.png":":/iconPicture/file.png");
                newltem->setText(0,p);
                newltem->setText(1,name);
                newltem->setIcon(1,pixmap1);
                newltem->setText(2,QString::number(file1.size()));
                newltem->setText(3,file1.lastModified().toString());
                newltem->setIcon(4,qicon1);
                if (file1.isDir()) {
                      newltem->setBackgroundColor(1, qRgb(177,177,177));
                }
                Ui->treeWidget->addTopLevelItem(newltem);
//                newltem->setText(7,name);
//                newltem->setText(8,);
//                newltem->setText(9,);
            }
            if (status == -1) {
//                QFileInfo file2(path2+name);
                newltem->setText(0,p);
                newltem->setText(7,name);
                newltem->setIcon(7,pixmap2);
                newltem->setText(8,QString::number(file2.size()));
                newltem->setText(9,file2.lastModified().toString());
                newltem->setIcon(4,qicon3);
                if (file2.isDir()) {
                      newltem->setBackgroundColor(7, qRgb(177,177,177));
                }
                Ui->treeWidget->addTopLevelItem(newltem);
            }
            if (status == 1) {
//                QFileInfo file1(path1+name);
//                QFileInfo file2(path2+name);
                newltem->setText(0,p);
                newltem->setText(1,name);
                newltem->setIcon(1,pixmap1);
                newltem->setText(2,QString::number(file1.size()));
                newltem->setText(3,file1.lastModified().toString());
                newltem->setIcon(4,qicon5);
                newltem->setText(7,name);
                newltem->setIcon(7,pixmap2);
                newltem->setText(9,file2.lastModified().toString());
                newltem->setText(8,QString::number(file2.size()));
                if (file1.isDir()) {
                      newltem->setBackgroundColor(1, qRgb(177,177,177));
                }
                if (file2.isDir()) {
                      newltem->setBackgroundColor(7, qRgb(177,177,177));
                }
                Ui->treeWidget->addTopLevelItem(newltem);
            }
        }
        else if (source == 2) {
            if (status == 0) {
//                QFileInfo file2(path2+name);
                newltem->setText(0,p);
                newltem->setText(7,name);
                newltem->setIcon(7,pixmap2);
                newltem->setText(8,QString::number(file2.size()));
                newltem->setText(9,file2.lastModified().toString());
                newltem->setIcon(6,qicon2);
                if (file2.isDir()) {
                      newltem->setBackgroundColor(7, qRgb(177,177,177));
                }
                Ui->treeWidget->addTopLevelItem(newltem);
            }
            if (status == -1) {
//                QFileInfo file1(path1+name);
                newltem->setText(0,p);
                newltem->setText(1,name);
                newltem->setIcon(1,pixmap1);
                newltem->setText(2,QString::number(file1.size()));
                newltem->setText(3,file1.lastModified().toString());
                newltem->setIcon(6,qicon4);
                if (file1.isDir()) {
                      newltem->setBackgroundColor(1, qRgb(177,177,177));
                }
                Ui->treeWidget->addTopLevelItem(newltem);
            }
            if (status == 1) {
//                QFileInfo file1(path1+name);
//                QFileInfo file2(path2+name);
                newltem->setText(0,p);
                newltem->setText(1,name);
                newltem->setIcon(1,pixmap1);
                newltem->setText(2,QString::number(file1.size()));
                newltem->setText(3,file1.lastModified().toString());
                newltem->setIcon(6,qicon6);
                newltem->setText(7,name);
                newltem->setIcon(7,pixmap2);
                newltem->setText(9,file2.lastModified().toString());
                newltem->setText(8,QString::number(file2.size()));
                if (file1.isDir()) {
                      newltem->setBackgroundColor(1, qRgb(177,177,177));
                }
                if (file2.isDir()) {
                      newltem->setBackgroundColor(7, qRgb(177,177,177));
                }
                Ui->treeWidget->addTopLevelItem(newltem);
            }
//            Ui->treeWidget->addTopLevelItem(newltem);
        }
        else if (source == -1) {//file and file conflict
//            QFileInfo file1(path1+name);
//            QFileInfo file2(path2+name);
            newltem->setText(0,p);
            newltem->setText(1,name);
            newltem->setIcon(1,pixmap1);
            newltem->setText(2,QString::number(file1.size()));
            newltem->setText(3,file1.lastModified().toString());
            newltem->setIcon(5,qicon7);
            newltem->setText(7,name);
            newltem->setIcon(7,pixmap2);
            newltem->setText(9,file2.lastModified().toString());
            newltem->setText(8,QString::number(file2.size()));
            if (file1.isDir()) {
                  newltem->setBackgroundColor(1, qRgb(177,177,177));
            }
            if (file2.isDir()) {
                  newltem->setBackgroundColor(7, qRgb(177,177,177));
            }
            Ui->treeWidget->addTopLevelItem(newltem);
        }
        else if (source == -2) {//file and category confilct
            newltem->setText(0,p);
            newltem->setText(1,name);
            newltem->setIcon(1,pixmap1);
            newltem->setText(2,QString::number(file1.size()));
            newltem->setText(3,file1.lastModified().toString());
            newltem->setIcon(4,qicon8);
            newltem->setIcon(6,qicon8);
            newltem->setText(7,name);
            newltem->setIcon(7,pixmap2);
            newltem->setText(9,file2.lastModified().toString());
            newltem->setText(8,QString::number(file2.size()));
            if (file1.isDir()) {
                  newltem->setBackgroundColor(1, qRgb(177,177,177));
            }
            if (file2.isDir()) {
                  newltem->setBackgroundColor(7, qRgb(177,177,177));
            }
            Ui->treeWidget->addTopLevelItem(newltem);
        }
        i++;
    }
    }
}
