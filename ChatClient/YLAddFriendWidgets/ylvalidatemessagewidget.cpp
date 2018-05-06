#include "ylvalidatemessagewidget.h"
#include <QPushButton>
#include "YLCommonControl/ylheadframe.h"
#include "YLNetWork/ylbusiness.h"
#include "ylconfirmwidget.h"
#include "globaldata.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QPainter>
YLValidateMessageWidget::YLValidateMessageWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(612, 489);
    setWidgetIcon(":/res/YLAddFriendWIdgets/AddBuddy/horn.png");
    setWidgetTitle("验证消息");
    initTop();
}


void YLValidateMessageWidget::initTop()
{
    m_friend_message = new QPushButton("好友验证", this);
    m_friend_message->setFixedSize(110, 30);
    m_friend_message->move(0, 30);

    m_group_message = new QPushButton("群组验证", this);
    m_group_message->setFixedSize(110, 30);
    m_group_message->move(110, 30);

    m_no_msg = new QLabel(this);
    m_no_msg->setFixedSize(176, 62);
    m_no_msg->setPixmap(QPixmap(":/res/YLAddFriendWIdgets/AddBuddy/AddBuddyNoMsg.png"));
    m_no_msg->move((width() - 176) / 2, 200);
    QScrollArea *ww = new QScrollArea(this);
    ww->setFixedSize(612, 400);
    ww->move(0, 60);

    QWidget *widget = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout;

    auto requests = GlobalData::getAddRequests();

    for (int i = 0; i < requests.size(); ++i)
    {
        const YLAddRequest &re = requests[i];
        ValidateInfomationWidget *w = new ValidateInfomationWidget(this);
        w->setAddRequest(re);
        layout->addWidget(w);
    }

    const auto &history = GlobalData::getRequestHistory();

    for (int i = 0; i < history.size(); ++i)
    {
        const YLAddRequest &re = history[i];
        ValidateInfomationWidget *w = new ValidateInfomationWidget(this);
        w->setAddRequest(re);
        if (re.getResultId() != 0)
            w->setConfirmed(true);
        layout->addWidget(w);
    }

    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setContentsMargins(20, 10, 20, 10);
    widget->setLayout(layout);

    ww->setWidget(widget);
}


/**********ValidateInfomationWidget**************/
ValidateInfomationWidget::ValidateInfomationWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(550, 85);

    init();
    initRight();

}

ValidateInfomationWidget::~ValidateInfomationWidget()
{
    qDebug() << "~ValidateInfomationWidget()";
}

void ValidateInfomationWidget::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(65, 65);
    m_head_frame->move(10, 10);

    m_nick = new QLabel("hahah", this);
    m_nick->move(85, 10);

    m_infomation = new QLabel("Boy 21",this);
    m_infomation->move(85, 30);

    m_attach_msg = new QLabel("附加消息:搜索1",this);
    m_attach_msg->move(85, 50);

    m_close = new QPushButton(this);
    m_close->move(525, 0);
    m_close->setFixedSize(25, 23);
    m_close->hide();
    m_close->setStyleSheet(qss_close_button);

    connect(m_close, &QPushButton::clicked, this, &ValidateInfomationWidget::close);
}

void ValidateInfomationWidget::initRight()
{
    QMenu *menu = new QMenu;
    QAction *agree = new QAction("同意");
    QAction *refuse = new QAction("拒绝");
    menu->addAction(agree);
    menu->addAction(refuse);
    connect(agree, &QAction::triggered, this, [this](){
        hideRight();
        m_op_text->setText("已同意");
        YLBusiness::addFriendRespone(m_request.getOtherId(), 1);
    });
    connect(refuse, &QAction::triggered, this, [this](){
        hideRight();
        m_op_text->setText("已拒绝");
        YLBusiness::addFriendRespone(m_request.getOtherId(), 2);
    });

    m_op_text = new QLabel(this);
    m_op_text->setFixedSize(69, 24);
    m_op_text->move(471, 30);
    m_op_text->hide();

    m_left_button = new QPushButton("同意", this);
    m_left_button->setFixedSize(61, 24);
    m_left_button->move(382, 30);
    m_left_button->setStyleSheet(qss_left_button);
    connect(m_left_button, &QPushButton::clicked, this, [this](){
        YLConfirmWidget *w = new YLConfirmWidget;
        w->setOtherId(m_request.getOtherId());
        w->move(mapToGlobal(geometry().center() - w->geometry().center() / 2));
        w->show();
        connect(w, &YLConfirmWidget::complete, this, [this](){
            hideRight();
            m_op_text->setText("已同意");
        });
    });


    m_right_button = new QPushButton(this);
    m_right_button->setFixedSize(20, 24);
    m_right_button->move(443, 30);
    m_right_button->setStyleSheet(qss_right_button);
    connect(m_right_button, &QPushButton::clicked, this, [this, menu] () {
        menu->exec(mapToGlobal(m_right_button->geometry().bottomLeft()));
    });

    m_ignore_button = new QPushButton("忽略", this);
    m_ignore_button->setFixedSize(69, 24);
    m_ignore_button->setStyleSheet(qss_ignore_button);
    m_ignore_button->move(471, 30);
    connect(m_ignore_button, &QPushButton::clicked, this, [this](){
        hideRight();
        m_op_text->setText("已忽略");
        YLBusiness::addFriendRespone(m_request.getOtherId(), 3);
    });

}

void ValidateInfomationWidget::showRight()
{
    m_op_text->hide();
    m_right_button->show();
    m_left_button->show();
    m_ignore_button->show();
}

void ValidateInfomationWidget::hideRight()
{
    m_op_text->show();
    m_right_button->hide();
    m_left_button->hide();
    m_ignore_button->hide();
}

void ValidateInfomationWidget::enterEvent(QEvent *event)
{
    m_close->show();
    QWidget::enterEvent(event);
}

void ValidateInfomationWidget::leaveEvent(QEvent *event)
{
    m_close->hide();
    QWidget::leaveEvent(event);
}


void ValidateInfomationWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor::fromRgba(qRgba(246, 246, 245, 200))));
    painter.drawRect(rect());
}


void ValidateInfomationWidget::setAddRequest(const YLAddRequest &req)
{
    m_request = req;

    m_head_frame->setHeadFromUrl(m_request.getOtherHeadUrl());
    m_nick->setText(m_request.getOtherNick());
    m_attach_msg->setText(m_request.getValidateData());
}

void ValidateInfomationWidget::setConfirmed(bool isConfirmed)
{
    if (isConfirmed)
    {
        hideRight();
        uint32_t resultId = m_request.getResultId();
        if (resultId == 1)
        {
            m_op_text->setText("已同意");
        }
        else if (resultId == 2)
        {
            m_op_text->setText("已拒绝");
        }
        else if (resultId == 3)
        {
            m_op_text->setText("已忽略");
        }
    }
}


