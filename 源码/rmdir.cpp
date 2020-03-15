#include "rmdir.h"
#include <QDir>
#include <QFile>
#include <QDirIterator>
#include <QtDebug>
void rmd::rmd_1(const QString *path) {
    QDir dir;
    QStringList dirlist;
    QDirIterator dir_iterator(*path,QDir::Files | QDir :: Dirs|QDir :: NoDotAndDotDot,QDirIterator::Subdirectories);//QDirIterator::Subdirectories
    while (dir_iterator.hasNext()) {//QDir :: NoDotAndDotDot,QDir::Files | QDir :: Dirs|
        dir_iterator.next();
        QFileInfo fi = dir_iterator.fileInfo();
//        qDebug()<<fi.absoluteFilePath();
        if (fi.isFile()) {
            QFile::remove(fi.absoluteFilePath());
        }
        else if (fi.isDir()){
            dirlist.append(fi.absoluteFilePath());
        }
    }
    for ( int i = 0;i < dirlist.size();i++) {
        dir.rmpath(dirlist.at(i));
    }
    dir.rmpath(*path);
}
