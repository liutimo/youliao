#include "ylsinglechatwidget.h"
#include "ylmessageview.h"
#include "ylmessageeditwidget.h"
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
YLSingleChatWidget::YLSingleChatWidget(QWidget *parent) : QWidget(parent)
{
    resize(800, 650);
    init();
}

void YLSingleChatWidget::init()
{
    m_label = new QLabel(this);
    QPixmap pixmap(":/res/YLChatWidget/1.png");
    m_label->setFixedSize(pixmap.size());
    m_label->setPixmap(pixmap);
    m_label->move(5, 5);

    m_meesage_view = new YLMessageView(this);
    m_meesage_view->setFocusPolicy(Qt::NoFocus);
    m_meesage_view->resize(width(), 450);
    m_meesage_view->move(0, 50);
    m_meesage_view->setStyleSheet("background:red;");

    m_label2 = new QLabel(this);
    QPixmap pixmap1(":/res/YLChatWidget/2.png");
    m_label2->setFixedSize(pixmap1.size());
    m_label2->setPixmap(pixmap1);
    m_label2->move(5, 502);

    m_meesage_edit_widget = new YLMessageEditWidget(this);
    m_meesage_edit_widget->resize(width(), 75);
    m_meesage_edit_widget->move(2, 540);


    m_close_button = new QPushButton("关闭", this);
    m_close_button->setFixedSize(65, 30);
    m_close_button->move(width() - 165, height() - 40);
//    m_close_button->setFocusPolicy(Qt::NoFocus);
    m_close_button->setStyleSheet("border:0px;background-color:white; color:black");

    m_send_button = new QPushButton("发送", this);
    m_send_button->setFixedSize(65, 30);
    m_send_button->move(width() - 95, height() - 40);
//    m_send_button->setFocusPolicy(Qt::NoFocus);
    m_send_button->setStyleSheet("border:0px;background-color:white; color:black");
}


void YLSingleChatWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(250, 250, 251)); //#FAFAFB
    p.drawRect(rect());

    p.setPen(QColor::fromRgb(217, 217, 218));     //#E7E7E8
    p.drawLine(0, 49, width(), 49);
    p.drawLine(0, 501, width(), 501);

}
