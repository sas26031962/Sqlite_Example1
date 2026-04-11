#include "csqlitedriver.h"

cSqliteDriver::cSqliteDriver(
        QTableView *table_view,
        QTextBrowser *text_browser,
        QGroupBox *group_box_incoming,
        QObject *parent
        ) : QObject(parent)
{
    TableView = table_view;
    TextBrowser = text_browser;
    GroupBoxIncoming = group_box_incoming;

    ControlIncomingData = new cControlIncomingData(GroupBoxIncoming);

    qDebug() << "Accessable drivers: " << QSqlDatabase::drivers();
    qDebug() << "cSqliteDriver ctor";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qsDatabaseName);
}

cSqliteDriver::~cSqliteDriver()
{
    qDebug() << "cSqliteDriver dector";

}

bool cSqliteDriver::openDatabase()
{
    bool x = db.open();
    qsMessage = qsName;
    qsMessage += " > Open ";
    qsMessage += qsDatabaseName;
    if (x)
    {
        qsMessage += " database success.";
    }
    else
    {
        qsMessage += " error:";
        qsMessage += db.lastError().text();
    }
    qDebug() << qsMessage;
    TextBrowser->append(qsMessage);

    return x;
}

bool cSqliteDriver::closeDatabase()
{
    db.close();
    qsMessage = qsName;
    qsMessage += " > Connection close.";

    qDebug() << qsMessage;
    TextBrowser->append(qsMessage);

    return true;
}

bool cSqliteDriver::dropTable()
{
    bool x = true;

    QString qsDropTable = "";
    qsDropTable += "DROP TABLE IF EXISTS ";
    qsDropTable += qsTableName;

    QSqlQuery query;
    x = query.exec(qsDropTable);
    qsMessage = qsName;
    qsMessage += " > Drop table ";
    if(x)
    {
        qsMessage += qsTableName;
        qsMessage += " complete.";
    }
    else
    {
        qsMessage += "error:";
        qsMessage += query.lastError().text();
    }
    qDebug() << qsMessage;
    TextBrowser->append(qsMessage);

    return x;
}

bool cSqliteDriver::createTable()
{
    QString qsRequestCreateTable = "";
    qsRequestCreateTable += "CREATE TABLE IF NOT EXISTS ";
    qsRequestCreateTable += qsTableName;                                //Имя таблицы
    qsRequestCreateTable += " (";
    qsRequestCreateTable += "id";                                       //Id
    qsRequestCreateTable += " INTEGER PRIMARY KEY AUTOINCREMENT, ";
    qsRequestCreateTable += "author";                                   //Автор
    qsRequestCreateTable += " TEXT NOT NULL, ";
    qsRequestCreateTable += "serial";                                   //Серия
    qsRequestCreateTable += " TEXT, ";
    qsRequestCreateTable += "name";                                     //Название
    qsRequestCreateTable += " TEXT NOT NULL)";

    QSqlQuery query;

    bool x = query.exec(qsRequestCreateTable);

    qsMessage = qsName;
    qsMessage += " > Create table: ";
    qsMessage += qsTableName;
    if(x)
    {
        qsMessage += " is ready.";
    }
    else
    {
        qsMessage += " error:";
        qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    TextBrowser->append(qsMessage);

    return x;
}
bool cSqliteDriver::insertRecordInstant()
{
    auto t1 = std::make_tuple(
        ControlIncomingData->leAuthor->text(),
        ControlIncomingData->leSerial->text(),
        ControlIncomingData->leName->text()
        );

    return insertRecord(t1);
}

bool cSqliteDriver::insertRecord(std::tuple<QString, QString, QString> data)
{
    QString qsInsertData = "";
    qsInsertData += "INSERT INTO ";
    qsInsertData += qsTableName;
    qsInsertData += " (author, serial, name) VALUES (:author, :serial, :name)";

    qDebug() << "InsertRecord> data: Author=" << std::get<0>(data) << " Serial=" << std::get<1>(data) << " Book=" << std::get<2>(data);
    QSqlQuery query;
    query.prepare(qsInsertData);
    query.bindValue(":author", std::get<0>(data));//"AuthorName"
    query.bindValue(":serial", std::get<1>(data));//"SerialName"
    query.bindValue(":name", std::get<2>(data));//"BookName"

    bool x = query.exec();
    qsMessage = qsName;
    qsMessage += " > Insert data to the table ";
    qsMessage += qsTableName;
    qsMessage += ": Data insert";
    if (x)
    {
        QSqlQuery query;
        QString qsSelecCount = "SELECT COUNT(*) FROM ";
        qsSelecCount += qsTableName;
        query.exec(qsSelecCount);
        int rowCount = 0;
        if (query.next())
        {
            rowCount = query.value(0).toInt();

            qsMessage += " success!";
            qsMessage += " RowCount=";
            qsMessage += QString::number(rowCount);
        }
        else
        {
            x = false;
        }
    }
    else
    {
        qsMessage +=  " error:";
        qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    TextBrowser->append(qsMessage);

    return x;
}

bool cSqliteDriver::selectAllAndShow()
{
    QString qsSelectData = "";
    qsSelectData += "SELECT id, author, serial, name FROM ";
    qsSelectData += qsTableName;

    QSqlQuery query;

    bool x = query.exec(qsSelectData);

    qsMessage = qsName;
    qsMessage += " > Select data from the table ";
    qsMessage += qsTableName;
    qsMessage += ": Data select";
    if (x)
    {
        qsMessage += " success!";
        //---
        showSelectionResult(query);
        //---
    }
    else
    {
        qsMessage +=  " error:";
        qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    TextBrowser->append(qsMessage);

    return x;
}

bool cSqliteDriver::selectAllAndViewInTable()
{
    QString qsSelectData = "";
    qsSelectData += "SELECT author, serial, name FROM ";
    qsSelectData += qsTableName;

    QSqlQueryModel * model = new QSqlQueryModel();

    bool x;

    model->setQuery(qsSelectData);
    if (model->lastError().isValid())
    {
        qCritical() << model->lastError().text();
        x = false;
    }
    else
    {
        x = true;
        qDebug() << "SelectAllAndViewInTable > Model rows count=" << model->rowCount();
        for (int row = 0; row < model->rowCount(); ++row)
        {
            QSqlRecord record = model->record(row);
            QString qsAuthor = record.value("author").toString();
            QString qsSerial = record.value("serial").toString();
            QString qsBook = record.value("name").toString();
            qDebug() << "Row:" << row << " Data=" << qsAuthor << qsSerial << qsBook;
        }

        TableView->setModel(model);
        TableView->show();
    }
    qsMessage = qsName;
    qsMessage += " > Select data from the table ";
    qsMessage += qsTableName;
    qsMessage += ": Data select";
    if (x)
    {
        qsMessage += " success!";
        //---
        //showSelectionResult(query);
        //---
    }
    else
    {
        qsMessage +=  " error:";
        //qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    TextBrowser->append(qsMessage);

    return x;
}

void cSqliteDriver::showSelectionResult(QSqlQuery query)
{
    qDebug() << "\nBooks list:";
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString author = query.value(1).toString();
        QString serial = query.value(2).toString();
        QString name = query.value(3).toString();
        qDebug() << "ID:" << id << ", Author:" << author << ", Serial:" << serial <<", Name:" << name;
    }
}

