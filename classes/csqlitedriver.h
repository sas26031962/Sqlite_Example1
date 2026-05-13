#ifndef CSQLITEDRIVER_H
#define CSQLITEDRIVER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTableView>
#include <QModelIndex>
#include <QTextBrowser>
#include <QGroupBox>
#include <QHeaderView>
#include <QAbstractItemModel>
#include <QComboBox>

#include <tuple>

#include "classes/ccontrolincoming.h"
#include "classes/cloadfiles.h"

class cSqliteDriver : public QObject
{
    Q_OBJECT

    //Атрибуты
    QString qsName = "SqliteDriver";
    QString qsMessage;
    QString qsRequestsFileName = "/data/SQL_Requests.txt";
    QString qsAuthorsFileName = "/data/Authors.txt";
    QStringList qslRequests;
    QStringList qslAuthors;

    QTableView * TableView;
    QTextBrowser* tbLog;
    QGroupBox * gbIncoming;
    cControlIncoming * ControlIncoming;
    QComboBox * cbHistory;
    QHeaderView * VerticalHeader;
    QHeaderView * HorizontalHeader;

    QSqlDatabase db;//База данных
    QString qsDatabaseName = "/data/audiobooks.db";//Имя базы данных
    QString qsTableName = "books";//Имя таблицы базы данных

    QString qsAuthor = "";
    QString qsSerial = "";
    QString qsVolume = "";
    QString qsBook = "";
    int iIncludionCount = 0;

public:
    static QString qsApplicationPath;

    //Конструкторы и деструкторы
    explicit cSqliteDriver(QTableView * table_view, QTextBrowser* text_browser_log, QGroupBox * groub_box_incoming, QComboBox * history, QObject *parent = 0);
    ~cSqliteDriver();

    //Методы
    bool openDatabase();
    bool closeDatabase();
    bool dropTable();
    bool createTable();
    bool insertRecord(std::tuple<QString, QString, QString, QString> data);
    bool selectAllAndShow();
    bool selectAllAndViewInTable();
    bool execRequest();
    void showSelectionResult(QSqlQuery query);
    QString getAuthor();
    QString getSerial();
    QString getVolume();
    QString getName();
    bool setAuthor();
    bool setSerial();
    bool setVolume();
    bool setName();
    bool storeRequestHistory();
    bool storeAuthorsList();
    bool getAuthorList();
    bool checkDataIncludion();

signals:

public slots:
    void onTableViewClicked(const QModelIndex &index);
    void onTableViewActivated(int logical_row);
    void onHistoryIndexChanged(int index);
    void showMessage(QString s);
    void execSetDataString(QString s);
};

#endif // CSQLITEDRIVER_H
