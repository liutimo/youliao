#include "ylgroupchatwidget.h"
#include "ylmessageview.h"
#include "YLCommonControl/ylgroupnoticewidget.h"
#include "ylmessageeditwidget.h"
#include "YLCommonControl/ylgroupmemberlistwidget.h"
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include <QToolButton>
YLGroupChatWidget::YLGroupChatWidget(QWidget *parent) : QWidget(parent), m_hide(false)
{
    resize(1000, 650);
    initTop();
    initLeft();
    init();

    m_scale_width = 200;;
}


void YLGroupChatWidget::initTop()
{
    m_chat = new QToolButton(this);
    m_chat->setText("聊天");
    m_chat->setFixedSize(45, 40);
    m_chat->setStyleSheet(qss_selected);
    connect(m_chat, &QToolButton::clicked, this, &YLGroupChatWidget::navigationClicked);

    m_notice = new QToolButton(this);
    m_notice->setText("公告");
    m_notice->setFixedSize(45, 40);
    m_notice->setStyleSheet(qss_no_selected);
    connect(m_notice, &QToolButton::clicked, this, &YLGroupChatWidget::navigationClicked);


    m_file = new QToolButton(this);
    m_file->setText("文件");
    m_file->setFixedSize(45, 40);
    m_file->setStyleSheet(qss_no_selected);
    connect(m_file, &QToolButton::clicked, this, &YLGroupChatWidget::navigationClicked);

    m_setting = new QToolButton(this);
    m_setting->setText("设置");
    m_setting->setFixedSize(45, 40);
    m_setting->setStyleSheet(qss_no_selected);
    connect(m_setting, &QToolButton::clicked, this, &YLGroupChatWidget::navigationClicked);
}

void YLGroupChatWidget::init()
{
//    m_label = new QLabel(this);
//    QPixmap pixmap(":/res/YLChatWidget/1.png");
//    m_label->setFixedSize(pixmap.size());
//    m_label->setPixmap(pixmap);
//    m_label->move(5, 5);

    m_meesage_view = new YLMessageView(this);
    m_meesage_view->setFocusPolicy(Qt::NoFocus);
    m_meesage_view->resize(width() - 200, 450);
    m_meesage_view->setStyleSheet("background:red;");

    m_label2 = new QLabel(this);
    QPixmap pixmap1(":/res/YLChatWidget/2.png");
    m_label2->setFixedSize(pixmap1.size());
    m_label2->setPixmap(pixmap1);

    m_meesage_edit_widget = new YLMessageEditWidget(this);
    m_meesage_edit_widget->resize(width(), 75);


    m_close_button = new QPushButton("关闭", this);
    m_close_button->setFixedSize(65, 30);
//    m_close_button->setFocusPolicy(Qt::NoFocus);
    m_close_button->setStyleSheet("border:0px;background-color:white; color:black");

    m_send_button = new QPushButton("发送", this);
    m_send_button->setFixedSize(65, 30);
//    m_send_button->setFocusPolicy(Qt::NoFocus);
    m_send_button->setStyleSheet("border:0px;background-color:white; color:black");

    m_split_button = new QPushButton(this);
    m_split_button->setFixedSize(13, 90);
    m_split_button->setStyleSheet(qss_split_button_right);
    connect(m_split_button, &QPushButton::clicked, this, &YLGroupChatWidget::spliteButtonClicked);
}

void YLGroupChatWidget::initLeft()
{
    m_notice_widget = new YLGroupNoticeWidget(this);

    m_member_list_widget = new YLGroupMemberListWidget(this);
}


void YLGroupChatWidget::updateSizeAndPosition()
{
    //顶部
    m_chat->move(10, 9);
    m_notice->move(65, 9);
    m_file->move(115, 9);
    m_setting->move(170, 9);


    m_split_button->move(width() - 13 - m_scale_width, height() / 2 - 45);

    m_meesage_view->move(0, 50);
    m_label2->move(5, height() - 146);
    m_meesage_edit_widget->move(2, height() - m_meesage_view->geometry().bottomLeft().y());
    m_close_button->move(width() - 165 - m_scale_width, height() - 40);
    m_send_button->move(width() - 95 - m_scale_width, height() - 40);

    //right
    m_notice_widget->move(width() - m_scale_width, 50);
    m_member_list_widget->move(width() - m_scale_width, 215);

    //resize
    m_meesage_view->resize(width() - m_scale_width - 1, m_label2->geometry().topLeft().y() - 53);
    m_member_list_widget->resize(m_scale_width, height() - m_notice_widget->geometry().bottomRight().y());
}

void YLGroupChatWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(250, 250, 251)); //#FAFAFB
    p.drawRect(rect());

    p.setPen(QColor::fromRgb(217, 217, 218));     //#E7E7E8
    p.drawLine(0, 49, width(), 49);
    p.drawLine(0, height() - 147, width() - m_scale_width, height() - 147);
    p.drawLine(m_meesage_view->width() + 1, 50, m_meesage_view->width(), m_meesage_view->height() + 50);

}


void YLGroupChatWidget::resizeEvent(QResizeEvent *event)
{
    updateSizeAndPosition();

    QWidget::resizeEvent(event);
}

void YLGroupChatWidget::navigationClicked()
{
    QToolButton *object = static_cast<QToolButton*>(sender());

    if (object == m_chat)
    {
        m_chat->setStyleSheet(qss_selected);
        m_notice->setStyleSheet(qss_no_selected);
        m_file->setStyleSheet(qss_no_selected);
        m_setting->setStyleSheet(qss_no_selected);
    }
    else if (object == m_notice)
    {
        m_chat->setStyleSheet(qss_no_selected);
        m_notice->setStyleSheet(qss_selected);
        m_file->setStyleSheet(qss_no_selected);
        m_setting->setStyleSheet(qss_no_selected);
    }
    else if (object == m_file)
    {

        m_chat->setStyleSheet(qss_no_selected);
        m_notice->setStyleSheet(qss_no_selected);
        m_file->setStyleSheet(qss_selected);
        m_setting->setStyleSheet(qss_no_selected);
    }
    else if (object == m_setting)
    {
        m_chat->setStyleSheet(qss_no_selected);
        m_notice->setStyleSheet(qss_no_selected);
        m_file->setStyleSheet(qss_no_selected);
        m_setting->setStyleSheet(qss_selected);
    }
}

void YLGroupChatWidget::spliteButtonClicked()
{
    if (m_hide)
    {
        m_scale_width = 200;
        m_notice_widget->show();
        m_split_button->setStyleSheet(qss_split_button_right);
    }
    else
    {
        m_scale_width = 0;
        m_notice_widget->hide();
        m_split_button->setStyleSheet(qss_split_button_left);
    }
    updateSizeAndPosition();
    m_hide = !m_hide;
}
