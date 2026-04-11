#ifndef CCONTROLINCOMINGDATA_H
#define CCONTROLINCOMINGDATA_H

#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QGridLayout>

class cControlIncomingData : public QObject
{
    Q_OBJECT
public:
    //Аргументы
    QGroupBox * GroupBoxParent;

    //Конструкторы и деструкторы
    explicit cControlIncomingData(QGroupBox * group_box_parent, QObject *parent = 0);
    ~cControlIncomingData();

    //Методы

signals:

public slots:
};

#endif // CCONTROLINCOMINGDATA_H
