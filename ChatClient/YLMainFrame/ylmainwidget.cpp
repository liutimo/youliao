#include "ylmainwidget.h"
#include <QPushButton>
#include <QDir>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QStandardPaths>
#include "globaldata.h"
#include "ylnavigationbar.h"
#include "ylgrouplistview.h"
#include "ylrecentchatview.h"
#include "ylfriendlistview.h"
#include "../signalforward.h"
#include "YLCommonControl/ylsearchlineedit.h"
#include "YLTray/ylmaintray.h"
#include "ylsignaturelineedit.h"
#include "YLNetWork/ylbusiness.h"
#include "YLNetWork/pduhandler.h"
#include "YLNetWork/http/httphelper.h"
#include "YLCommonControl/ylmessagebox.h"
#include "YLAddFriendWidgets/yladdfriendwidget.h"
#include "YLCommonControl/ylheadandstatusframe.h"
#include "YLDataBase/yldatabase.h"
#include "yluserinformationwidget.h"
using namespace youliao::pdu;

QPoint YLMainWidget::center = QPoint();

YLMainWidget::YLMainWidget(QWidget *parent) : YLBasicWidget(parent)
{
    resize(400, 800);
    init();
    initTray();
    initListWidget();
    center = geometry().center();

    connect(PduHandler::instance(), &PduHandler::userHeaderIconChanged, this, [this](){
        head_status_frame_->setHeadFromUrl(GlobalData::getCurrLoginUserHeadUrl());
    });
}

void YLMainWidget::init()
{
    min_button_ = new QPushButton(this);
    min_button_->resize(close_button_->size());
    min_button_->setObjectName("min_button_");
    min_button_->setStyleSheet(qss_min_button);

    connect(min_button_, &QPushButton::clicked, this, [this](){
        hide();
    });


    skin_button_ = new QPushButton(this);
    skin_button_->resize(close_button_->size());
    skin_button_->setObjectName("skin_button_");
    skin_button_->setStyleSheet(qss_skin_button);
    skin_button_->hide();

    logo_label_ = new QLabel(this);
    logo_label_->setObjectName("logo_label_");
    logo_label_->setStyleSheet(qss_logo_label);
    logo_label_->resize(QSize(21, 24));

    head_status_frame_  = new YLHeadAndStatusFrame(this);
    head_status_frame_->resize(80, 80);
    connect(head_status_frame_, &YLHeadAndStatusFrame::clicked, this, [this]()
    {
        YLUserInformationWidget *w = new YLUserInformationWidget;
        w->setUserInfo();
        w->show();
    });

    nickname_label_ = new QLabel(this);
    nickname_label_->setText("hahaha");
    nickname_label_->setObjectName("nickname_label_");
    nickname_label_->setStyleSheet(qss_nickname_label);

    signature_lineedit_ = new YLSignatureLineEdit(this);
    signature_lineedit_->resize(width() - 145, 30);
    connect(signature_lineedit_, &YLSignatureLineEdit::editFinished, this, [this](){
        YLBusiness::modifySignature(GlobalData::getCurrLoginUserId(), signature_lineedit_->text());
    });


    search_lineedit_ = new YLSearchLineEdit(this);
    search_lineedit_->resize(width() - 1, 40);

    navigation_bar_ = new YLNavigationBar(this);
    navigation_bar_->resize(width() - 1, 40);
    connect(navigation_bar_, &YLNavigationBar::click_index, this, [this](int index){
        for (int i = 0; i < vec.size(); ++i)
        {
            if (i == index - 1)
                vec[i]->show();
            else
                vec[i]->hide();
        }
    });

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        YLBusiness::heartBeat();
    });

    add_friend_button_ = new QPushButton(this);
    add_friend_button_->setFixedSize(60, 30);
    add_friend_button_->move(40, height() - 30);

    connect(add_friend_button_, &QPushButton::clicked, this, [](){
        YLAddFriendWidget *w = new YLAddFriendWidget;
        w->resize(600, 400);
        w->show();
    });
}

void YLMainWidget::initTray()
{
    m_main_tray = YLMainTray::instance();
    m_main_tray->show();

    connect(m_main_tray, &YLMainTray::showMain, this, [this](){ this->show(); });
    connect(m_main_tray, &YLMainTray::quit,     this, &YLMainWidget::close);
}

void YLMainWidget::initListWidget()
{
    //[1] 消息列表
    YLRecentChatView *yl_recent_chat_view = new YLRecentChatView(this);
    yl_recent_chat_view->resize(width() - 1, height() - 250);
    yl_recent_chat_view->move(0, 220);
    yl_recent_chat_view->hide();
    vec.push_back(yl_recent_chat_view);
    connect(SignalForward::instance(), &SignalForward::updateSession, yl_recent_chat_view, &YLRecentChatView::addItem);

    //[2] frient list
    YLFriendListView *yl_friendlist_view = new YLFriendListView(this);
    yl_friendlist_view->resize(width() - 1, height() - 250);
    yl_friendlist_view->move(0, 220);
    vec.push_back(yl_friendlist_view);

    //[3] group list
    YLGroupListView *yl_grouplist_vide = new YLGroupListView(this);
    yl_grouplist_vide->resize(width() - 1, height() - 250);
    yl_grouplist_vide->move(0, 220);
    yl_grouplist_vide->hide();
    vec.push_back(yl_grouplist_vide);

    connect(yl_friendlist_view, &YLFriendListView::updateSessions, yl_recent_chat_view, &YLRecentChatView::updateList);
}

void YLMainWidget::startHeartBeat()
{
    m_timer->start(2000);
}

void YLMainWidget::resizeEvent(QResizeEvent *event)
{
    //因为要使用close_button的位置，此处需要先调用父类的resizeEvent
    YLBasicWidget::resizeEvent(event);
    min_button_->move(close_button_->x() - close_button_->width(), 0);
    skin_button_->move(min_button_->x() - min_button_->width(), 0);
    logo_label_->move(8, 8);
    head_status_frame_->move(25, 50);
    nickname_label_->move(115, 50);
    signature_lineedit_->move(115, 90);
    search_lineedit_->move(0, 140);
    navigation_bar_->move(0, 180);

}

void YLMainWidget::mousePressEvent(QMouseEvent *event)
{
    min_button_->setFocus();
    YLBasicWidget::mousePressEvent(event);
}

void YLMainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    center = geometry().center();
    YLBasicWidget::mouseReleaseEvent(event);
}

void YLMainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(40, 138, 221, 122));
    p.drawRect(rect());
}
#include <QApplication>
void YLMainWidget::closeEvent(QCloseEvent *event)
{
    YLBusiness::loginOut(m_user_info->user_id());

    QApplication::quit();
}

/************************************************/
void YLMainWidget::setUserInfo(UserInfo *userInfo)
{

    m_user_info = userInfo;

    //创建默认文件夹
    QString documentDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/youliao/" + QString::number(userInfo->user_id()) ;
    QString audioDir = documentDir + "/audios/";
    QString imageDir = documentDir + "/images/";
    QString fileDir = documentDir + "/fileRecv/";

    GlobalData::audioPath = audioDir;
    GlobalData::imagePath = imageDir;
    GlobalData::filePath = fileDir;

    QDir dir;
    bool ret = true;
    dir.setPath(documentDir);
    if (!dir.exists())
       dir.mkdir(documentDir);
    if (!ret)
    {
        close();
        return;
    }

    dir.setPath(audioDir);
    if (!dir.exists())
        ret = dir.mkdir(audioDir);
    if (!ret)
    {
        close();
        return;
    }

    dir.setPath(imageDir);
    if (!dir.exists())
        ret = dir.mkdir(imageDir);
    if (!ret)
    {
        close();
        return;
    }

    dir.setPath(fileDir);
    if (!dir.exists())
        ret = dir.mkdir(fileDir);
    if (!ret)
    {
        close();
        return;
    }


    //必须在这里，因为需要使用设置好的图片路径
    GlobalData::setCurrLoginUser(*m_user_info);

    //设置用户信息
    nickname_label_->setText(m_user_info->user_nick().c_str());
    signature_lineedit_->setText(m_user_info->user_sign_info().c_str());
    head_status_frame_->setHeadFromUrl(QUrl(m_user_info->user_header_url().c_str()));

    //网络请求数据
    YLBusiness::getFriendGroupsRequest(m_user_info->user_id());
    YLBusiness::getFriendListRequest(m_user_info->user_id());
    YLBusiness::getGroupList();
    YLBusiness::getAllAddRequests();
}

