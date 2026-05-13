#include "cclickablelabel.h"

cClickAbleLabel::cClickAbleLabel(QWidget *parent) : QLabel(parent)
{

}

void cClickAbleLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) emit clicked();
}
