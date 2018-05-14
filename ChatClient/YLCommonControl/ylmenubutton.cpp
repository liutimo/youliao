#include "ylmenubutton.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QMenu>
#include <QPainter>
YLMenuButton::YLMenuButton(QWidget *parent) : QWidget(parent), m_menu_init(false), m_status(NORMAL)
{
    m_hover_color = m_pressed_color = m_normal_color = QColor::fromRgb(255, 255, 255, 0);
    init();
}


void YLMenuButton::init()
{
    m_right_arrow = new QPushButton(this);
    connect(m_right_arrow, &QPushButton::clicked, this, &YLMenuButton::showMenu);

    m_left_button = new QPushButton(this);
}


void YLMenuButton::setSize(const QSize& left, const QSize &right)
{
    m_left_size = left;
    m_right_size = right;

    m_left_button->setFixedSize(m_left_size);
    m_right_arrow->setFixedSize(m_right_size);

    int w = left.width() + right.width() + 5;

    int padding = (width() - w) / 2;

    m_left_button->move(padding, (height() - left.height()) / 2);
    m_right_arrow->move(m_left_button->geometry().topRight().x() + 5, (height() - right.height()) / 2);
}


void YLMenuButton::setIcon(const QString &leftIcon, const QString &rightIcon)
{
    m_left_button->setStyleSheet(qss_custom_button_.arg(leftIcon));
    m_right_arrow->setStyleSheet(qss_custom_button_.arg(rightIcon));
}

void YLMenuButton::setHoverColor(const QColor &color)
{
    m_hover_color = color;
}

void YLMenuButton::setNormalColor(const QColor &color)
{
    m_normal_color = color;
}

void YLMenuButton::setPressedColor(const QColor &color)
{
    m_pressed_color = color;
}

void YLMenuButton::setMenu(QMenu *menu)
{
    m_menu = menu;
    m_menu_init = true;
}

void YLMenuButton::showMenu()
{
    if (m_menu_init)
        m_menu->exec(mapToGlobal(m_right_arrow->geometry().bottomLeft()));
}


void YLMenuButton::enterEvent(QEvent *e)
{
    m_status = HOVER;
    update();
    QWidget::enterEvent(e);
}

void YLMenuButton::leaveEvent(QEvent *e)
{
    m_status = NORMAL;
    update();
    QWidget::leaveEvent(e);
}

void YLMenuButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_status = PRESSED;
        update();
    }
    QWidget::mousePressEvent(e);
}


void YLMenuButton::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    switch (m_status) {
    case HOVER:
        p.setBrush(m_hover_color);
        break;
    case NORMAL:
        p.setBrush(m_normal_color);
        break;
    case PRESSED:
        p.setBrush(m_pressed_color);
        break;
    default:
        break;
    }

    p.drawRect(rect());
}
