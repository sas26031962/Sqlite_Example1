#include "cexternaldata.h"

cExternalData::cExternalData(QGroupBox *group_box_parent, QObject *parent) : QObject(parent)
{
    gbParent = group_box_parent;

    QHBoxLayout * layout = new QHBoxLayout(gbParent);

    int Height = 20;
    int ButtonWidth = Height;

    leCurrentString = new QLineEdit(gbParent);
    leCurrentString->setText("Current_data_text");
    leCurrentString->setMinimumHeight(Height);
    leCurrentString->setMaximumHeight(Height);

    pbPrevious = new QPushButton(gbParent);
    pbPrevious->setText("<");
    pbPrevious->setMinimumHeight(Height);
    pbPrevious->setMaximumHeight(Height);
    pbPrevious->setMinimumWidth(ButtonWidth);
    pbPrevious->setMaximumWidth(ButtonWidth);
    pbPrevious->setCursor(Qt::PointingHandCursor);

    pbNext = new QPushButton(gbParent);
    pbNext->setText(">");
    pbNext->setMinimumHeight(Height);
    pbNext->setMaximumHeight(Height);
    pbNext->setMinimumWidth(ButtonWidth);
    pbNext->setMaximumWidth(ButtonWidth);
    pbNext->setCursor(Qt::PointingHandCursor);

    pbStore = new QPushButton(gbParent);
    pbStore->setText("S");
    pbStore->setMinimumHeight(Height);
    pbStore->setMaximumHeight(Height);
    pbStore->setMinimumWidth(ButtonWidth);
    pbStore->setMaximumWidth(ButtonWidth);
    pbStore->setCursor(Qt::PointingHandCursor);

    layout->addWidget(pbPrevious);
    layout->addWidget(pbNext);
    layout->addWidget(leCurrentString);
    layout->addWidget(pbStore);

    int Margin = 3;
    layout->setContentsMargins(Margin, Margin, Margin, Margin);

    qsFullPath = cSqliteDriver::qsApplicationPath + DataFileName;
    qslData = cLoadFiles::loadStringListFromFile(qsFullPath);
    int DataLinesCount = qslData.count();
    qDebug() << "Load from file: " << DataLinesCount << " lines";
    if(DataLinesCount > 0)
    {
        leCurrentString->setText(qslData.at(DataIndex));
        emit setDataString(qslData.at(DataIndex));

        connect(pbPrevious, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
            qDebug() << "PushButton 'Previous' click";
              DataIndex--;
              if(DataIndex < 0) DataIndex = 0;
              leCurrentString->setText(qslData.at(DataIndex));
              emit setDataString(qslData.at(DataIndex));
              emit setStatus("Previous click:" + QString::number(DataIndex));
        });

        connect(pbNext, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
            qDebug() << "PushButton 'Next' click";
              DataIndex++;
              if(DataIndex == qslData.count()) DataIndex = qslData.count() - 1;
              leCurrentString->setText(qslData.at(DataIndex));
              emit setDataString(qslData.at(DataIndex));
              emit setStatus("Next click:" + QString::number(DataIndex));
        });

        connect(pbStore, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
            qDebug() << "PushButton 'Store' click, line=" << DataIndex;
            qslData[DataIndex] = leCurrentString->text();
            bool x = cLoadFiles::saveStringListToFile(qsFullPath, qslData);
            QString qsMessage = "ExternalData > ";
            if(x)
            {
                qsMessage += "Store line:" + QString::number(DataIndex);
            }
            else
            {
                qsMessage += "Can't store line:";
            }
            emit setStatus(qsMessage);

        });
    }
    else
    {
        emit closeMainProgramm();
    }
}

cExternalData::~cExternalData()
{

}
