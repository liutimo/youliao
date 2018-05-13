#include "ylchatlistwidget.h"
#include "YLCommonControl/ylsearchlineedit.h"
#include "YLCommonControl/ylheadframe.h"
#include "ylsinglechatwidget.h"
#include <QLabel>
#include <QSplitter>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QFontMetrics>
YLChatListWidget::YLChatListWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setMouseTracking(true);
    resize(1050, 702);

    p = new QSplitter(this);
    p->resize(1050, 670);
    p->move(0, 52);
    p->setChildrenCollapsible(false);

    connect(p, &QSplitter::splitterMoved, this, [this](int pos, int index)
    {
        if (index == 1)
        {
            m_search_lineedit->resize(pos - 20, m_search_lineedit->height());
            update();
        }
    });


    LeftChildWidget *l1 = new LeftChildWidget(this);
    l1->setMinimumWidth(70);
    l1->setMaximumWidth(250);
    connect(l1, &LeftChildWidget::leftItemChanged, this, [this](const QString name){
        setName(name);
    });


    m_search_lineedit = new YLSearchLineEdit(this);
    m_search_lineedit->move(10, 10);
    m_search_lineedit->setFocusPolicy(Qt::ClickFocus);

    m_signle_chat_widget = new YLSingleChatWidget(this);

    p->addWidget(l1);
    p->addWidget(m_signle_chat_widget);

    m_name = new QPushButton(this);
    m_name->setStyleSheet("border:0px;");
    QFont f = m_name->font();
    f.setPixelSize(18);
    m_name->setFont(f);
    m_name->setFixedSize(500, 30);
    m_name->move(252, 5);

    l1->setFocus();
    QWidget::setTabOrder(l1, m_signle_chat_widget);
    QWidget::setTabOrder(m_signle_chat_widget, l1);
}

void YLChatListWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor::fromRgb(25, 156, 107));    //#31A66B
    painter.drawRect(0, 0, p->widget(0)->width(), height());

}


void YLChatListWidget::setName(const QString &name)
{
    QFontMetrics fm(m_name->font());
    m_name->setFixedWidth(fm.width(name));
    m_name->setText(name);
}

/*******************LeftChildWidget*******************/
LeftChildWidget::LeftChildWidget(QWidget *parent) : QWidget(parent), m_current_selected_id(0)
{
    setMouseTracking(true);
    init();
}

LeftChildWidget::~LeftChildWidget()
{
    qDebug() << "析构LeftChildWidget";
    delete m_vertical_layout;
}

void LeftChildWidget::init()
{
    m_vertical_layout = new QVBoxLayout(this);
    m_vertical_layout->setSizeConstraint(QLayout::SetNoConstraint);
    m_vertical_layout->setSpacing(0);
    m_vertical_layout->setMargin(0);
    setLayout(m_vertical_layout);

    QStringList list;
    list << "温柔" << "五月天" << "阿信" << "知足" << "改变";
    for (int i = 0; i < 5; ++i)
    {
        ChildWidgetItem *item = new ChildWidgetItem(this);
        connect(item, &ChildWidgetItem::selectedId, this, [this](int id){
            qDebug() << id;
            m_child_items[id]->setSelected();
            m_child_items[m_current_selected_id]->setSelected(false);
            m_current_selected_id = id;
            emit leftItemChanged(static_cast<ChildWidgetItem*>(sender())->getName());
        });
        item->setId(i);
        item->setName(list.at(i));
        m_vertical_layout->addWidget(item);
        m_child_items[i] = item;
    }
    m_vertical_layout->addStretch();
    m_child_items[0]->setSelected();
}


void LeftChildWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}


/*******************LeftChildWidget*******************/
ChildWidgetItem::ChildWidgetItem(QWidget *parent) : QWidget(parent), m_index(0), m_hover(false), m_selected(false)
{
    setMouseTracking(true);
    setMinimumHeight(56);
    init();
}

ChildWidgetItem::~ChildWidgetItem()
{

}

void ChildWidgetItem::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(46, 46);

    m_name = new QLabel("刘提莫", this);
    m_name->setAlignment(Qt::AlignVCenter);
    m_name->setStyleSheet("color:white;");

    m_latest_time = new QLabel("11:09", this);
    m_latest_time->setAlignment(Qt::AlignVCenter);
    m_latest_time->setStyleSheet("color:#A4A4A4;");

    m_latest_msg = new QLabel("你好！！！！！！！1111111111！！好", this);
    m_latest_msg->setAlignment(Qt::AlignVCenter);
    m_latest_msg->setStyleSheet("color:#A4A4A4;");

    m_close_button = new QPushButton(this);
    m_close_button->setFixedSize(25, 25);
    m_close_button->setStyleSheet(m_qss_close_btn);
    m_close_button->hide();
    connect(m_close_button, &QPushButton::clicked, this, [this]()
    {
        close();
    });

    m_grid_layout = new QGridLayout(this);
    m_grid_layout->addWidget(m_head_frame, 0, 0, 2,  2);
    m_grid_layout->addWidget(m_name, 0, 2, 1, 4);
    m_grid_layout->addWidget(m_latest_time, 0, 6, 1, 1);
    m_grid_layout->addWidget(m_latest_msg, 1, 2, 1, 5);
    m_grid_layout->setSpacing(0);
    m_grid_layout->setMargin(0);
    m_grid_layout->setSizeConstraint(QLayout::SetNoConstraint);
    setLayout(m_grid_layout);

}

void ChildWidgetItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_selected = true;
        update();
        emit selectedId(m_id);
    }
    QWidget::mousePressEvent(event);
}

void ChildWidgetItem::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (width() < 80 && m_index != 1)
    {
        m_index = 1;
        m_latest_msg->hide();
        m_latest_time->hide();
        m_name->hide();
    }
    else if (width() >= 80 &width() <= 190 && m_index != 2)
    {
        m_index = 2;
        m_name->show();
        m_latest_msg->hide();
        m_latest_time->hide();
        m_grid_layout->removeWidget(m_latest_msg);
        m_grid_layout->removeWidget(m_latest_time);
        m_grid_layout->removeWidget(m_name);
        m_grid_layout->addWidget(m_name, 0, 2, 2, 5);
    }
    else if (width() > 190 && m_index != 3)
    {
        m_index = 3;
        m_name->show();
        m_latest_msg->show();
        m_latest_time->show();
        m_grid_layout->addWidget(m_head_frame, 0, 0, 2,  2);
        m_grid_layout->addWidget(m_name, 0, 2, 1, 4);
        m_grid_layout->addWidget(m_latest_time, 0, 6, 1, 1);
        m_grid_layout->addWidget(m_latest_msg, 1, 2, 1, 5);
    }
    QWidget::resizeEvent(event);
}

void ChildWidgetItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    if (m_selected)
        painter.setBrush(QColor::fromRgb(216, 216, 216, 200));      //#E6E6E6
    else
        painter.setBrush(QColor::fromRgb(255, 255, 255, 0));

    if (m_hover && !m_selected)
        painter.setBrush(QColor::fromRgb(210, 210, 210, 100));  //#F0F0F0
    else if (!m_selected)
        painter.setBrush(QColor::fromRgb(255, 255, 255, 0));

    painter.drawRect(rect());
    QWidget::paintEvent(event);
}

void ChildWidgetItem::leaveEvent(QEvent *event)
{
    m_close_button->hide();
    m_grid_layout->removeWidget(m_close_button);
    m_grid_layout->addWidget(m_latest_msg, 1, 2, 1, 5);

    m_hover = false;
    update();
    QWidget::leaveEvent(event);
}

void ChildWidgetItem::enterEvent(QEvent *event)
{
    m_close_button->show();
    m_grid_layout->addWidget(m_close_button, 1, 6, 1, 1);

    m_hover = true;
    update();
    QWidget::enterEvent(event);
}


void ChildWidgetItem::setFriend(const YLFriend &fri)
{
    m_friend = fri;
}

void ChildWidgetItem::setGroup (const YLGroup &group)
{
    m_group = group;
}

void ChildWidgetItem::setName(const QString &name)
{
    m_name->setText(name);
}


QString ChildWidgetItem::getName() const
{
    return m_name->text();
}

ChildWidgetItem::ItemType ChildWidgetItem::getItemType()
{
    if (m_friend.friendId() != 0)
        return ChildWidgetItem::FRIEND;
    else if (m_group.getGroupId() != 0)
        return ChildWidgetItem::GROUP;

}
