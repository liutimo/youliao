#include "ylcreategroupwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QDebug>
#include "YLCommonControl/ylheadframe.h"
#include "globaldata.h"
#include "signalforward.h"

YLCreateGroupWidget::YLCreateGroupWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(550, 450);
    setAttribute(Qt::WA_DeleteOnClose);
    init();
    initLayout();
    setWidgetIcon();
    setWidgetTitle("创建群组");

}

YLCreateGroupWidget::~YLCreateGroupWidget()
{
    qDebug() << "~YLCreateGroupWidget()";
}

void YLCreateGroupWidget::init()
{
    m_tip = new QLabel(this);
    m_tip->move(70, 40);
    m_tip->setText("填写信息");

    m_label_group_name = new QLabel("群名称:", this);
    m_label_group_name->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_label_group_name->setFixedWidth(60);

    m_label_group_count = new QLabel("群规模:", this);
    m_label_group_count->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_label_group_count->setFixedWidth(60);

    m_label_verify = new QLabel("加群验证:", this);
    m_label_verify->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_label_verify->setFixedWidth(60);

    m_lineedit_group_name = new QLineEdit(this);
    m_lineedit_custom_count = new QLineEdit(this);
    m_lineedit_custom_count->setEnabled(false);

    m_custom = new QRadioButton("自定义", this);
    m_custom->setStyleSheet(qss_radio);

    m_200 = new QRadioButton("200人", this);
    m_200->setStyleSheet(qss_radio);

    m_500 = new QRadioButton("500人", this);
    m_500->setStyleSheet(qss_radio);

    m_200->setChecked(true);

    m_group1 = new QButtonGroup(this);
    m_group1->addButton(m_200, 1);
    m_group1->addButton(m_500, 2);
    m_group1->addButton(m_custom, 3);
    connect(m_group1, SIGNAL(buttonToggled(int,bool)), this, SLOT(enableCustom(int,bool)));

    m_all = new QRadioButton("允许任何人", this);
    m_all->setStyleSheet(qss_radio);

    m_need_verify = new QRadioButton("需身份验证", this);
    m_need_verify->setStyleSheet(qss_radio);

    m_none_all = new QRadioButton("不允许任何人", this);\
    m_none_all->setStyleSheet(qss_radio);

    m_need_verify->setChecked(true);

    m_friend_list_widget = new FriendListWidget(this);
    m_friend_list_widget->loadFriendList();

    m_search_line_edit = new QLineEdit(this);


    m_selected_friend_list_widget = new SelectedFriendListWidget(this);
    m_selected_friend_list_widget->addSelf();
    connect(m_selected_friend_list_widget, &SelectedFriendListWidget::remove, this, &YLCreateGroupWidget::updateInfo);
    connect(SignalForward::instance(), &SignalForward::inviteGroupSelected, this, &YLCreateGroupWidget::addSelectedItem);

    m_label_selected = new QLabel("已选成员：", this);
    m_label_selected->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_label_selected->setFixedWidth(100);

    m_label_selected_count = new QLabel("(1/200)", this);
    m_label_selected_count->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_label_selected_count->setFixedWidth(100);


    m_next = new QPushButton("下一步", this);
    m_next->setFixedSize(60, 30);

    m_before = new QPushButton("上一步", this);
    m_before->setFixedSize(60, 30);
    m_before->hide();

    connect(m_next, &QPushButton::clicked, this, [this](){
        if (m_next->text() == "下一步")
        {
            updateInfo();
            if (m_lineedit_group_name->text().isEmpty())
            {
                //do something
                return;
            }

            if (m_custom->isChecked() && m_lineedit_custom_count->text().isEmpty())
            {
                //do something
                return;
            }

            m_widget_1->hide();
            m_widget_2->show();
            m_widget_3->show();
            m_before->show();
            m_next->setText("完成");
            m_tip->setText("邀请成员");
        }
        else
        {
            //do something
            close();
        }
    });

    connect(m_before, &QPushButton::clicked, this, [this](){
        m_widget_1->show();
        m_widget_2->hide();
        m_widget_3->hide();
        m_next->setText("下一步");
        m_tip->setText("填写信息");
    });

    m_widget_1 = new QWidget(this);

    m_widget_2 = new QWidget(this);
    m_widget_2->setFixedSize(275, 340);


    m_widget_3 = new QWidget(this);
    m_widget_3->setFixedSize(275, 340);
}

void YLCreateGroupWidget::initLayout()
{
    h1 = new QHBoxLayout();
    h1->setContentsMargins(0, 10, 0, 10);
    h1->addWidget(m_label_group_name);
    h1->addWidget(m_lineedit_group_name);
    h1->setSizeConstraint(QLayout::SetFixedSize);

    h2 = new QHBoxLayout();
    h2->setContentsMargins(0, 10, 0, 10);
    h2->addWidget(m_label_group_count);
    h2->addWidget(m_200);
    h2->addWidget(m_500);
    h2->addWidget(m_custom);
    h2->addWidget(m_lineedit_custom_count);
    h2->setSizeConstraint(QLayout::SetFixedSize);

    h3 = new QHBoxLayout();
    h3->setContentsMargins(0, 10, 0, 10);
    h3->addWidget(m_label_verify);
    h3->addWidget(m_all);
    h3->addWidget(m_need_verify);
    h3->addWidget(m_none_all);
    h3->setSizeConstraint(QLayout::SetFixedSize);

    v = new QVBoxLayout();
    v->setContentsMargins(10, 50, 10, 0);
    v->addLayout(h1);
    v->addLayout(h2);
    v->addLayout(h3);

    m_widget_1->setLayout(v);
    m_widget_1->move(70, 70);

    v2 = new QVBoxLayout;
    v2->setMargin(0);
    v2->addWidget(m_search_line_edit);
    v2->addWidget(m_friend_list_widget);
    m_widget_2->setLayout(v2);
    m_widget_2->move(5, 70);
    m_widget_2->hide();


    v3 = new QVBoxLayout;
    h4 = new QHBoxLayout;
    h4->addWidget(m_label_selected);
    h4->addWidget(m_label_selected_count);
    v3->addLayout(h4);
    v3->addWidget(m_selected_friend_list_widget);
    m_widget_3->setLayout(v3);
    m_widget_3->move(280, 70);
    m_widget_3->hide();

    m_next->move(480, 410);
    m_before->move(410, 410);

    v->setSizeConstraint(QLayout::SetFixedSize);
}

void YLCreateGroupWidget::enableCustom(int id, bool checked)
{
    if (id == 3 && checked)
    {
        m_lineedit_custom_count->setEnabled(true);
    }
    else
    {
        m_lineedit_custom_count->setEnabled(false);
    }
}

void YLCreateGroupWidget::addSelectedItem(uint32_t friId)
{
    m_selected_friend_list_widget->addOne(friId, true);
    updateInfo();
}

void YLCreateGroupWidget::updateInfo()
{
    uint32_t total = 0;

    if (m_200->isChecked())
        total = 200;
    else if (m_500->isChecked())
        total = 500;
    else
        total = m_lineedit_custom_count->text().toInt();

    m_label_selected_count->setText(QString("(%1/%2)").arg(m_selected_friend_list_widget->count()).arg(total));
}

/***************************FriendListWidget****************************/
FriendListWidget::FriendListWidget(QWidget *parent) : QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(qss_this + qss_scroll_bar);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    init();
}


FriendListWidget::~FriendListWidget()
{
    qDebug() << "~FriendListWidget()";
}

void FriendListWidget::init()
{

}

void FriendListWidget::loadFriendList()
{
    clear();
    const QMap<int, QVector<YLFriend>> &friends = GlobalData::getFriends();
    QMap<int, QString> groups = GlobalData::getGroup();

    for (auto elem : groups)
    {
        int key = groups.key(elem);
        bool expand = m_group_show[key];
        addGroupItem(elem, expand);
        if (expand)
        {
            const QVector<YLFriend>& fris = friends[key];
            for (const YLFriend &fri : fris)
            {
                addFriendItem(fri);
            }
        }
    }
}


void FriendListWidget::addGroupItem(const QString &groupName, bool isExpand)
{
    FriendGroupItem *w = new FriendGroupItem;
    w->setExpand(isExpand);
    w->setGroupName(groupName);
    connect(w, &FriendGroupItem::isExpand, this, [this, w](bool flag)
    {
        int key = (GlobalData::getGroup()).key(w->getGroupName());
        m_group_show[key] = flag;
        loadFriendList();
    });


    QListWidgetItem *item = new QListWidgetItem(this);
    item->setSizeHint(QSize(225, 30));
    addItem(item);
    setItemWidget(item, w);
}


//
void FriendListWidget::addFriendItem(const YLFriend &fri, bool hide)
{
    uint32_t friendId = fri.friendId();
    FriendItem *w = new FriendItem;
    w->setFriendId(friendId);
    w->setHeadIcon(fri.friendImagePath());
    w->setFriendInfo(fri.friendRemark().isEmpty() ? fri.friendNickName() : fri.friendRemark(), fri.friendAccount());
    if (hide)
    {
        w->hideDeleteButton();
    }
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setSizeHint(QSize(260, 30));
    addItem(item);
    setItemWidget(item, w);
}


/***************************SelectedFriendListWidget****************************/
SelectedFriendListWidget::SelectedFriendListWidget(QWidget *parent) : QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(qss_this + qss_scroll_bar);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    init();
    m_selected_member = new QVector<uint32_t>();
}


SelectedFriendListWidget::~SelectedFriendListWidget()
{
    delete m_selected_member;
    qDebug() << "~SelectedFriendListWidget()";
}

void SelectedFriendListWidget::init()
{

}


void SelectedFriendListWidget::addSelf()
{
    uint32_t id = GlobalData::getCurrLoginUserId();

    FriendItem *w = new FriendItem;
    w->setFriendId(id);
    w->setHeadIcon(GlobalData::getCurrLoginUserHeadUrl());
    w->setFriendInfo(GlobalData::getCurrLoginUserNick(), GlobalData::getCurrLoginUserAccount());
    w->hideDeleteButton();

    QListWidgetItem *item2 = new QListWidgetItem(this);
    item2->setSizeHint(QSize(260, 30));
    addItem(item2);
    setItemWidget(item2, w);
}

void SelectedFriendListWidget::addOne(uint32_t friendId, bool first)
{
    if (first && isSelected(friendId))
        return;
    if (first)
        m_selected_member->push_back(friendId);
    YLFriend frie = GlobalData::getFriendById(friendId);

    FriendItem *w = new FriendItem;
    w->setFriendId(friendId);
    w->setHeadIcon(frie.friendImagePath());
    w->setFriendInfo(frie.friendRemark().isEmpty() ? frie.friendNickName() : frie.friendRemark(), frie.friendAccount());


    connect(w, &FriendItem::deleted, this, [this](uint32_t id){
        removeOne(id);
    });

    QListWidgetItem *item = new QListWidgetItem(this);
    item->setSizeHint(QSize(260, 30));
    addItem(item);
    setItemWidget(item, w);
}


void SelectedFriendListWidget::removeOne(uint32_t friendId)
{
    for (auto iter = m_selected_member->begin(); iter != m_selected_member->end(); ++iter)
    {
        if (*iter == friendId)
        {
            m_selected_member->erase(iter);
            break;
        }
    }

    loadSelectedList();
    emit remove();
}

void SelectedFriendListWidget::loadSelectedList()
{
    clear();
    addSelf();
    for (uint32_t friId : (*m_selected_member))
    {
        addOne(friId);
    }
}


bool SelectedFriendListWidget::isSelected(uint32_t friId)
{
    for (int i = 0; i < m_selected_member->size(); ++i)
    {
        if ((*m_selected_member)[i] == friId)
        {
            return true;
        }
    }

    return false;
}

/*****************************FriendItem********************************/
FriendItem::FriendItem(QWidget *parent) : QWidget(parent)
{
    setFixedSize(260, 30);
    init();
}

void FriendItem::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(26, 26);
    m_head_frame->move(24, 2);

    m_label_info = new QLabel("Haha(7796564531)", this);
    m_label_info->setFixedHeight(26);
    m_label_info->setAlignment(Qt::AlignVCenter);
    m_label_info->move(55, 2);

    m_delete = new QPushButton(this);
    m_delete->setFixedSize(16, 16);
    m_delete->move(240, 7);
    connect(m_delete, &QPushButton::clicked, this, [this](){
        emit deleted(m_friend_id);
    });
}


void FriendItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !m_delete->isVisible() && m_friend_id != GlobalData::getCurrLoginUserId())
        SignalForward::instance()->forwardInviteGroupSelected(m_friend_id);
    QWidget::mousePressEvent(event);
}

void FriendItem::setFriendId(uint32_t friId)
{
    m_friend_id = friId;
}


void FriendItem::setHeadIcon(const QString &path)
{
    m_head_frame->setHeadFromUrl(path);
}

void FriendItem::setFriendInfo(const QString &nickOrRemark, const QString &account)
{
    m_label_info->setText(QString("%1(%2)").arg(nickOrRemark).arg(account));
}

void FriendItem::hideDeleteButton()
{
    m_delete->hide();
}

/***************************FriendGroupItem****************************/
FriendGroupItem::FriendGroupItem(QWidget *parent) : QWidget(parent), m_is_expand(false)
{
    setFixedSize(260, 30);
    init();
}

void FriendGroupItem::init()
{
    m_icon = new QLabel(this);
    m_icon->setFixedSize(12, 12);
    m_icon->move(18, 9);
    m_icon->setPixmap(QPixmap(":/res/MainFrame/right.png"));

    m_add_all = new QPushButton(this);
    m_add_all->setFixedSize(16, 16);
    m_add_all->setStyleSheet(qss_add_all);
    m_add_all->move(230, 7);
    m_add_all->hide();

    m_label_group_name = new QLabel(this);
    m_label_group_name->setText("111");
    m_label_group_name->setFixedHeight(28);
    m_label_group_name->setAlignment(Qt::AlignVCenter);
    m_label_group_name->move(32, 1);
}


void FriendGroupItem::setGroupName(const QString &groupName)
{
    m_group_name = groupName;
    m_label_group_name->setText(groupName);
}


void FriendGroupItem::setExpand(bool flag)
{
    m_is_expand = flag;
    if (flag)
        m_icon->setPixmap(QPixmap(":/res/MainFrame/down.png"));
    else
        m_icon->setPixmap(QPixmap(":/res/MainFrame/right.png"));
}

void FriendGroupItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_is_expand)
            m_is_expand = false;
        else
            m_is_expand = true;

        setExpand(m_is_expand);
        emit isExpand(m_is_expand);
    }

    QWidget::mousePressEvent(event);
}

void FriendGroupItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
    }
    QWidget::mouseDoubleClickEvent(event);
}
void FriendGroupItem::enterEvent(QEvent *event)
{
    m_add_all->show();
    QWidget::enterEvent(event);
}

void FriendGroupItem::leaveEvent(QEvent *event)
{
    m_add_all->hide();
    QWidget::leaveEvent(event);
}
