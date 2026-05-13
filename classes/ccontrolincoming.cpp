#include "ccontrolincoming.h"

cControlIncoming::cControlIncoming(QGroupBox *group_box_parent, QObject *parent) : QObject(parent)
{
    gbParent = group_box_parent;

    QGridLayout * layout = new QGridLayout(gbParent);

    lbAuthor = new QLabel(gbParent);
    lbAuthor->setText("Author");
    lbAuthor->setAlignment(Qt::AlignCenter);
    lbAuthor->setCursor(Qt::PointingHandCursor);

    lbSerial = new QLabel(gbParent);
    lbSerial->setText("Serial");
    lbSerial->setAlignment(Qt::AlignCenter);
    lbSerial->setCursor(Qt::PointingHandCursor);

    lbVolume = new QLabel(gbParent);
    lbVolume->setText("Volume");
    lbVolume->setAlignment(Qt::AlignCenter);
    lbVolume->setCursor(Qt::PointingHandCursor);

    lbName = new QLabel(gbParent);
    lbName->setText("Name");
    lbName->setAlignment(Qt::AlignCenter);
    lbName->setCursor(Qt::PointingHandCursor);

    leAuthor = new QLineEdit(gbParent);
    leAuthor->setText("Author_text");

    leSerial = new QLineEdit(gbParent);
    leSerial->setText("Serial_text");

    leVolume = new QLineEdit(gbParent);
    leVolume->setText("Volume_text");

    leName = new QLineEdit(gbParent);
    leName->setText("Name_text");

    leRequest = new QLineEdit(gbParent);
    leRequest->setText("Request_text");

    layout->addWidget(lbAuthor, 0,0);
    layout->addWidget(lbSerial, 0,1);
    layout->addWidget(lbVolume, 0,2);
    layout->addWidget(lbName, 0,3);

    layout->addWidget(leAuthor, 1,0);
    layout->addWidget(leSerial, 1,1);
    layout->addWidget(leVolume, 1,2);
    layout->addWidget(leName, 1,3);

    layout->addWidget(leRequest, 2,0,1,4);

    int Margin = 3;
    layout->setContentsMargins(Margin, Margin, Margin, Margin);
}

cControlIncoming::~cControlIncoming()
{

}

QString cControlIncoming::getRequest()
{
    return leRequest->text();
}


QString cControlIncoming::getAuthor()
{
    return leAuthor->text();
}

QString cControlIncoming::getSerial()
{
    return leSerial->text();
}

QString cControlIncoming::getVolume()
{
    return leVolume->text();
}

QString cControlIncoming::getName()
{
    return leName->text();
}

void cControlIncoming::setAuthor(QString s)
{
    leAuthor->setText(s);
}

void cControlIncoming::setSerial(QString s)
{
    leSerial->setText(s);
}

void cControlIncoming::setVolume(QString s)
{
    leVolume->setText(s);
}

void cControlIncoming::setName(QString s)
{
    leName->setText(s);
}

void cControlIncoming::setAuthorFromClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString textFromClipboard = clipboard->text();
    leAuthor->setText(textFromClipboard);
}

void cControlIncoming::setSerialFromClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString textFromClipboard = clipboard->text();
    leSerial->setText(textFromClipboard);
}

void cControlIncoming::setVolumeFromClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString textFromClipboard = clipboard->text();
    leVolume->setText(textFromClipboard);
}

void cControlIncoming::setNameFromClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString textFromClipboard = clipboard->text();
    leName->setText(textFromClipboard);
}

void cControlIncoming::setRequest(QString s)
{
    leRequest->setText(s);
}
