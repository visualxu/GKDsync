#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSql>
#include "analyse.h"
#include "smbdialog.h"
#include <unistd.h>
QString MainWindow::path1;
QString MainWindow::path2;
QString MainWindow::displayString;
QString MainWindow::displayString1;
QString MainWindow::name;
QSqlQuery MainWindow::sql_query;
QSqlDatabase MainWindow::db;
QStringList MainWindow::namedir;
QStringList MainWindow::namefile;
int MainWindow::a=0;
int MainWindow::start = 0;
int MainWindow::switch1 = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //设置ui标题跟图标
    setWindowTitle("GKDsync");
    setWindowIcon(QIcon(":/iconPicture/logo.png"));

    QStringList headerList;
    headerList.append(tr("序号"));
    headerList.append(tr("文件名"));
    headerList.append(tr("大小"));
    headerList.append(tr("最后修改时间"));
    headerList.append(tr("状态"));
    headerList.append(tr("选择"));
    headerList.append(tr("状态"));
    headerList.append(tr("文件名"));
    headerList.append(tr("大小"));
    headerList.append(tr("最后修改时间"));
    ui->treeWidget->setHeaderLabels(headerList);
    ui->treeWidget->setColumnWidth(0,30);
    ui->treeWidget->setColumnWidth(1,300);
    ui->treeWidget->setColumnWidth(2,50);
    ui->treeWidget->setColumnWidth(3,225);
    ui->treeWidget->setColumnWidth(4,25);
    ui->treeWidget->setColumnWidth(5,25);
    ui->treeWidget->setColumnWidth(6,25);
    ui->treeWidget->setColumnWidth(7,300);
    ui->treeWidget->setColumnWidth(8,50);
    ui->treeWidget->setColumnWidth(9,180);
//    ui->treeWidget->header()->setSectionResizeMode(0,QHeaderView::Stretch);
//    ui->treeWidget->header()->setSectionResizeMode(1,QHeaderView::Stretch);
//    ui->treeWidget->header()->setSectionResizeMode(2,QHeaderView::Stretch);
//    ui->treeWidget->header()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->treeWidget->header()->setSectionResizeMode(4,QHeaderView::Fixed);
    ui->treeWidget->header()->setSectionResizeMode(5,QHeaderView::Fixed);
    ui->treeWidget->header()->setSectionResizeMode(6,QHeaderView::Fixed);
//    ui->treeWidget->header()->setSectionResizeMode(7,QHeaderView::Stretch);
//    ui->treeWidget->header()->setSectionResizeMode(8,QHeaderView::Stretch);
//    ui->treeWidget->header()->setSectionResizeMode(9,QHeaderView::Stretch);
    ui->treeWidget->clear();

    //tooltip_new
    QString str1=QStringLiteral("分析");
    ui->pushButton_4->setToolTip(str1);
    QString str2=QStringLiteral("同步");
    ui->pushButton->setToolTip(str2);
    QString str3=QStringLiteral("过滤");
    ui->pushButton_6->setToolTip(str3);
    QString str4=QStringLiteral("网络传输");
    ui->pushButton_7->setToolTip(str4);
    QString str6=QStringLiteral("选择文件夹");
    ui->pushButton_2->setToolTip(str6);
    QString str7=QStringLiteral("选择文件夹");
    ui->pushButton_3->setToolTip(str7);
    QString str8=QStringLiteral("第一个文件夹路径");
    ui->comboBox->setToolTip(str8);
    QString str9=QStringLiteral("第二个文件夹路径");
    ui->comboBox_3->setToolTip(str9);
    QString str10=QStringLiteral("同步方式");
    ui->comboBox_2->setToolTip(str10);
    QString str11=QStringLiteral("日志记录");
    ui->pushButton_5->setToolTip(str11);

    ui->statusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角
    ui->statusBar->showMessage(tr("Designed By GKD"));//

    ui->treeWidget->setStyleSheet(
                "QHeaderView::section{font:14pt '微软雅黑';}"
                "QTreeView::item:hover{background-color:rgb(85, 170, 255)}"
                "QTreeView::item:selected{background-color:rgb(85, 170, 255)}"
                );

    /***************/
    this->setStyleSheet("QMainWidget{background-color:rgba(0,0,0);}"
                        "QPushButton{background-color: rgba(255, 255, 255, 0);border:1px solid gray;border-radius:10px;}"
                        "QPushButton:hover{background-color: rgba(85, 170, 255, 0);border:1px solid black;border-radius:10px;background:rgb(85, 170, 255);}"
                        "QPushButton:press{background-color: rgba(85, 170, 255, 0);border:1px solid black;border-radius:10px;background:rgb(85, 170, 255);}"
//                        "QComboBox{background-color: rgba(255, 255, 255, 0);border:2px solid black;border-radius:2px;}"
                        );
    /****************/
    one = new QAction("向左同步",ui->treeWidget);
    two = new QAction("向右同步",ui->treeWidget);
    List << one << two;
    menu1 = new QMenu(ui->treeWidget);
    connect(ui->treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(itemPressedSlot(QTreeWidgetItem*,int)));
    connect(one, SIGNAL(triggered(bool)), this, SLOT(function()));
    connect(two, SIGNAL(triggered(bool)), this, SLOT(function2()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_2_clicked()
{
    QString directory=QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("Save path"),QDir::currentPath()));
    if(!directory.isEmpty())
    {
        if(ui->comboBox->findText(directory)==-1)
            ui->comboBox->addItem(directory);
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(directory));

    }
    path1 = directory.toStdString().data();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString directory=QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("Save path"),QDir::currentPath()));
    if(!directory.isEmpty())
    {
        if(ui->comboBox_3->findText(directory)==-1)
            ui->comboBox_3->addItem(directory);
        ui->comboBox_3->setCurrentIndex(ui->comboBox_3->findText(directory));

    }
    path2 = directory.toStdString().data();
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if(arg1.contains("向右同步"))
    {
        a=0;
    }
    if(arg1.contains("向左同步"))
    {
        a=1;
    }
    if(arg1.contains("双向同步"))
    {
        a=2;
    }
}


void MainWindow::on_pushButton_clicked()
{
    int count;
    if(a==0)
    {
        ui->pushButton->setEnabled(false);
        /**********Set ProgressBar**************/
        count = 0;
        sql_query.exec("select * from owfile where time != 0");
        if (sql_query.last()) {
            count = sql_query.at() + 1;
        }
        else {
            count = 0;
        }
        QProgressDialog* dialog = new QProgressDialog(tr("File sync progress"), tr("Cancel"), 0, count, this);
        dialog->setWindowTitle(tr("Progress"));
        dialog->setWindowModality(Qt::WindowModal);
        dialog->show();
        /**********Set ProgressBar**************/
        qDebug() << path1<<"向右同步"<<path2;
        execlute exec;
        exec.owexec(sql_query,path1,path2,name,a,dialog);
        //        dialog->setValue(count);
        delete dialog;
        ui->treeWidget->clear();
    }
    if(a==1)
    {
        ui->pushButton->setEnabled(false);
        /**********Set ProgressBar**************/
        count = 0;
        sql_query.exec("select * from owfile where time != 0");
        if (sql_query.last()) {
            count = sql_query.at() + 1;
        }
        else {
            count = 0;
        }
        QProgressDialog* dialog = new QProgressDialog(tr("File sync progress"), tr("Cancel"), 0, count, this);
        dialog->setWindowTitle(tr("Progress"));
        dialog->setWindowModality(Qt::WindowModal);
        dialog->show();
        /**********Set ProgressBar**************/
        qDebug() << path1<<"向左同步"<<path2;
        execlute exec;
        exec.owexec(sql_query,path2,path1,name,a,dialog);
        //        dialog->setValue(count);
        delete dialog;
        ui->treeWidget->clear();

    }
    if(a==2)
    {
        QStringList list2 = displayString1.split("\n");
        QStringList list1 = displayString.split("\n");
        start = 1;
        int pos0 = 0;
        sql_query.exec("select * from fileinfo where source = -2");
        if (sql_query.last()) {
            pos0 = sql_query.at()+1;
        }
        if (pos0 > 0) {
            warning_file_and_category warn0;
            warn0.exec();
            return;
        }
        int pos = 0;
        sql_query.exec("select * from fileinfo where source = -1");
        int first = sql_query.at();
        if (sql_query.last()) {
            pos = sql_query.at()+1;
        }
        sql_query.seek(first);
        if (pos > 0) {
            WarningDialog warn;
            warn.exec();
            while (switch1 == 0) {

            }
            if (switch1 == 2) {
                /**********Set ProgressBar**************/
                count = 0;
                sql_query.exec("select * from fileinfo where status != 9");
                if (sql_query.last()) {
                    count = sql_query.at() + 1;
                }
                else {
                    count = 0;
                }
                QProgressDialog *dialog_1 = new QProgressDialog(tr("File sync progress"), tr("Cancel"), 0, count, this);
                dialog_1->setWindowTitle(tr("Progress"));
                dialog_1->setWindowModality(Qt::WindowModal);
                dialog_1->show();
                /**********Set ProgressBar**************/
                //                qDebug() <<path1<<"双向同步"<<path2;
                //                start = 1;
                sql_query.exec("select * from fileinfo where source = -1");
                QSqlQuery sql_query1 = sql_query;
                while (sql_query.next()) {
                    QString nameconf = sql_query.value(0).toString();
                    QFileInfo file1(path1+nameconf);
                    QFileInfo file2(path2+nameconf);


                    if (file1.lastModified().toTime_t() > file2.lastModified().toTime_t()) {
                        sql_query1.prepare("update fileinfo set status = 1, time = ? , source = 1,size = 0 where name = ?");
                        if (file1.isDir()) {
                            sql_query1.bindValue(0,0);

                        }
                        else {
                            sql_query1.bindValue(0,file1.lastModified().toTime_t());
                        }
                        sql_query1.bindValue(1,nameconf);
                        sql_query1.exec();
                        //                        utimbuf timekkk;
                        //                        timekkk.modtime = file1.lastModified().toTime_t();
                        //                        QByteArray s = (path2+name).toUtf8();
                        //                        char *filename;
                        //                        filename = s.data();
                        //                        utime(filename,&timekkk);
                    }
                    else  {
                        sql_query1.prepare("update fileinfo set status = 1, time = ? , source = 2, size = 0 where name = ?");
                        if (file1.isDir()) {
                            sql_query1.bindValue(0,0);

                        }
                        else {
                            sql_query1.bindValue(0,file1.lastModified().toTime_t());
                        }
                        sql_query1.bindValue(1,nameconf);
                        sql_query1.exec();

                    }
                }
                ui->pushButton->setEnabled(false);
                execlute exec_1;
                exec_1.exec(sql_query,&path2,&path1,dialog_1);
                end_1 end1;
                end1.end(sql_query,name);
                ui->treeWidget->clear();
                //                dialog_1->setValue(count);
                delete dialog_1;
            }
        }
        else {
            /**********Set ProgressBar**************/
            count = 0;
            sql_query.exec("select * from fileinfo where status != 9");
            if (sql_query.last()) {
                count = sql_query.at() + 1;
            }
            else {
                count = 0;
            }

            QProgressDialog* dialog_2 = new QProgressDialog(tr("File sync progress"), tr("Cancel"), 0, count, this);
            dialog_2->setWindowTitle(tr("Progress"));
            dialog_2->setWindowModality(Qt::WindowModal);
            dialog_2->show();
            //            if (count < 100) {
            //                sleep(1);
            //            }
            /**********Set ProgressBar**************/
            ui->pushButton->setEnabled(false);
            execlute exec_1;
            exec_1.exec(sql_query,&path2,&path1,dialog_2);
            end_1 end1;
            end1.end(sql_query,name);
            ui->treeWidget->clear();
            //            dialog_2->setValue(count);
            delete dialog_2;
        }
    }
    //       db.close();
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->treeWidget->clear();
    db = QSqlDatabase::addDatabase("QSQLITE");
    database database;
    name = path1+path2;
    if (a != 2) {
        name = "owfile";
    }
    sql_query = database.create(db,a,path1,path2);
    one_way oneway;
    QProgressDialog* dialog = new QProgressDialog(tr("File sync progress"), tr("Cancel"), 0, 100, this);
    dialog->setFixedWidth(600);
    dialog->setWindowTitle(tr("分析"));
    dialog->setWindowModality(Qt::WindowModal);
    dialog->show();
    switch (a) {
    case 0:
        oneway.oneway(name,sql_query,path1,namedir,namefile,1,dialog);
        oneway.oneway(name,sql_query,path2,namedir,namefile,2,dialog);
        dialog->setValue(100);
        break;
    case 1:
        oneway.oneway(name,sql_query,path2,namedir,namefile,1,dialog);
        oneway.oneway(name,sql_query,path1,namedir,namefile,2,dialog);
        dialog->setValue(100);
        break;
    case 2:
        back_up back_up1;
        back_up1.BfsCollectFiles(path1,&displayString,1,&path2,sql_query,namedir,namefile,dialog);
        QString display1 = displayString;
        back_up1.BfsCollectFiles(path2,&displayString1,2,&path1,sql_query,namedir,namefile,dialog);
        QString display2 = displayString1;
        dialog->setValue(100);
        break;
    }
    delete dialog;


    //start
    if (a == 2) {
        analyse analyse1;
        analyse1.analy(sql_query,ui,path1,path2);
    }
    else if (a == 0){
        analyse analyse2;
        analyse2.owanaly(sql_query,ui,path1,path2,name,a);
    }
    else {
        analyse analyse2;
        analyse2.owanaly(sql_query,ui,path2,path1,name,a);
    }
    //        execlute exec_1;
    //        exec_1.exec(sql_query,&path1,&path2);
    ui->pushButton->setEnabled(true);

}

void MainWindow::on_pushButton_5_clicked()
{
    //    logDialog* dia = new logDialog(this);
    logDialog dia;
    //    dia->showlog();
    dia.showlog();
}
void MainWindow::on_pushButton_6_clicked()
{
    deleteDialog del;
    //    deleteDialog *del = new  deleteDialog();
    del.show();
    namedir = del.deldir();
    namefile = del.delfile();
    qDebug()<<namedir<<"haha";
    qDebug()<<namefile<<"haha";
    //    del.show();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this,"退出","是否确定关闭");
    if(ret == QMessageBox::Yes)
    {
        //关闭窗口
        event->accept();
    }else {
        //不关闭
        event->ignore();
    }
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    path1=arg1;
}

void MainWindow::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    path2=arg1;

}

void MainWindow::on_pushButton_7_clicked()
{
    SMBDialog dlg;
    dlg.exec();
    QString directory=QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("Save path"),"../.."));//第三个参数自定义选择文件路径
    if(!directory.isEmpty())
    {
        if(ui->comboBox->findText(directory)==-1)
            ui->comboBox->addItem(directory);
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(directory));

    }
    path1 = directory.toStdString().data();
}
void MainWindow::itemPressedSlot(QTreeWidgetItem * pressedItem, int column)
{
    QTreeWidgetItem* curItem=ui->treeWidget->currentItem();
    QString wellName = curItem->text(0);
    if(qApp->mouseButtons() == Qt::RightButton)   //判断是否为右键
    {
        if (!pressedItem->icon(5).isNull())
        {
            menu1->addActions(List);
            menu1->exec(QCursor::pos());
        }
    }
}

void MainWindow::function()
{
    QSqlQuery sql_query1 = sql_query;
    QIcon qicon = QIcon(":/iconPicture/check-circle.png");
    QIcon qicon1 = QIcon(":/iconPicture/copy_to_left.png");
    QIcon qicon2 = QIcon(":/iconPicture/white.png");
    QTreeWidgetItem* curItem=ui->treeWidget->currentItem();
    QString wellName = curItem->text(1);
    curItem->setIcon(6,qicon1);
    curItem->setIcon(5,qicon);
    curItem->setIcon(4,qicon2);
    QFileInfo fi(path2+wellName);
    sql_query1.prepare("update fileinfo set time = ?, source = 2,size = 0 where name = ?");
    sql_query1.bindValue(0,fi.lastModified().toTime_t());
    sql_query1.bindValue(1,wellName);
    sql_query1.exec();
}

void MainWindow::function2()
{
    QSqlQuery sql_query1 = sql_query;
    QIcon qicon = QIcon(":/iconPicture/check-circle.png");
    QIcon qicon1 = QIcon(":/iconPicture/copy_to_right.png");
    QIcon qicon2 = QIcon(":/iconPicture/white.png");
    QTreeWidgetItem* curItem=ui->treeWidget->currentItem();
    QString wellName = curItem->text(1);
    curItem->setIcon(5,qicon);
    curItem->setIcon(4,qicon1);
    curItem->setIcon(6,qicon2);
    qDebug()<<wellName;
    QFileInfo fi(path1+wellName);
    sql_query1.prepare("update fileinfo set time = ?, source = 1,size = 0 where name = ?");
    sql_query1.bindValue(0,fi.lastModified().toTime_t());
    sql_query1.bindValue(1,wellName);
    sql_query1.exec();
}
