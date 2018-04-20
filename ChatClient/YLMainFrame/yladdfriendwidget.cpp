#include "yladdfriendwidget.h"
#include <QLineEdit>
#include <QPushButton>

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
    m_search_lineedit->move((width() - 350) / 2, 60);
    m_search_lineedit->setStyleSheet("QLineEdit{font: 13px;border-image:url(:/res/MainFrame/linedit_normal.png);}\
                                      QLineEdit:hover{font: 13px;border-image:url(:/res/MainFrame/linedit_hover.png);}");

    m_search_button = new QPushButton("Search", this);
    m_search_button->setFixedSize(60, 0);
    m_search_button->move((width() - 350) / 2 + 290, 60);
}
