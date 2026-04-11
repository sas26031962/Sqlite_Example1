#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "classes/csqlitedriver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    cSqliteDriver * SqliteDriver;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    bool execActionOpenDatabase();
    bool execActionDropTable();
    bool execActionCreateTable();
    bool execActionInsertRecord();
    bool execActionSelectAll();
    bool execActionCloseDatabase();

public slots:

signals:

};

#endif // MAINWINDOW_H
