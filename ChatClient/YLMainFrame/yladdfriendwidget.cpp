#include "yladdfriendwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include "YLNetWork/ylbusiness.h"
#include "globaldata.h"
YLAddFriendWidget::YLAddFriendWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(600, 480);
    init();
    setWidgetTitle("FindFriend");
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
}
