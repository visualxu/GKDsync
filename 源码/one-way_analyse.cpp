#include "analyse.h"
#include <QFile>
#include <QPixmap>
void analyse::owanaly(QSqlQuery sql_query, Ui::MainWindow *ui, QString path1, QString path2,QString name,int a) {
    QIcon qicon1 = QIcon(":/iconPicture/copy_to_right.png");
    QIcon qicon2 = QIcon(":/iconPicture/copy_to_left.png");
    QIcon qicon3 = QIcon(":/iconPicture/so_delete_left.png");
    QIcon qicon4 = QIcon(":/iconPicture/so_delete_right.png");
    QIcon qicon5 = QIcon(":/iconPicture/so_update_right_small.png");
    QIcon qicon6 = QIcon(":/iconPicture/so_update_left.png");
    if (a == 0) {
        QString add = QString("select * from '%1'").arg(name);
        sql_query.exec(add);
        int i = 1;
        //    if (qicon7.isNull()) {
        //        qDebug()<<"haha";
        //    }
        //    else {
        //        qDebug()<<"nihao";
        //    }
        while (sql_query.next()) {
            QString p = QString("%1").arg(i);
            QString filename = sql_query.value(0).toString();
            int time = sql_query.value(1).toInt();
            QTreeWidgetItem *newltem = new QTreeWidgetItem();
            QFileInfo file1(path1+filename);
            QFileInfo file2(path2+filename);
            QPixmap pixmap1(file1.isDir() ? ":/iconPicture/dir.png":":/iconPicture/file.png");
            QPixmap pixmap2(file2.isDir() ? ":/iconPicture/dir.png":":/iconPicture/file.png");
            if (time > 0) {//add
                //            qDebug()<<time;
                //            QFileInfo file1(path1+filename);
                int size = file1.size();
                newltem->setText(0,p);
                newltem->setText(1,filename);
                newltem->setIcon(1,pixmap1);
                newltem->setText(2,QString::number(size));
                newltem->setText(3,file1.lastModified().toString());
                newltem->setIcon(4,qicon1);
                if (file1.isDir()) {
                    newltem->setBackgroundColor(1, qRgb(177,177,177));
                }
                ui->treeWidget->addTopLevelItem(newltem);
                i++;
            }
//            else if (time == 0 ) {//not sync
//                i--;
//            }
            else if (time == -1) {//delete
                //            QFileInfo file2(filename);
                newltem->setText(0,p);
                newltem->setIcon(6,qicon4);
                newltem->setText(7,filename);
                newltem->setIcon(7,pixmap2);
                newltem->setText(8,QString::number(file2.size()));
                newltem->setText(9,file2.lastModified().toString());
                if (file2.isDir()) {
                    newltem->setBackgroundColor(7, qRgb(177,177,177));
                }
                ui->treeWidget->addTopLevelItem(newltem);
                i++;
            }
            else if (time == -2) {//modify
                //            QFileInfo file1(path1+filename);
                //            QFileInfo file2(path2+filename);
                if (file1.isFile()) {
                    newltem->setText(0,p);
                    newltem->setText(1,filename);
                    newltem->setIcon(1,pixmap1);
                    newltem->setText(2,QString::number(file1.size()));
                    newltem->setText(3,file1.lastModified().toString());
                    newltem->setIcon(4,qicon5);
                    newltem->setText(7,filename);
                    newltem->setIcon(7,pixmap2);
                    newltem->setText(8,QString::number(file2.size()));
                    newltem->setText(9,file2.lastModified().toString());
                    if (file1.isDir()) {
                        newltem->setBackgroundColor(1, qRgb(177,177,177));
                    }
                    if (file2.isDir()) {
                        newltem->setBackgroundColor(7, qRgb(177,177,177));
                    }
                    ui->treeWidget->addTopLevelItem(newltem);
                    i++;
                }
            }
//            i++;
        }
    }
    else {
        QString add = QString("select * from '%1'").arg(name);
        sql_query.exec(add);
        int i = 1;
        //    if (qicon7.isNull()) {
        //        qDebug()<<"haha";
        //    }
        //    else {
        //        qDebug()<<"nihao";
        //    }
        while (sql_query.next()) {
            QString p = QString("%1").arg(i);
            QString filename = sql_query.value(0).toString();
            int time = sql_query.value(1).toInt();
            QTreeWidgetItem *newltem = new QTreeWidgetItem();
            QFileInfo file1(path1+filename);
            QFileInfo file2(path2+filename);
            QPixmap pixmap1(file1.isDir() ? ":/iconPicture/dir.png":":/iconPicture/file.png");
            QPixmap pixmap2(file2.isDir() ? ":/iconPicture/dir.png":":/iconPicture/file.png");
            if (time > 0) {//add
                //            qDebug()<<time;
                //            QFileInfo file1(path1+filename);
                int size = file1.size();
                newltem->setText(0,p);
                newltem->setText(7,filename);
                newltem->setIcon(7,pixmap1);
                newltem->setText(8,QString::number(size));
                newltem->setText(9,file1.lastModified().toString());
                newltem->setIcon(6,qicon2);
                if (file1.isDir()) {
                    newltem->setBackgroundColor(7, qRgb(177,177,177));
                }
                ui->treeWidget->addTopLevelItem(newltem);
                i++;
            }
//            else if (time == 0 ) {//not sync
//                i--;
//            }
            else if (time == -1) {//delete
                //            QFileInfo file2(filename);
                newltem->setText(0,p);
                newltem->setIcon(4,qicon3);
                newltem->setText(1,filename);
                newltem->setIcon(1,pixmap2);
                newltem->setText(2,QString::number(file2.size()));
                newltem->setText(3,file2.lastModified().toString());
                if (file2.isDir()) {
                    newltem->setBackgroundColor(1, qRgb(177,177,177));
                }
                ui->treeWidget->addTopLevelItem(newltem);
                i++;
            }
            else if (time == -2) {//modify
                //            QFileInfo file1(path1+filename);
                //            QFileInfo file2(path2+filename);
                if (file1.isFile()) {
                    newltem->setText(0,p);
                    newltem->setText(1,filename);
                    newltem->setIcon(1,pixmap1);
                    newltem->setText(2,QString::number(file2.size()));
                    newltem->setText(3,file2.lastModified().toString());
                    newltem->setIcon(6,qicon6);
                    newltem->setText(7,filename);
                    newltem->setIcon(7,pixmap2);
                    newltem->setText(8,QString::number(file1.size()));
                    newltem->setText(9,file1.lastModified().toString());
                    if (file1.isDir()) {
                        newltem->setBackgroundColor(1, qRgb(177,177,177));
                    }
                    if (file2.isDir()) {
                        newltem->setBackgroundColor(7, qRgb(177,177,177));
                    }
                    ui->treeWidget->addTopLevelItem(newltem);
                    i++;
                }
            }
//            i++;
        }
    }
//    QString drop = QString("drop table '%1'").arg(name);
//    if(!sql_query.exec(drop))
//    {
//        qDebug()<<sql_query.lastError();
//    }

}
