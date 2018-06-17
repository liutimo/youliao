#include "ylimageeditwidget.h"
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QScrollBar>
#include <QPainter>
YLImageEditWidget::YLImageEditWidget(QWidget *parent) : QScrollArea(parent), m_left_pressed(false), m_loop(false)
{
    imageWidget  = new ImageWidget;
    setWidget(imageWidget);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    m_x_offest = m_y_offest = 0;
}


void YLImageEditWidget::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    imageWidget->setPixmap(m_pixmap);
    update();
}

void  YLImageEditWidget::leftRotate()
{
    QMatrix matrix;
    matrix.rotate(-90.0);
    m_pixmap = m_pixmap.transformed(matrix, Qt::SmoothTransformation);

    imageWidget->setPixmap(m_pixmap);
    update();
    qDebug() << "左旋转90度";
}

void  YLImageEditWidget::rightRotate()
{
    QMatrix matrix;
    matrix.rotate(90.0);
    m_pixmap = m_pixmap.transformed(matrix, Qt::SmoothTransformation);

    imageWidget->setPixmap(m_pixmap);
    update();


    horizontalScrollBar()->setValue(horizontalScrollBar()->maximum() - m_h_value);
    verticalScrollBar()->setValue(verticalScrollBar()->maximum() - m_v_value);
    qDebug() << "右旋转90度";
}

void YLImageEditWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_h_value = horizontalScrollBar()->value();
        m_v_value = verticalScrollBar()->value();
        m_left_pressed = false;
    }

    event->accept();
}

void YLImageEditWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_left_pressed = true;
        m_pressed_x = event->pos().x();
        m_pressed_y = event->pos().y();
    }

//    QScrollArea::mousePressEvent(event);
    event->accept();
}

void YLImageEditWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_left_pressed)
    {
        m_x_offest = event->pos().x() - m_pressed_x;
        m_y_offest = event->pos().y() - m_pressed_y;

        horizontalScrollBar()->setValue(m_h_value - m_x_offest);
        verticalScrollBar()->setValue(m_v_value - m_y_offest);
    }

//    QScrollArea::mouseMoveEvent(event);
    event->accept();
}

void YLImageEditWidget::paintEvent(QPaintEvent *event)
{
//    QPainter p(this->viewport());
//    p.drawPixmap(0, 0, 350, 350, QPixmap(":/res/headicon/CircleMask.png").scaled(350, 350, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

/***************************************华丽的分割线***********************************/

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{

}

//设置图片
void ImageWidget::setPixmap(const QString &fileName)
{
    m_pixmap = QPixmap(fileName);
    resize(m_pixmap.size());
    update();
}

void ImageWidget::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    resize(m_pixmap.size());
    update();
}

void ImageWidget::zoomInPixmap()
{

}

void ImageWidget::zoomOutPixmap()
{

}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.drawPixmap(rect(), m_pixmap);
}
