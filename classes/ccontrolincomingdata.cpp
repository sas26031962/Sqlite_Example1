#include "ccontrolincomingdata.h"

cControlIncomingData::cControlIncomingData(
        QGroupBox *group_box_parent,
        QObject *parent
        ) : QObject(parent)
{
    GroupBoxParent = group_box_parent;
}

cControlIncomingData::~cControlIncomingData()
{

}
