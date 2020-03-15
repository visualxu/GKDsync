#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class WarningDialog;
}

class WarningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WarningDialog(QWidget *parent = nullptr);
    ~WarningDialog();

private slots:
    void on_pushButton_clicked();

    void on_btn_ignore_clicked();

private:
    Ui::WarningDialog *ui;
};

#endif // WARNINGDIALOG_H
