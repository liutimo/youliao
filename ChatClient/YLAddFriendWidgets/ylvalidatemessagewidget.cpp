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

    setWidgetIcon();
    m_widget_icon->setFixedSize(18, 18);
    m_widget_icon->move(5, 7);
    m_widget_icon->setPixmap(QPixmap(":/res/YLAddFriendWIdgets/AddBuddy/SessionNode.png").scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    setWidgetTitle("验证消息");
    m_title_label->move(30, 5);
    initTop();

    m_friend_widget = new QScrollArea(this);
    m_friend_widget->setFixedSize(612, 400);
    m_friend_widget->move(0, 60);

    m_group_widget = new QScrollArea(this);
    m_group_widget->setFixedSize(612, 400);
    m_group_widget->move(0, 60);
    m_group_widget->hide();

    showFriendWidget();
}


void YLValidateMessageWidget::initTop()
{
    m_friend_message = new QPushButton("好友验证", this);
    m_friend_message->setFixedSize(110, 30);
    m_friend_message->move(0, 30);
    m_friend_message->setStyleSheet(qss_selected);

    m_group_message = new QPushButton("群系统消息", this);
    m_group_message->setFixedSize(110, 30);
    m_group_message->move(110, 30);
    m_group_message->setStyleSheet(qss_no_selected);


    connect(m_friend_message, &QPushButton::clicked, this, [this](){
        m_friend_message->setStyleSheet(qss_selected);
        m_group_message->setStyleSheet(qss_no_selected);

        showFriendWidget();
    });

    connect(m_group_message, &QPushButton::clicked, this, [this](){
        m_group_message->setStyleSheet(qss_selected);
        m_friend_message->setStyleSheet(qss_no_selected);
        showGroupWidget();
    });


    m_no_msg = new QLabel(this);
    m_no_msg->setFixedSize(176, 62);
    m_no_msg->setPixmap(QPixmap(":/res/YLAddFriendWIdgets/AddBuddy/AddBuddyNoMsg.png"));
    m_no_msg->move((width() - 176) / 2, 200);


}


void YLValidateMessageWidget::paintEvent(QPaintEvent *event)
{
    const int titleBarHeight = 70;
    const int bottomBtnHeight = 36;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);


    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    painter.setBrush(QColor::fromRgb(40, 138, 221));            //#288ADD
    painter.drawRect(0, 0, width(), titleBarHeight);

    painter.setBrush(QColor::fromRgb(234, 244, 252));           //#EAF4FC
    painter.drawRect(0, titleBarHeight, width(), height() - 106);

    painter.setBrush(QColor::fromRgb(219,228,240));             //#DBE4F0
    painter.drawRect(0, height() - bottomBtnHeight, width(), height());
}

void YLValidateMessageWidget::showFriendWidget()
{
    m_friend_widget->show();
    m_group_widget->hide();

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

    m_friend_widget->setWidget(widget);
}



void YLValidateMessageWidget::showGroupWidget()
{
    m_friend_widget->hide();
    m_group_widget->show();

    QWidget *widget = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout;

    auto requests = GlobalData::getGroupAddRequests();

    for (int i = 0; i < requests.size(); ++i)
    {
        const YLAddRequest &re = requests[i];
        ValidateInfomationWidget *w = new ValidateInfomationWidget(this);
        w->setAddRequest(re, true);
        layout->addWidget(w);
    }

//    const auto &history = GlobalData::getRequestHistory();

//    for (int i = 0; i < history.size(); ++i)
//    {
//        const YLAddRequest &re = history[i];
//        ValidateInfomationWidget *w = new ValidateInfomationWidget(this);
//        w->setAddRequest(re);
//        if (re.getResultId() != 0)
//            w->setConfirmed(true);
//        layout->addWidget(w);
//    }

    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setContentsMargins(20, 10, 20, 10);
    widget->setLayout(layout);

    m_group_widget->setWidget(widget);
}


/**********ValidateInfomationWidget**************/
ValidateInfomationWidget::ValidateInfomationWidget(QWidget *parent) : QWidget(parent), m_is_group(false)
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
    connect(agree, &QAction::triggered, this, &ValidateInfomationWidget::acceptRequest);

    connect(refuse, &QAction::triggered, this, &ValidateInfomationWidget::refuseRequest);

    m_op_text = new QLabel(this);
    m_op_text->setFixedSize(69, 24);
    m_op_text->move(471, 30);
    m_op_text->hide();

    m_left_button = new QPushButton("同意", this);
    m_left_button->setFixedSize(61, 24);
    m_left_button->move(382, 30);
    m_left_button->setStyleSheet(qss_left_button);
    connect(m_left_button, &QPushButton::clicked, this, &ValidateInfomationWidget::acceptRequest);


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


void ValidateInfomationWidget::setAddRequest(const YLAddRequest &req, bool isGroup)
{
    m_request = req;
    m_is_group = isGroup;

    m_head_frame->setHeadFromUrl(m_request.getOtherHeadUrl());
    if(!isGroup)
        m_nick->setText(m_request.getOtherNick());
    else
    {
        m_nick->setText(QString("<span style='color:#239AF2; font-size:14px;'>%1</span>申请加入群"
                                "<span style='color:#239AF2;font-size:14px;'>%2</span>").arg(req.getOtherNick())
                                .arg(GlobalData::getGroupByGroupId(req.getGroupId()).getGroupName()));
        m_infomation->hide();
    }
    m_attach_msg->setText("附加消息:" + m_request.getValidateData());
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

void ValidateInfomationWidget::acceptRequest()
{
    if (!m_is_group)
    {
        hideRight();
        YLConfirmWidget *w = new YLConfirmWidget;
        w->setOtherId(m_request.getOtherId());
        w->move(mapToGlobal(geometry().center() - w->geometry().center() / 2));
        w->show();
        connect(w, &YLConfirmWidget::complete, this, [this](){
            hideRight();
            m_op_text->setText("已同意");
        });
    }
    else
    {
        hideRight();
        m_op_text->setText("已同意");
        YLBusiness::sendGroupVerifyResult(m_request.getGroupId(), m_request.getOtherId(), base::GROUP_VERIFY_RESULT_PASS);
    }
}

void ValidateInfomationWidget::refuseRequest()
{
    hideRight();
    m_op_text->setText("已拒绝");
    if (!m_is_group)
    {
        YLBusiness::addFriendRespone(m_request.getOtherId(), 2);
    }
    else
    {
        YLBusiness::sendGroupVerifyResult(m_request.getGroupId(), m_request.getOtherId(), base::GROUP_VERIGY_RESULT_REFUEST);
    }
}
