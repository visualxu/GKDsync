#include "logdialog.h"
#include "ui_logdialog.h"
#include <QFile>
#include <QDebug>
logDialog::logDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logDialog)
{
    ui->setupUi(this);
    setWindowTitle("日志");
}

logDialog::~logDialog()
{
    delete ui;
}
void logDialog::showlog()
{
    QString displayString;
    QFile file("./log.txt");
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
       ui->textBrowser->clear();
       ui->textBrowser->setPlainText(displayString);
       this->exec();
}
