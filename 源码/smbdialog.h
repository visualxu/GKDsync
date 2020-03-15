#ifndef SMBDIALOG_H
#define SMBDIALOG_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class SMBDialog;
}

class SMBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMBDialog(QWidget *parent = nullptr);
    ~SMBDialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void onReadDataError();
    void onReadData();

private:
    Ui::SMBDialog *ui;
    QProcess* cmd = new QProcess();
};

#endif // SMBDIALOG_H
