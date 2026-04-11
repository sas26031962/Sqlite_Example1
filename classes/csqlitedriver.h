#ifndef CSQLITEDRIVER_H
#define CSQLITEDRIVER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QDebug>
#include <QTableView>
#include <QTextBrowser>
#include <QGroupBox>
#include <tuple>

#include "classes/ccontrolincomingdata.h"

class cSqliteDriver : public QObject
{
    Q_OBJECT

    //Атрибуты
    QString qsName = "SqliteDriver";
    QString qsMessage;
    QString qsDatabaseName = "audiobooks.db";

    QTableView * TableView;
    QTextBrowser * TextBrowser;
    QGroupBox * GroupBoxIncoming;

public:
    cControlIncomingData * ControlIncomingData;
    QString qsTableName = "books";

    QSqlDatabase db;

    //Конструкторы и деструкторы
    explicit cSqliteDriver(
            QTableView * table_view,
            QTextBrowser * text_browser,
            QGroupBox * group_box_incoming,
            QObject *parent = 0
            );
    ~cSqliteDriver();

    //Методы
    bool openDatabase();
    bool closeDatabase();
    bool dropTable();
    bool createTable();
    bool insertRecord(std::tuple<QString, QString, QString> data);
    bool selectAllAndShow();
    bool selectAllAndViewInTable();
    void showSelectionResult(QSqlQuery query);

signals:

public slots:
};

#endif // CSQLITEDRIVER_H
