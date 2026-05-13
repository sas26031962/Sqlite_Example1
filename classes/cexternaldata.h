#ifndef CEXTERNALDATA_H
#define CEXTERNALDATA_H

#include <QObject>
#include <QString>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QStringList>
#include <QClipboard>
#include <QApplication>

#include "classes/cloadfiles.h"
#include "classes/csqlitedriver.h"

class cExternalData : public QObject
{
    Q_OBJECT

    //Атрибуты
    QGroupBox * gbParent;

    QLineEdit * leCurrentString;
    QPushButton * pbPrevious;
    QPushButton * pbNext;
    QPushButton * pbStore;
    QStringList qslData;
    int DataIndex = 0;

    QString qsFullPath;
    QString DataFileName = "/data/ExternalText.txt";

public:
    explicit cExternalData(QGroupBox * group_box_parent, QObject *parent = 0);
    ~cExternalData();

signals:
    void closeMainProgramm();
    void setStatus(QString s);
    void setDataString(QString s);

public slots:
};

#endif // CEXTERNALDATA_H
