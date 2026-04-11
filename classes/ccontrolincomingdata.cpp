#include "ccontrolincomingdata.h"

cControlIncomingData::cControlIncomingData(
        QGroupBox *group_box_parent,
        QObject *parent
        ) : QObject(parent)
{
    GroupBoxParent = group_box_parent;

     QGridLayout *gridLayout = new QGridLayout(GroupBoxParent);

     QLabel * qlAuthor = new QLabel("Author");
     qlAuthor->setAlignment(Qt::AlignCenter);

     QLineEdit * leAuthor = new QLineEdit;
     leAuthor->setText("Author_name");

     QLabel * qlSerial = new QLabel("Serial");
     qlSerial->setAlignment(Qt::AlignCenter);

     QLineEdit * leSerial = new QLineEdit;
     leSerial->setText("Serial_name");

     QLabel * qlName = new QLabel("Name");
     qlName->setAlignment(Qt::AlignCenter);

     QLineEdit * leName = new QLineEdit;
     leName->setText("Book_name");

     // Размещаем: label и поле ввода в одной строке, label слева, поле справа
     gridLayout->addWidget(qlAuthor, 0, 0);
     gridLayout->addWidget(qlSerial, 0, 1);
     gridLayout->addWidget(qlName, 0, 2);
     gridLayout->addWidget(leAuthor, 1, 0);
     gridLayout->addWidget(leSerial, 1, 1);
     gridLayout->addWidget(leName, 1, 2);

}

cControlIncomingData::~cControlIncomingData()
{

}
