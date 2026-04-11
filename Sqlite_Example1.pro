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
    classes/csqlitedriver.cpp

HEADERS  += mainwindow.h \
    classes/csqlitedriver.h

FORMS    += mainwindow.ui
