QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analyse.cpp \
    back-up-one-way.cpp \
    back-up.cpp \
    createdatabase.cpp \
    deletedialog.cpp \
    end.cpp \
    exec.cpp \
    logdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    one-way_analyse.cpp \
    onexec.cpp \
    rmdir.cpp \
    smbdialog.cpp \
    sync.cpp \
    warning_file_and_category.cpp \
    warningdialog.cpp

HEADERS += \
    analyse.h \
    back-up-one-way.h \
    back-up.h \
    createdatabase.h \
    deletedialog.h \
    end.h \
    exec.h \
    logdialog.h \
    mainwindow.h \
    rmdir.h \
    smbdialog.h \
    sync.h \
    warning_file_and_category.h \
    warningdialog.h

FORMS += \
    deletedialog.ui \
    logdialog.ui \
    mainwindow.ui \
    smbdialog.ui \
    warning_file_and_category.ui \
    warningdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    iconPicture/FFS_tray_16x16.png \
    iconPicture/FFS_tray_24x24.png \
    iconPicture/FreeFileSync.png \
    iconPicture/RealtimeSync.png \
    iconPicture/about_small.png \
    iconPicture/appreciate.png \
    iconPicture/cat_right_only.png \
    iconPicture/cfg_compare.png \
    iconPicture/cfg_sync.png \
    iconPicture/check-circle.png \
    iconPicture/compare.png \
    iconPicture/conflict.png \
    iconPicture/copy_to_left.png \
    iconPicture/copy_to_right.png \
    iconPicture/filter.png \
    iconPicture/filter_small.png \
    iconPicture/load.png \
    iconPicture/new.png \
    iconPicture/reset_dialogs.png \
    iconPicture/save.png \
    iconPicture/settings.png \
    iconPicture/sheet_28.png \
    iconPicture/so_delete_left.png \
    iconPicture/so_delete_right.png \
    iconPicture/so_move_left.png \
    iconPicture/so_move_right.png \
    iconPicture/so_none.png \
    iconPicture/so_update_right_small.png \
    iconPicture/status_finished_success.png \
    iconPicture/status_scanning.png \
    iconPicture/sync.png \
    iconPicture/viewtype_sync_action.png \
    iconPicture/上张.png \
    iconPicture/下张.png \
    iconPicture/保存.png \
    iconPicture/冲销.png \
    iconPicture/同步.png \
    iconPicture/增加.png \
    iconPicture/备份.png \
    iconPicture/已审核.png \
    iconPicture/找平.png \
    iconPicture/新增.png \
    iconPicture/新建.png \
    iconPicture/新建组.png \
    iconPicture/未审核.png \
    iconPicture/科目.png \
    iconPicture/过滤.png

RESOURCES += \
    res.qrc
