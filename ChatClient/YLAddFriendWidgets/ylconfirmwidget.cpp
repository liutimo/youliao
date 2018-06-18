#include "ylconfirmwidget.h"
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QPainter>
#include "globaldata.h"
#include "YLNetWork/ylbusiness.h"
YLConfirmWidget::YLConfirmWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(275, 180);
    setWidgetTitle("添加好友");
    setWidgetIcon(":/res/qqlogo.png");
    setAttribute(Qt::WA_DeleteOnClose);
    m_remark = new QLabel("备注姓名:", this);
    m_remark->move(10, 50);
    m_group = new QLabel("分         组:", this);
    m_group->move(10, 80);

    m_line_edit = new QLineEdit(this);
    m_line_edit->setFixedSize(180, 25);
    m_line_edit->move(65, 48);

    m_combo_box = new QComboBox(this);
    m_combo_box->setFixedSize(180, 25);
    m_combo_box->move(65, 78);
    m_combo_box->setStyleSheet("QComboBox{border:1px solid gray;}QComboBox:hover{border:1px solid #1583DD;}QComboBox::drop-down {\
                               subcontrol-origin: padding;subcontrol-position: top right;width: 20px;border-left-width: 0px;}\
                               QComboBox::down-arrow {image: url(:/res/YLCommonControl/arrow_down.png);}\
                               QComboBox::item {color:black;height: 25px;background: white;}\
                               QComboBox::item:hover {color:black;height: 25px; background: red;}QListView::item:hover {background: #BDD7FD;}");

    for(auto groupName : GlobalData::getGroup())
    {
        m_combo_box->addItem(groupName);
    }

    m_confirm = new QPushButton("确定", this);
    m_confirm->setFixedSize(69, 24);
    m_confirm->move(190, 145);
    m_confirm->setStyleSheet(qss_confirm_button);

    connect(m_confirm, &QPushButton::clicked, this, [this](){
        uint32_t groupId = GlobalData::getGroupIdByName(m_combo_box->currentText());
        YLBusiness::addFriendRespone(m_other_id, 1, groupId, m_line_edit->text());
        emit complete();
        close();
    });
}



YLConfirmWidget::~YLConfirmWidget()
{
    qDebug() << "~YLConfirmWidget();";
}


void YLConfirmWidget::paintEvent(QPaintEvent *event)
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
