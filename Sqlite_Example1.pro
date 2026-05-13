#-------------------------------------------------
#
# Project created by QtCreator 2026-04-06T13:54:55
#
#-------------------------------------------------

QT       += core gui
QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sqlite_Example1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classes/csqlitedriver.cpp \
    classes/ccontrolincoming.cpp \
    classes/cclickablelabel.cpp \
    classes/cloadfiles.cpp \
    classes/cexternaldata.cpp

HEADERS  += mainwindow.h \
    classes/csqlitedriver.h \
    classes/ccontrolincoming.h \
    classes/cclickablelabel.h \
    classes/cloadfiles.h \
    classes/cexternaldata.h

FORMS    += mainwindow.ui

win32 {
    RC_FILE += file.rc
    OTHER_FILES += file.rc
}
