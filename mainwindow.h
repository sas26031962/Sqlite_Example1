#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>

#include "classes/csqlitedriver.h"
#include "classes/cexternaldata.h"

namespace Ui {
class MainWindow;
}

//=============================================================================
// КОНСТАНТЫ
//=============================================================================
#define PROGRAMM_SUFFICS " 20260430"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    cSqliteDriver * SqliteDriver;
    cExternalData * ExtrnalData;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    bool execActionOpenDatabase();
    bool execActionDropTable();
    bool execActionCreateTable();
    bool execActionInsertRecord();
    bool execActionSelectAll();
    bool execActionExecRequest();
    bool execActionCloseDatabase();
    bool execActionSetAuthor();
    bool execActionSetSerial();
    bool execActionSetVolume();
    bool execActionSetName();

public slots:

signals:

};

#endif // MAINWINDOW_H
