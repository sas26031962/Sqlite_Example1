#include "csqlitedriver.h"

QString cSqliteDriver::qsApplicationPath = "";

cSqliteDriver::cSqliteDriver(
        QTableView *table_view,
        QTextBrowser *text_browser_log,
        QGroupBox * groub_box_incoming,
        QComboBox *history,
        QObject *parent
        ) : QObject(parent)
{
    TableView = table_view;
    tbLog = text_browser_log;
    gbIncoming = groub_box_incoming;
    cbHistory = history;

    VerticalHeader = TableView->verticalHeader();
    HorizontalHeader = TableView->horizontalHeader();
    HorizontalHeader->setSectionResizeMode(QHeaderView::Stretch);

    connect(TableView, &QTableView::clicked, this, &cSqliteDriver::onTableViewClicked);
    connect(VerticalHeader, &QHeaderView::sectionClicked, this, &cSqliteDriver::onTableViewActivated);
    connect(cbHistory, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &cSqliteDriver::onHistoryIndexChanged);

    ControlIncoming = new cControlIncoming(gbIncoming);

    qDebug() << "Accessable drivers: " << QSqlDatabase::drivers();
    qDebug() << "cSqliteDriver ctor";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qsApplicationPath + qsDatabaseName);

    qslRequests = cLoadFiles::loadStringListFromFile(qsApplicationPath + qsRequestsFileName);

    qsMessage = "SqliteDriver > Load from ";
    qsMessage += qsApplicationPath + qsRequestsFileName;
    qsMessage += " ";
    qsMessage += QString::number(qslRequests.count());
    qsMessage += " lines";
    qDebug() << qsMessage;
    showMessage(qsMessage);

    cbHistory->addItems(qslRequests);
    if(qslRequests.count() > 0) ControlIncoming->setRequest(qslRequests.at(0));
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
    qsMessage += qsApplicationPath + qsDatabaseName;
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
    showMessage(qsMessage);

    return x;
}

bool cSqliteDriver::closeDatabase()
{
    db.close();
    qsMessage = qsName;
    qsMessage += " > Connection close.";
    qDebug() << qsMessage;
    showMessage(qsMessage);

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
    showMessage(qsMessage);

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
    showMessage(qsMessage);

    return x;
}

bool cSqliteDriver::insertRecord(std::tuple<QString, QString, QString, QString> data)
{
    QString qsInsertData = "";
    qsInsertData += "INSERT INTO ";
    qsInsertData += qsTableName;
    qsInsertData += " (author, serial, volume, name) VALUES (:author, :serial, :volume, :name)";

    qDebug() << "InsertRecord> data: Author=" << std::get<0>(data) << " Serial=" << std::get<1>(data) << " Book=" << std::get<2>(data);
    QSqlQuery query;
    query.prepare(qsInsertData);
    query.bindValue(":author", std::get<0>(data));//"AuthorName"
    query.bindValue(":serial", std::get<1>(data));//"SerialName"
    query.bindValue(":volume", std::get<2>(data));//"VolumeName"
    query.bindValue(":name", std::get<3>(data));//"BookName"

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
    showMessage(qsMessage);

    return x;
}

bool cSqliteDriver::selectAllAndShow()
{
    QString qsSelectData = "";
    qsSelectData += "SELECT id, author, serial, name FROM ";
    qsSelectData += qsTableName;
    qsSelectData += ";";

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
    showMessage(qsMessage);

    return x;
}

bool cSqliteDriver::selectAllAndViewInTable()
{
    QString qsSelectData = "";
    qsSelectData += "SELECT author, serial, volume, name FROM ";
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
            QString qsVolume = record.value("volume").toString();
            QString qsBook = record.value("name").toString();
            qDebug() << qsAuthor << qsSerial << qsVolume << qsBook;
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
    showMessage(qsMessage);

    return x;
}

bool cSqliteDriver::execRequest()
{
    QString qsExecRequest = ControlIncoming->getRequest();

    qsMessage = qsName;
    if(qslRequests.contains(qsExecRequest))
    {
        qsMessage += " > contains this request";
    }
    else
    {
        qslRequests.append(qsExecRequest);
        qsMessage += " > append this request";
        cbHistory->addItem(qsExecRequest);
    }
    qDebug() << qsMessage;
    showMessage(qsMessage);

    QSqlQueryModel * model = new QSqlQueryModel();

    bool x;

    model->setQuery(qsExecRequest);
    if (model->lastError().isValid())
    {
        qCritical() << model->lastError().text();
        x = false;
    }
    else
    {
        x = true;
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
    }
    else
    {
        qsMessage +=  " error:";
        qsMessage += model->lastError().text();
    }

    qDebug() << qsMessage;
    showMessage(qsMessage);

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
        QString volume = query.value(3).toString();
        QString name = query.value(4).toString();
        qDebug() << "ID:" << id << ", Author:" << author << ", Serial:" << serial << ", Volume:" << volume << ", Name:" << name;
    }
}

QString cSqliteDriver::getAuthor()
{
    return ControlIncoming->getAuthor();
}

QString cSqliteDriver::getSerial()
{
    return ControlIncoming->getSerial();
}

QString cSqliteDriver::getVolume()
{
    return ControlIncoming->getVolume();
}

QString cSqliteDriver::getName()
{
    return ControlIncoming->getName();
}

void cSqliteDriver::onTableViewClicked(const QModelIndex &index)
{
    QString Message = "TableViewClicked > ";
    if(index.isValid())
    {
        QString data = index.data().toString();
        int row = index.row();
        int col = index.column();

        Message += "Data=";
        Message += data;
        Message += " Row=";
        Message += QString::number(row);
        Message += " Column=";
        Message += QString::number(col);
        //qDebug() << "Clicked:" << data << " row=" << row << " col" << col;

        switch(col)
        {
            case 0:
                ControlIncoming->setAuthor(data);
            break;

            case 1:
                ControlIncoming->setSerial(data);
            break;

            case 2:
                ControlIncoming->setVolume(data);
            break;

            case 3:
                ControlIncoming->setName(data);
            break;

            default:
                Message += "Wrong row index:";
                Message += QString::number(col);
            break;
        }
    }
    else
    {
        Message += "Model index is not valid";
    }
    showMessage(qsMessage);
}

void cSqliteDriver::onTableViewActivated(int logical_row)
{
    //qDebug() << "TableViewActivated" << logical_row;

    // Получаем данные из модели
    QAbstractItemModel *model = TableView->model();
        if (!model) return;

        // Например, читаем ID из первого столбца
        QModelIndex idIndex = model->index(logical_row, 0);
        int id = model->data(idIndex).toInt();

        QString author = model->data(model->index(logical_row, 0)).toString();
        QString serial = model->data(model->index(logical_row, 1)).toString();
        QString volume = model->data(model->index(logical_row, 2)).toString();
        QString name = model->data(model->index(logical_row, 3)).toString();

        qDebug() << "Выбрана запись> " << id << " Author:" << author << " Serial: " << serial << " Volume: " << volume << " Name:" << name;

        ControlIncoming->setAuthor(author);
        ControlIncoming->setSerial(serial);
        ControlIncoming->setVolume(volume);
        ControlIncoming->setName(name);
}

bool cSqliteDriver::setAuthor()
{
    qDebug() << "SqliteDriver: setAuthor()";
    ControlIncoming->setAuthorFromClipboard();
    return true;
}

bool cSqliteDriver::setSerial()
{
    qDebug() << "SqliteDriver: setSerial()";
    ControlIncoming->setSerialFromClipboard();
    return true;
}

bool cSqliteDriver::setVolume()
{
    qDebug() << "SqliteDriver: setVolume()";
    ControlIncoming->setVolumeFromClipboard();
    return true;
}

bool cSqliteDriver::setName()
{
    qDebug() << "SqliteDriver: setName()";
    ControlIncoming->setNameFromClipboard();
    return true;
}

bool cSqliteDriver::storeRequestHistory()
{
    return cLoadFiles::saveStringListToFile(qsApplicationPath + qsRequestsFileName, qslRequests);
}

bool cSqliteDriver::storeAuthorsList()
{
    return cLoadFiles::saveStringListToFile(qsApplicationPath + qsAuthorsFileName, qslAuthors);
}

void cSqliteDriver::onHistoryIndexChanged(int index)
{
    qDebug() << "SqligeDriver > History index changed: " << index;
    ControlIncoming->setRequest(qslRequests.at(index));
}

bool cSqliteDriver::getAuthorList()
{
    QString qsAuthorListRequest = "";
    qsAuthorListRequest += "SELECT id, author FROM ";
    qsAuthorListRequest += qsTableName;

    QSqlQueryModel * model = new QSqlQueryModel();

    bool x;

    model->setQuery(qsAuthorListRequest);
    if (model->lastError().isValid())
    {
        qCritical() << model->lastError().text();
        x = false;
    }
    else
    {
        x = true;
        qDebug() << "GetAuthorListRequest > Model rows count=" << model->rowCount();
        qslAuthors.clear();
        for (int row = 0; row < model->rowCount(); ++row)
        {
            QSqlRecord record = model->record(row);
            int Id = record.value("id").toInt();
            QString qsAuthor = record.value("author").toString();
            qDebug() << Id << qsAuthor;
            if(qslAuthors.contains(qsAuthor))
            {
                qsMessage += " > contains this author";
            }
            else
            {
                qslAuthors.append(qsAuthor);
                qsMessage += " > append this author";
            }

        }

        TableView->setModel(model);
        TableView->show();
    }
    qsMessage = qsName;
    qsMessage += " > GetAuthorListRequest: length = ";
    qsMessage += QString::number(qslAuthors.count());
    if (x)
    {
        qsMessage += " success!";
    }
    else
    {
        qsMessage +=  " error";
        //qsMessage += ": ";
        //qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    showMessage(qsMessage);

    return x;
}

void cSqliteDriver::showMessage(QString s)
{
    tbLog->append(s);

}

void cSqliteDriver::execSetDataString(QString s)
{
    qDebug() << qsName << " > Full data string = " << s;
    int iLeftBracketStquareIndex = s.indexOf('[');
    QString qsData = s.mid(0, iLeftBracketStquareIndex - 1);
    qDebug() << qsName << " > Left data string = " << qsData;

    int iDashIndex = s.indexOf(" - ");
    int iDotIndex = s.indexOf('.');
    int iOctothorpe = s.indexOf('#');
    qsAuthor = qsData.mid(0, iDashIndex);
    if(iDotIndex > 0)
    {
        qsSerial = qsData.mid(iDashIndex + 3, iDotIndex - iDashIndex - 3);
        if(iOctothorpe < 0)
        {
            qsVolume = "";
            qsBook = qsData.mid(iDotIndex + 2);
        }
        else
        {
            qsVolume = qsData.mid(iOctothorpe + 1, 2);
            qsBook = qsData.mid(iOctothorpe + 4);
        }
    }
    else
    {
        qsBook = qsData.mid(iDashIndex + 3);
        qsSerial = "";
        qsVolume = "";
    }
    qDebug() << qsName << " > Author = " << qsAuthor << " Serial = " << qsSerial << " Name = " << qsBook;
    ControlIncoming->setAuthor(qsAuthor);
    ControlIncoming->setSerial(qsSerial);
    ControlIncoming->setVolume(qsVolume);
    ControlIncoming->setName(qsBook);

    checkDataIncludion();
}

bool cSqliteDriver::checkDataIncludion()
{
    QString qsExecRequest = "SELECT author, serial, volume, name from ";
    qsExecRequest += qsTableName;
    qsExecRequest += " WHERE ";
    qsExecRequest += "author";
    qsExecRequest += " = '";
    qsExecRequest += qsAuthor;
    qsExecRequest += "' AND ";
    qsExecRequest += "serial";
    qsExecRequest += " = '";
    qsExecRequest += qsSerial;
    qsExecRequest += "' AND ";
    qsExecRequest += "volume";
    qsExecRequest += " = '";
    qsExecRequest += qsVolume;
    qsExecRequest += "' AND ";
    qsExecRequest += "name";
    qsExecRequest += " = '";
    qsExecRequest += qsBook;
    qsExecRequest += "';";

    qDebug() << "CheckDataInclusion: request = " << qsExecRequest;

    qsMessage = qsName;
    if(qslRequests.contains(qsExecRequest))
    {
        qsMessage += " > contains this request";
    }
    else
    {
        qslRequests.append(qsExecRequest);
        qsMessage += " > append this request";
        cbHistory->addItem(qsExecRequest);
    }
    qDebug() << qsMessage;
    showMessage(qsMessage);

    QSqlQueryModel * model = new QSqlQueryModel();

    bool x;

    model->setQuery(qsExecRequest);
    if (model->lastError().isValid())
    {
        qCritical() << model->lastError().text();
        x = false;
    }
    else
    {
        x = true;
        TableView->setModel(model);
        TableView->show();
    }
    qsMessage = qsName;
    qsMessage += " > Select data from the table ";
    qsMessage += qsTableName;
    qsMessage += ": Data select";
    if (x)
    {
        qsMessage += " success, rows count=";
        qsMessage += QString::number(model->rowCount());
    }
    else
    {
        qsMessage +=  " error:";
        qsMessage += model->lastError().text();
    }

    qDebug() << qsMessage;
    showMessage(qsMessage);

    return x;

}//End of void cSqliteDriver::checkDataIncludion()
