#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui {
class deleteDialog;
}

class deleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit deleteDialog(QWidget *parent = nullptr);
    ~deleteDialog();
       void show();
       QStringList delfile();
       QStringList deldir();

private slots:
    void on_pushButton_clicked();

private:
    Ui::deleteDialog *ui;

};

#endif // DELETEDIALOG_H
