#include "yladdfriendwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include "YLNetWork/ylbusiness.h"
#include "globaldata.h"
YLAddFriendWidget::YLAddFriendWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(400, 300);
    init();
    setWidgetTitle("FindFriend");
}

void YLAddFriendWidget::init()
{
    m_search_lineedit = new QLineEdit(this);
    m_search_lineedit->setFixedSize(129, 28);
    m_search_lineedit->move((width() - 170) / 2, 60);
    m_search_lineedit->setStyleSheet("QLineEdit{font: 13px;border-image:url(:/res/MainFrame/linedit_normal.png);}\
                                      QLineEdit:hover{font: 13px;border-image:url(:/res/MainFrame/linedit_hover.png);}");

    m_search_button = new QPushButton("Search", this);
    m_search_button->setFixedSize(40, 28);
    m_search_button->move((width() - 170) / 2 + 129, 60);
    connect(m_search_button, &QPushButton::clicked, this, [this](){
        YLBusiness::searchFriend(GlobalData::getCurrLoginUserId(), m_search_lineedit->text(), base::SEARCH_TYPE_NICKNAME);
    });
}
