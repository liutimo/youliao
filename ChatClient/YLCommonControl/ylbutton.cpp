#include "ylbutton.h"
#include <QPainter>
#include <QMouseEvent>
YLButton::YLButton(QWidget *parent) : QPushButton(parent), m_clicked(false), m_has_menu(false)
{
    setStyleSheet("QPushButton{border:0px;}QPushButton:hover{background:#CFCFCF;;}");
}


void YLButton::setImage(const QString &image)
{
    m_pixmap = QPixmap(image);
    update();
}

void YLButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    QPainter p(this);
    int w = m_pixmap.width();
    int h = m_pixmap.height();
    p.drawPixmap((width() - w) / 2, (height() - h) / 2,  w, h, m_pixmap);
}


void YLButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {

        if (m_clicked)
        {
            m_clicked = false;
            setStyleSheet("QPushButton{border:0px;}QPushButton:hover{background:#CFCFCF;}");
        }
        else
        {
            m_clicked = true;
            setStyleSheet("border:0px;background:#C6C6C6;");
        }
    }

    QPushButton::mousePressEvent(e);
}


void YLButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (!m_has_menu)
    {
        m_clicked = false;
        setStyleSheet("QPushButton{border:0px;}QPushButton:hover{background:#CFCFCF;}");
    }
    QPushButton::mouseReleaseEvent(e);
}


void YLButton::focusOutEvent(QFocusEvent *e)
{
    m_clicked = false;
    setStyleSheet("QPushButton{border:0px;}QPushButton:hover{background:#CFCFCF;}");
    QPushButton::focusOutEvent(e);
}
