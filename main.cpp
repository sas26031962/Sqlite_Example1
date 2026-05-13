#include "mainwindow.h"
#include <QApplication>

#include <QCoreApplication>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString sName = w.windowTitle();
    sName += PROGRAMM_SUFFICS;
    w.setWindowTitle(sName);

    w.show();

    return a.exec();
}

