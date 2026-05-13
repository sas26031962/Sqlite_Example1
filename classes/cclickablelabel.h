#ifndef CCLICKABLELABEL_H
#define CCLICKABLELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class cClickAbleLabel : public QLabel
{
    Q_OBJECT
public:
    explicit cClickAbleLabel(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void clicked();

public slots:

};

#endif // CCLICKABLELABEL_H
