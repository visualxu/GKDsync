#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    w.resize(DESKTOP_WIDTH, DESKTOP_HEIGHT);
//    w.showMaximized();
    w.show();
    return a.exec();
}
