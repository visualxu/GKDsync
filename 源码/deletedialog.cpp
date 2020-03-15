#include "deletedialog.h"
#include "mainwindow.h"
#include "ui_deletedialog.h"
#include <QFile>
#include <QDebug>
deleteDialog::deleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteDialog)
{
    ui->setupUi(this);
    setWindowTitle("过滤器");
}

deleteDialog::~deleteDialog()
{
    delete ui;
}

void deleteDialog::on_pushButton_clicked()
{
    QFile file("./grep2.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "file open failed!";
    }
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
    QFile file1("./grep3.txt");
    if(!file1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "file open failed!";
    }
    QTextStream out1(&file1);
    out1 << ui->textEdit_2->toPlainText();
    file1.close();

    this->delfile();
    this->deldir();
    close();
}
void deleteDialog::show(){
    QString displayString;
    QString displayString1;
    QFile file("./grep2.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        displayString.append(str);
    }
       ui->textEdit->clear();
       ui->textEdit->setPlainText(displayString);

       QFile file1("./grep3.txt");
       if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           qDebug()<<"Can't open the file!"<<endl;
       }
       while(!file1.atEnd())
       {
           QByteArray line = file1.readLine();
           QString str(line);
           displayString1.append(str);
       }
          ui->textEdit_2->clear();
          ui->textEdit_2->setPlainText(displayString1);
          this->exec();
}

QStringList deleteDialog::delfile()
{
    QStringList name;
    QFile file1("./grep2.txt");
    name.clear();
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file1.atEnd())
    {
        QByteArray line = file1.readLine();
        QString str(line);
        line.replace("\n","");
        name << line;
    }
//    qDebug() << name;
    return name;
}

QStringList deleteDialog::deldir()
{
    QStringList name;
    QFile file1("./grep3.txt");
    name.clear();
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file1.atEnd())
    {
        QByteArray line = file1.readLine();
        QString str(line);
        line.replace("\n","");
        name << line;
    }
//    qDebug() << name;
    return name;
}
