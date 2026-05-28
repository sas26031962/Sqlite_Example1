#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //cSqliteDriver::qsApplicationPath = QCoreApplication::applicationFilePath();

    QString Message = "MainWindow > ";
    QString qsFullApplicationPath = QCoreApplication::applicationFilePath();
    int SlashPosition = qsFullApplicationPath.indexOf("/release");
    if(SlashPosition < 0)
    {
        SlashPosition = qsFullApplicationPath.indexOf("/debug");
        if(SlashPosition < 0)
        {
            Message += "no /debug section in ApplicationPath, exit!";
            ui->textBrowserLog->append(Message);
            close();
        }
    }
    //Извлечение пути к приложению
    cSqliteDriver::qsApplicationPath = qsFullApplicationPath.mid(0, SlashPosition);
    Message += "ApplicationPath = ";
    Message += cSqliteDriver::qsApplicationPath;
    ui->textBrowserLog->append(Message);

    SqliteDriver = new cSqliteDriver(
                ui->tableView,
                ui->textBrowserLog,
                ui->groupBoxIncoming,
                ui->comboBoxHistory
                );

    ExtrnalData = new cExternalData(ui->groupBoxExternalData);
    connect(ExtrnalData, &cExternalData::closeMainProgramm, this, &MainWindow::close);
    connect(ExtrnalData, &cExternalData::setStatus, SqliteDriver, &cSqliteDriver::showMessage);
    connect(ExtrnalData, &cExternalData::setDataString, SqliteDriver, &cSqliteDriver::execSetDataString);

    //Создание кнопок управления
//    QPushButton * pbOpenDatabase = new QPushButton("Open");
//    pbOpenDatabase->setCursor(Qt::PointingHandCursor);
//    connect(pbOpenDatabase, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
//        qDebug() << "PushButton 'Open' click";
//        if(!execActionOpenDatabase()) this->close();
//    });
//    ui->statusBar->addWidget(pbOpenDatabase);

//    QPushButton * pbDropTable = new QPushButton("Drop Table");
//    pbDropTable->setCursor(Qt::PointingHandCursor);
//    connect(pbDropTable, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
//        qDebug() << "PushButton 'Drop table' click";
//        if(!execActionDropTable()) close();
//    });
//    ui->statusBar->addWidget(pbDropTable);

//    QPushButton * pbCreateTable = new QPushButton("Create Table");
//    pbCreateTable->setCursor(Qt::PointingHandCursor);
//    connect(pbCreateTable, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
//        qDebug() << "PushButton 'Create table' click";
//        if(!execActionCreateTable()) close();
//    });
//    ui->statusBar->addWidget(pbCreateTable);
    //---
    QPushButton * pbSetAuthor = new QPushButton("Set Author");
    pbSetAuthor->setCursor(Qt::PointingHandCursor);
    connect(pbSetAuthor, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Set Author' click";
        if(!execActionSetAuthor()) close();
    });
    ui->statusBar->addWidget(pbSetAuthor);

    QPushButton * pbSetSerial = new QPushButton("Set Serial");
    pbSetSerial->setCursor(Qt::PointingHandCursor);
    connect(pbSetSerial, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Set Serial' click";
        if(!execActionSetSerial()) close();
    });
    ui->statusBar->addWidget(pbSetSerial);

    QPushButton * pbSetVolume = new QPushButton("Set Volume");
    pbSetVolume->setCursor(Qt::PointingHandCursor);
    connect(pbSetVolume, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Set Volume' click";
        if(!execActionSetVolume()) close();
    });
    ui->statusBar->addWidget(pbSetVolume);

    QPushButton * pbSetName = new QPushButton("Set Name");
    pbSetName->setCursor(Qt::PointingHandCursor);
    connect(pbSetName, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Set Name' click";
        if(!execActionSetName()) close();
    });
    ui->statusBar->addWidget(pbSetName);
    //---
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

    QPushButton * pbExecRequest = new QPushButton("Exec request");
    pbExecRequest->setCursor(Qt::PointingHandCursor);
    connect(pbExecRequest, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Exec request' click";
        if(!execActionExecRequest()) close();
    });
    ui->statusBar->addWidget(pbExecRequest);

//    QPushButton * pbCloseDatabase = new QPushButton("Close");
//    pbCloseDatabase->setCursor(Qt::PointingHandCursor);
//    connect(pbCloseDatabase, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
//        qDebug() << "PushButton 'Close database' click";
//        if(!execActionCloseDatabase()) close();
//    });
//    ui->statusBar->addWidget(pbCloseDatabase);

    //--- Подключение действий
    //File
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    //Actions

    connect(ui->actionOpen, &QAction::triggered, [this](bool x){
        qDebug() << "PushButton 'Open' click: " << x;
        if(!execActionOpenDatabase()) this->close();
    });

    connect(ui->actionDropTable, &QAction::triggered, [this](bool x){
        qDebug() << "PushButton 'Drop table' click: " << x;
        if(!execActionDropTable()) close();
    });

    connect(ui->actionCreateTable, &QAction::triggered, [this](bool x){
        qDebug() << "PushButton 'Create table' click: " << x;
        if(!execActionCreateTable()) close();
    });

    connect(ui->actionClose, &QAction::triggered, [this](bool x){
        qDebug() << "PushButton 'Close database' click: " << x;
        if(!execActionCloseDatabase()) close();
    });

    connect(ui->actionGetAuthorList, &QAction::triggered, [this](bool x){
        qDebug() << "MainMenu 'getAuthorList' click: " << x;
        if(!SqliteDriver->getAuthorList()) close();
    });

    connect(ui->actionCheckRecordInclusion, &QAction::triggered, [this](bool x){
        qDebug() << "MainMenu 'checkRecordInclusion' click: " << x;
        if(!SqliteDriver->checkDataIncludion()) close();
    });

    //--- Открытие базы данных
    if(!execActionOpenDatabase()) this->close();

    qDebug() << "Window size: " << this->width() << "x" << this->height();

}//End of ctor

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(
        this, "Confirmation",
        tr("Are you shure to exit?\n"),
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
        QMessageBox::Yes);

    if (resBtn != QMessageBox::Yes)
    {
        event->ignore(); // Игнорируем событие закрытия
    }
    else
    {
        event->accept(); // Принимаем событие закрытия

        //---
        //if(SqliteDriver != nullptr)
        SqliteDriver->storeRequestHistory();
        SqliteDriver->storeAuthorsList();
        //---
    }
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
    QString qsAuthor = SqliteDriver->getAuthor();
    QString qsSerial = SqliteDriver->getSerial();
    QString qsVolume = SqliteDriver->getVolume();
    QString qsName = SqliteDriver->getName();
    auto t1 = std::make_tuple(qsAuthor, qsSerial, qsVolume, qsName);
    return SqliteDriver->insertRecord(t1);
}

bool MainWindow::execActionSelectAll()
{
    return SqliteDriver->selectAllAndViewInTable();
}

bool MainWindow::execActionExecRequest()
{
    return SqliteDriver->execRequest();
}

bool MainWindow::execActionCloseDatabase()
{
    return SqliteDriver->closeDatabase();
}

bool MainWindow::execActionSetAuthor()
{
    qDebug() << "MainWindow: execActionSetAuthor()";
    return SqliteDriver->setAuthor();
}

bool MainWindow::execActionSetSerial()
{
    qDebug() << "MainWindow: execActionSetSerial()";
    return SqliteDriver->setSerial();
}

bool MainWindow::execActionSetVolume()
{
    qDebug() << "MainWindow: execActionSetVolume()";
    return SqliteDriver->setVolume();
}

bool MainWindow::execActionSetName()
{
    qDebug() << "MainWindow: execActionSetName()";
    return SqliteDriver->setName();
}
