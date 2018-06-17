#include "ylgroupchatwidget.h"

#include "globaldata.h"
#include "signalforward.h"
#include "ylmessageview.h"
#include "ylemoticonwidget.h"
#include "ylmessageeditwidget.h"
#include "YLNetWork/ylbusiness.h"
#include "YLDataBase/yldatabase.h"
#include "YLCommonControl/ylbutton.h"
#include "YLNetWork/http/httphelper.h"
#include "YLCommonControl/ylheadframe.h"
#include "YLCommonControl/ylgroupnoticewidget.h"
#include "YLCommonControl/ylgroupmemberlistwidget.h"

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolButton>

/***********************************************/
YLGroupChatWidget::YLGroupChatWidget(QWidget *parent) : QWidget(parent), m_hide(false)
{
    resize(1000, 650);
    initTop();
    initLeft();
    init();
    initMidToolBar();

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


void YLGroupChatWidget::initMidToolBar()
{
    m_emotion = new YLButton(this);
    m_emotion->setImage(":/res/YLChatWidget/aio_quickbar_face.png");
    m_emotion->setFixedSize(35, 30);
    connect(m_emotion, &YLButton::clicked, this, &YLGroupChatWidget::showEmotionWidget);

    m_gif = new YLButton(this);
    m_gif->setImage(":/res/YLChatWidget/aio_quickbar_gif.png");
    m_gif->setFixedSize(35, 30);

    m_cut = new YLButton(this);
    m_cut->setImage(":/res/YLChatWidget/aio_quickbar_cut.png");
    m_cut->setFixedSize(35, 30);

    m_file2 = new YLButton(this);
    m_file2->setImage(":/res/YLChatWidget/aio_quickbar_uploadfile.png");
    m_file2->setFixedSize(35, 30);
//    connect(m_file, &YLButton::clicked, this, &YLSingleChatWidget::selectFile);

    m_image = new YLButton(this);
    m_image->setImage(":/res/YLChatWidget/aio_quickbar_sendpic.png");
    m_image->setFixedSize(35, 30);

    m_more = new YLButton(this);
    m_more->setImage(":/res/YLChatWidget/aio_quickbar_more.png");
    m_more->setFixedSize(35, 30);

    m_msg_record = new YLButton(this);
    m_msg_record->setImage(":/res/YLChatWidget/aio_quickbar_register.png");
    m_msg_record->setFixedSize(35, 30);

    QHBoxLayout *hl = new QHBoxLayout;

    hl->addWidget(m_emotion);
    hl->addWidget(m_gif);
    hl->addWidget(m_cut);
    hl->addWidget(m_file2);
    hl->addWidget(m_image);
    hl->addWidget(m_more);
    hl->addStretch();
    hl->addWidget(m_msg_record);
    hl->setMargin(0);
    hl->setSpacing(0);

    m_mid_toolbar = new QWidget(this);
    m_mid_toolbar->setLayout(hl);
}

void YLGroupChatWidget::init()
{
//    m_label = new QLabel(this);
//    QPixmap pixmap(":/res/YLChatWidget/1.png");
//    m_label->setFixedSize(pixmap.size());
//    m_label->setPixmap(pixmap);
//    m_label->move(5, 5);

    m_message_view = new YLMessageView(this);
    m_message_view->setFocusPolicy(Qt::NoFocus);
    m_message_view->resize(width() - 200, 450);
    m_message_view->setStyleSheet("background:red;");
    connect(m_message_view, &YLMessageView::loadFinished, this, [this](bool f) {
        //加载最近消息
        YLDataBase db;
        auto vec = db.getRecentGroupMsgByGroupId(m_group.getGroupId());

        for (QPair<uint32_t, YLMessage> pair : vec)
        {
            //senderid 是当前登录用户
            if (pair.first == GlobalData::getCurrLoginUserId())
            {
                m_message_view->addRight(GlobalData::getCurrLoginUserIconPath(), pair.second.getMsgContent());
            }
            else
            {
//                m_message_view->addGroupLeft(GlobalData::getMemberInfo(m_group.getGroupId(), pair.first).user_info().user_header_url().c_str(),
//                                        pair.second.getMsgContent());
                receiveMessage(pair.first, pair.second.getMsgContent());
            }
        }

        if (f) emit loadFinish();

    });


    m_message_edit_widget = new YLMessageEditWidget(this);
    m_message_edit_widget->resize(width(), 75);


    m_close_button = new QPushButton("关闭", this);
    m_close_button->setFixedSize(65, 30);
    m_close_button->setStyleSheet("border:0px;background-color:white; color:black");

    m_send_button = new QPushButton("发送", this);
    m_send_button->setFixedSize(65, 30);
    m_send_button->setStyleSheet("border:0px;background-color:white; color:black");
    connect(m_send_button, &QPushButton::clicked, this, &YLGroupChatWidget::sendTextMessage);

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

    m_message_view->move(0, 50);
    m_message_edit_widget->move(0, height() - 110);
    m_close_button->move(width() - 165 - m_scale_width, height() - 40);
    m_send_button->move(width() - 95 - m_scale_width, height() - 40);
    m_mid_toolbar->move(0, height() - 148);

    //right
    m_notice_widget->move(width() - m_scale_width, 50);
    m_member_list_widget->move(width() - m_scale_width, 215);

    //resize
    m_mid_toolbar->resize(width() - m_scale_width, 35);
    m_message_view->resize(width() - m_scale_width - 1, m_mid_toolbar->geometry().topLeft().y() - 53);
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
    p.drawLine(m_message_view->width() + 1, 50, m_message_view->width(), m_message_view->height() + 50);

}


void YLGroupChatWidget::resizeEvent(QResizeEvent *event)
{
    updateSizeAndPosition();

    QWidget::resizeEvent(event);
}


void YLGroupChatWidget::closeEvent(QCloseEvent *event)
{
    GlobalData::removeGroupChatWidget(m_group.getGroupId());
    QWidget::closeEvent(event);
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

void YLGroupChatWidget::showEmotionWidget()
{
    if (YLEmoticonWidget::isShow)
        return;

    YLEmoticonWidget  *emotionWidget = new YLEmoticonWidget();
    QPoint p = mapToGlobal(QPoint(0, 502));
    emotionWidget->move(p.x(), p.y() - 230);
    emotionWidget->show();
    connect(emotionWidget, &YLEmoticonWidget::selected, m_message_edit_widget, &YLMessageEditWidget::addEmoticon);
}


void YLGroupChatWidget::sendTextMessage()
{
    QString content = m_message_edit_widget->getContent();
    m_message_edit_widget->clear();

    //提取文件
    QString pattern = "src='(file:.*)'";
    QRegExp re(pattern);
    re.setMinimal(true);
    int pos = 0;
    QStringList fileList;
    while ((pos = re.indexIn(content, pos)) >= 0 )
    {
        QString p = re.cap(1);
        fileList << p;
        pos += re.matchedLength();
    };

    //上传文件
    HttpHelper *helper = new HttpHelper;
    QStringList uploadFileList;
    for (QString fileName : fileList)
    {
        QString localFile = fileName.replace("file://", "");
        uploadFileList << helper->upload(localFile);
    }


    m_message_view->addRight(GlobalData::getCurrLoginUserIconPath(), content);

    for (int i = 0; i < fileList.size(); ++i)
    {
        content.replace(fileList[i], "http://www.liutimo.cn/" + uploadFileList[i]);
    }

    YLBusiness::sendGroupTextMessage(m_group.getGroupId(), GlobalData::getCurrLoginUserId(), content);

    YLSession session = GlobalData::getSessionByGroupId(m_group.getGroupId());

    //session 存在,更新session
    if (session.getOtherId() == m_group.getGroupId())
    {
        session.setSessionLastChatMessage(content);
        session.setSessionLastChatTime(QDateTime::currentDateTime().toTime_t());
        SignalForward::instance()->forwordUpdateSession(session);
    }
}

void YLGroupChatWidget::receiveMessage(uint32_t user_id, const QString &message)
{
    QRegExp re;
    re.setPattern("<img.*src='.*'.*>");
    re.setMinimal(true);
    QString msg = message;

    bool ret = false;
    base::MemberInfo& memberInfo = GlobalData::getMemberInfo(m_group.getGroupId(), user_id, ret);

    if (!ret)
        return;

    QString groupCard = memberInfo.group_card().c_str();
    QString name = groupCard.isEmpty() ? memberInfo.user_info().user_nick().c_str() : groupCard;

    QUrl url(memberInfo.user_info().user_header_url().c_str());
    m_message_view->addGroupLeft("file://" + GlobalData::imagePath + url.fileName(), name ,message);

    msg.replace(re, "[Picture]");

//    YLSession session = GlobalData::getSessionByFriendId(m_friend.friendId());
//    session.setOtherId(m_group.getGroupId());
//    session.setSessionType(base::SESSION_TYPE_GROUP);
//    session.setSessionLastChatMessage(msg);
//    session.setSessionLastChatTime(QDateTime::currentDateTime().toTime_t());
//    SignalForward::instance()->forwordUpdateSession(session);
//    //send message ack
}


void YLGroupChatWidget::loadMemberList()
{
    QVector<YLGroupMember> vec;
    {
        YLDataBase db;

        vec = db.getMemberByGroupId(m_group.getGroupId());
    }

    if (vec.empty())
        return;

    for (auto &mem : vec)
    {
        m_member_list_widget->addRow(mem);
    }
}
