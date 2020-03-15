#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>

namespace Ui {
class logDialog;
}

class logDialog : public QDialog
{
    Q_OBJECT

public:
    explicit logDialog(QWidget *parent = nullptr);
    ~logDialog();
     void showlog();

private:
    Ui::logDialog *ui;
};

#endif // LOGDIALOG_H
