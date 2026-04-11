#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SqliteDriver = new cSqliteDriver(
        ui->tableView,
        ui->textBrowser,
        ui->groupBoxIncoming
        );

    QPushButton * pbOpenDatabase = new QPushButton("Open");
    pbOpenDatabase->setCursor(Qt::PointingHandCursor);
    connect(pbOpenDatabase, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Open' click";
        if(!execActionOpenDatabase()) this->close();
    });
    ui->statusBar->addWidget(pbOpenDatabase);

    QPushButton * pbDropTable = new QPushButton("Drop Table");
    pbDropTable->setCursor(Qt::PointingHandCursor);
    connect(pbDropTable, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Drop table' click";
        if(!execActionDropTable()) close();
    });
    ui->statusBar->addWidget(pbDropTable);

    QPushButton * pbCreateTable = new QPushButton("Create Table");
    pbCreateTable->setCursor(Qt::PointingHandCursor);
    connect(pbCreateTable, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Create table' click";
        if(!execActionCreateTable()) close();
    });
    ui->statusBar->addWidget(pbCreateTable);

    QPushButton * pbInsertRecord = new QPushButton("Insert Record");
    pbInsertRecord->setCursor(Qt::PointingHandCursor);
    connect(pbInsertRecord, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Insert Record' click";
        if(!execActionInsertRecord()) close();
    });
    ui->statusBar->addWidget(pbInsertRecord);

    QPushButton * pbSelectAll = new QPushButton("Select All");
    pbSelectAll->setCursor(Qt::PointingHandCursor);
    connect(pbSelectAll, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Select All' click";
        if(!execActionSelectAll()) close();
    });
    ui->statusBar->addWidget(pbSelectAll);

    QPushButton * pbCloseDatabase = new QPushButton("Close");
    pbCloseDatabase->setCursor(Qt::PointingHandCursor);
    connect(pbCloseDatabase, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Close database' click";
        if(!execActionCloseDatabase()) close();
    });
    ui->statusBar->addWidget(pbCloseDatabase);

    //Первоначальное открытие базы
    if(!execActionOpenDatabase()) this->close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::execActionOpenDatabase()
{
    return SqliteDriver->openDatabase();
}

bool MainWindow::execActionDropTable()
{
    return SqliteDriver->dropTable();
}

bool MainWindow::execActionCreateTable()
{
    return SqliteDriver->createTable();
}

bool MainWindow::execActionInsertRecord()
{
    auto t1 = std::make_tuple("AuthorName", "SerialName", "BookName");
    return SqliteDriver->insertRecord(t1);
}

bool MainWindow::execActionSelectAll()
{
    //return SqliteDriver->selectAllAndShow();
    return SqliteDriver->selectAllAndViewInTable();
}

bool MainWindow::execActionCloseDatabase()
{
    SqliteDriver->closeDatabase();
    return true;
}
