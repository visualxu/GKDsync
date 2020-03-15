#include "smbdialog.h"
#include "ui_smbdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
SMBDialog::SMBDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SMBDialog)
{
    connect(cmd, SIGNAL(readyReadStandardError()),
            this,
            SLOT(onReadDataError()));
    connect(cmd, SIGNAL(readyReadStandardOutput()),
            this,
            SLOT(onReadData()));
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("//192.168.X.X/XXX");
    setWindowTitle("SAMBA服务器连接");

}

SMBDialog::~SMBDialog()
{
    delete ui;
}
//Ok
void SMBDialog::on_pushButton_clicked()
{
    close();
}

void SMBDialog::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    QString commandProgram = "./smbConnect.sh";      //commandProgram 这个变量是待执行脚本的完整路径
    QStringList args;
    args.append(ui -> lineEdit_4 -> text());                                     //mFileName 是待复制的文件名，作为参数传递给copyFile.sh文件，如果还有其他参数，可以往后加args.append（XX）
    args.append(ui -> lineEdit -> text());
    args.append(ui -> lineEdit_2 -> text());
    args.append(ui -> lineEdit_3 -> text());
    cmd->start(commandProgram,args);
//    ui->textEdit->setPlainText("Successfully!");
//    this->exec();
}
void SMBDialog::onReadData()
{
    cmd->setReadChannel(QProcess::StandardOutput);
    ui -> textEdit ->append(cmd -> readAllStandardOutput());
}
void SMBDialog::onReadDataError()
{
    cmd->setReadChannel(QProcess::StandardError);
    ui -> textEdit ->append(cmd -> readAllStandardError());
}
