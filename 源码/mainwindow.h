#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <utime.h>
#include "warning_file_and_category.h"
#include <QProgressDialog>
#include "warningdialog.h"
#include "end.h"
#include "back-up-one-way.h"
#include <rmdir.h>
#include "exec.h"
#include "createdatabase.h"
#include <QMainWindow>
#include "logdialog.h"
#include "deletedialog.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include"back-up.h"
#include <QDirIterator>
#include<QQueue>
#include<QDateTime>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QDirModel>
#include <QLabel>
#include <QMouseEvent>
#include <QComboBox>
#include <QAction>
#include <QMenuBar>
#include <QDialog>
#include <QColorDialog>
#include <QFontDialog>

#define DESKTOP_WIDTH    1440		   //主界面大小
#define DESKTOP_HEIGHT	 648
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QString path1;
    static QString path2;
    static int a;
    static  QString displayString;
    static QString displayString1;
    static int start;
    static QSqlQuery sql_query;
    static QSqlDatabase db;
    static QStringList namedir;
    static QStringList namefile;
    static QString name;
    static int switch1;

    Ui::MainWindow *ui;
    QAction * test;
private:
    QAction * one;
    QAction * two;
    QList<QAction*> List;
    QMenu*menu1;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_3_currentTextChanged(const QString &arg1);\
    void on_pushButton_7_clicked();

    void function();

    void function2();

    void itemPressedSlot(QTreeWidgetItem *, int);

public:

};
#endif // MAINWINDOW_H
