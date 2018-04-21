#include "yladdfriendwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>
#include <QLabel>
#include "YLNetWork/ylbusiness.h"
#include "globaldata.h"
#include "ylfriendinfowidget.h"
#include "YLNetWork/pduhandler.h"
YLAddFriendWidget::YLAddFriendWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(600, 480);
    init();
    init_table_widget();
    setWidgetTitle("FindFriend");
    setWidgetIcon(":/res/MainFrame/logo.png");
    connect(PduHandler::instance(), &PduHandler::searchResult, this, &YLAddFriendWidget::friends);
    showNoResultTip(false);
}

void YLAddFriendWidget::init()
{
    m_search_lineedit = new QLineEdit(this);
    m_search_lineedit->setFixedSize(400, 28);
    m_search_lineedit->move((width() - 480) / 2, 60);
    m_search_lineedit->setStyleSheet("QLineEdit{font: 13px;border:2px solid #D0E9FF;}\
                                      QLineEdit:hover{font: 13px;border:2px solid #1DB0B8;}");

    m_search_button = new QPushButton("Search", this);
    m_search_button->setFixedSize(80, 28);
    m_search_button->move((width() - 480) / 2 + 400, 60);
    connect(m_search_button, &QPushButton::clicked, this, [this](){
        base::SearchType type = base::SEARCH_TYPE_ACCOUNT;
        if (m_search_by_nickname->isChecked())
            type = base::SEARCH_TYPE_NICKNAME;
        YLBusiness::searchFriend(GlobalData::getCurrLoginUserId(), m_search_lineedit->text(), type);
    });

    m_search_by_account = new QRadioButton("Account", this);
    m_search_by_account->move((width() - 480) / 2 + 60, 90);
    m_search_by_account->setStyleSheet(qss_radio);
    m_search_by_account->setChecked(true);

    m_search_by_nickname = new QRadioButton("NickName", this);
    m_search_by_nickname->move((width() - 480) / 2 + 200, 90);
    m_search_by_nickname->setStyleSheet(qss_radio);

    m_label_icon = new QLabel(this);
    m_label_icon->setPixmap(QPixmap(":/res/YLAddFriendWIdgets/no_result.png"));
    m_label_icon->setFixedSize(250, 250);
    m_label_icon->move(175, 145);

    m_label_tips = new QLabel("<p style='color:#bfbfbf; font:16px;'>没有找到符合条件的用户</p>", this);
    m_label_tips->move(205, 405);
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
            YLFriendInfoWidget *w = new YLFriendInfoWidget;/*
            QTableWidgetItem  *item = new QTableWidgetItem;
            m_table_widget->setItem(row, column, item);*/
            w->setType(type);
            w->setFriend(fris[row * 3 + column]);
            m_table_widget->setCellWidget(row, column, w);
        }
    }
}
