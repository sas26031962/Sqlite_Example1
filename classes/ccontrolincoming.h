#ifndef CCONTROLINCOMING_H
#define CCONTROLINCOMING_H

#include <QObject>
#include <QString>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QClipboard>
#include <QApplication>


class cControlIncoming : public QObject
{
    Q_OBJECT

    //Атрибуты
    QGroupBox * gbParent;
    QLabel * lbAuthor;
    QLabel * lbSerial;
    QLabel * lbVolume;
    QLabel * lbName;

    QLineEdit * leAuthor;
    QLineEdit * leSerial;
    QLineEdit * leVolume;
    QLineEdit * leName;

    QLineEdit * leRequest;

public:
    //Конструкторы и деструкторы
    explicit cControlIncoming(QGroupBox * group_box_parent, QObject *parent = 0);
    ~cControlIncoming();

    //Методы
    QString getRequest();
    QString getAuthor();
    QString getSerial();
    QString getVolume();
    QString getName();

    void setAuthor(QString s);
    void setSerial(QString s);
    void setVolume(QString s);
    void setName(QString s);
    void setRequest(QString s);

    void setAuthorFromClipboard();
    void setSerialFromClipboard();
    void setVolumeFromClipboard();
    void setNameFromClipboard();

signals:

public slots:
};

#endif // CCONTROLINCOMING_H
