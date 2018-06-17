#include "ylgroupiconeditwidget.h"
#include <QPainter>

YLGroupIconEditWidget::YLGroupIconEditWidget(QWidget *parent) : QWidget(parent)
{
}



YLDragWidget::YLDragWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    resize(400, 400);
}

void YLDragWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);


    int w = width();
    qreal cw = w / 3.0;
    qreal mid = w / 2.0;
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(255, 255, 255, 100));
    p.drawRect(rect());



    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setColor(Qt::white);
    pen.setWidth(1);
    p.setPen(pen);

    p.drawLine(cw, 0, cw, w);
    p.drawLine(cw * 2, 0, cw * 2, w);
    p.drawLine(0, cw, w, cw);
    p.drawLine(0, cw * 2, w, cw * 2);


    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor::fromRgb(10, 124, 202));
    pen.setWidth(2);
    p.setPen(pen);      //#0A7CCA
    w = w - 4;
    p.drawLine(2, 2, w, 2);
    p.drawLine(w, 2, w, w);
    p.drawLine(w, w, 2, w);
    p.drawLine(2, w, 2, 2);

    p.drawEllipse(0, 0, 4, 4);

    p.drawEllipse(w, w, w + 4, w + 4);
}
