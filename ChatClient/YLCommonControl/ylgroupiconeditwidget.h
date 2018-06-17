#ifndef YLGROUPICONEDITWIDGET_H
#define YLGROUPICONEDITWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"


class YLGroupIconEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLGroupIconEditWidget(QWidget *parent = nullptr);

signals:

public slots:

};

class YLDragWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLDragWidget(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *event);

};

#endif // YLGROUPICONEDITWIDGET_H
