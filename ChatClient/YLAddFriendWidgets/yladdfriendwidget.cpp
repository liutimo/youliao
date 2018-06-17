#include "yladdfriendwidget.h"
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QScrollBar>
#include <QPushButton>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QTableWidget>
#include <QButtonGroup>

#include "globaldata.h"
#include "ylgroupwidget.h"
#include "ylfriendinfowidget.h"
#include "YLNetWork/ylbusiness.h"
#include "YLNetWork/pduhandler.h"

YLAddFriendWidget::YLAddFriendWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(600, 480);
    init();
    init_table_widget();
    setWidgetTitle("查找");
    setWidgetIcon(":/res/qqlogo.png");
    connect(PduHandler::instance(), &PduHandler::searchResult, this, &YLAddFriendWidget::friends);
    connect(PduHandler::instance(), &PduHandler::searchGroupResult, this, &YLAddFriendWidget::groups);
    showNoResultTip(false);
}

void YLAddFriendWidget::init()
{
    m_search_lineedit = new QLineEdit(this);
    m_search_lineedit->setFixedSize(400, 28);
    m_search_lineedit->move((width() - 480) / 2, 60);
    m_search_lineedit->setStyleSheet("QLineEdit{font: 13px;border:2px solid #D0E9FF;}\
                                      QLineEdit:hover{font: 13px;border:2px solid #1DB0B8;}");

    m_search_button = new QPushButton("查找", this);
    m_search_button->setFixedSize(80, 28);
    m_search_button->move((width() - 480) / 2 + 400, 60);
    m_search_button->setStyleSheet("border:0px; color:white; background:#009BDB;");

    connect(m_search_button, &QPushButton::clicked, this, [this](){
        base::SearchType type = base::SEARCH_TYPE_ACCOUNT;
        if (m_search_by_nickname->isChecked())
            type = base::SEARCH_TYPE_NICKNAME;
        if (m_search_friend->isChecked())
            YLBusiness::searchFriend(GlobalData::getCurrLoginUserId(), m_search_lineedit->text(), type);
        else
            YLBusiness::searchGroup(m_search_lineedit->text(), type);
    });

    m_search_by_account = new QRadioButton("按账号", this);
    m_search_by_account->move(120, 90);
    m_search_by_account->setStyleSheet(qss_radio);

    m_search_by_nickname = new QRadioButton("按昵称", this);
    m_search_by_nickname->move(190, 90);
    m_search_by_nickname->setStyleSheet(qss_radio);

    m_search_friend = new QRadioButton("好友", this);
    m_search_friend->move(325, 90);
    m_search_friend->setStyleSheet(qss_radio);


    m_search_group = new QRadioButton("群组", this);
    m_search_group->move(390, 90);
    m_search_group->setStyleSheet(qss_radio);

    m_label_icon = new QLabel(this);
    m_label_icon->setPixmap(QPixmap(":/res/YLAddFriendWIdgets/no_result.png"));
    m_label_icon->setFixedSize(250, 250);
    m_label_icon->move(175, 145);

    m_label_tips = new QLabel("<p style='color:#bfbfbf; font:16px;'>没有找到符合条件的用户</p>", this);
    m_label_tips->move(205, 405);

    m_mode = new QLabel("搜索方式:", this);
    m_mode->setAlignment(Qt::AlignHCenter | Qt::AlignLeft);
    m_mode->move(60, 90);

    m_type = new QLabel("搜索类型:", this);
    m_type->setAlignment(Qt::AlignHCenter | Qt::AlignLeft);
    m_type->move(270, 90);


    m_search_mode = new QButtonGroup(this);
    m_search_mode->addButton(m_search_by_account, 1);
    m_search_mode->addButton(m_search_by_nickname, 2);

    m_search_type = new QButtonGroup(this);
    m_search_type->addButton(m_search_friend, 1);
    m_search_type->addButton(m_search_group, 2);

    m_search_by_account->setChecked(true);
    m_search_friend->setChecked(true);
}

void YLAddFriendWidget::init_table_widget()
{
    m_table_widget = new QTableWidget(this);
    m_table_widget->setFixedSize(580, 340);
    m_table_widget->move(10, 130);

    m_table_widget->horizontalHeader()->hide();
    m_table_widget->verticalHeader()->hide();

    m_table_widget->setShowGrid(false);
    m_table_widget->setFocusPolicy(Qt::NoFocus);
    m_table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table_widget->setSelectionMode(QAbstractItemView::NoSelection);
    m_table_widget->horizontalHeader()->setDefaultSectionSize(200);
    m_table_widget->verticalHeader()->setDefaultSectionSize(100);
    m_table_widget->horizontalScrollBar()->hide();
    m_table_widget->verticalScrollBar()->hide();

    m_table_widget->setStyleSheet(qss_table_widget);
}

void YLAddFriendWidget::showNoResultTip(bool show)
{
   if (show)
   {
       m_label_tips->show();
       m_label_icon->show();
       m_table_widget->hide();
   }
   else
   {
       m_label_tips->hide();
       m_label_icon->hide();
       m_table_widget->show();
   }
}

void YLAddFriendWidget::friends(const QVector<YLFriend> &fris)
{
    m_table_widget->clear();

    m_table_widget->horizontalHeader()->setDefaultSectionSize(200);
    m_table_widget->verticalHeader()->setDefaultSectionSize(100);
    if (fris.size() == 0)
    {
        showNoResultTip();
        return;
    }
    else
        showNoResultTip(false);


    int rows = fris.size() / 3 + 1;

    int columns = 3;

    m_table_widget->setColumnCount(columns);
    m_table_widget->setRowCount(rows);

    base::SearchType type = base::SEARCH_TYPE_ACCOUNT;
    if (m_search_by_nickname->isChecked())
        type = base::SEARCH_TYPE_NICKNAME;

    for (int row = 0; row < rows; ++row)
    {
        for (int column = 0; column < columns; ++column)
        {
            if (row * 3 + column == fris.size())
                break;
            YLFriendInfoWidget *w = new YLFriendInfoWidget;
            w->setType(type);
            w->setFriend(fris[row * 3 + column]);
            m_table_widget->setCellWidget(row, column, w);
        }
    }
}


void YLAddFriendWidget::groups(const QVector<YLGroup> &groups)
{
    m_table_widget->clear();

    m_table_widget->horizontalHeader()->setDefaultSectionSize(230);
    m_table_widget->verticalHeader()->setDefaultSectionSize(130);
    if (groups.size() == 0)
    {
        showNoResultTip();
        return;
    }
    else
        showNoResultTip(false);


    int rows = groups.size() / 2 + 1;

    int columns = 2;

    m_table_widget->setColumnCount(columns);
    m_table_widget->setRowCount(rows);


    for (int row = 0; row < rows; ++row)
    {
        for (int column = 0; column < columns; ++column)
        {
            if (row * 2 + column == groups.size())
                break;
            YLGroupWidget *w = new YLGroupWidget;
            w->setGroup(groups[row * 2 + column]);
            m_table_widget->setCellWidget(row, column, w);
        }
    }
}


void YLAddFriendWidget::paintEvent(QPaintEvent *event)
{
    const int titleBarHeight = 32;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);


    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    painter.setBrush(QColor::fromRgb(40, 138, 221));           //#288ADD
    painter.drawRect(0, 0, width(), titleBarHeight);


    painter.setBrush(QColor::fromRgb(234,241,248));            //#EAF1F8
    painter.drawRect(0, titleBarHeight, width(), height() - titleBarHeight);
}

