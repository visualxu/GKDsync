#include "warningdialog.h"
#include "ui_warningdialog.h"
extern int switch1;
WarningDialog::WarningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningDialog)
{
    ui->setupUi(this);
    setWindowTitle("注意");

}

WarningDialog::~WarningDialog()
{
    delete ui;
}

void WarningDialog::on_pushButton_clicked()
{
    close();
    MainWindow::switch1 = 1;
}

void WarningDialog::on_btn_ignore_clicked()
{
    MainWindow::switch1 = 2;
    close();
}
