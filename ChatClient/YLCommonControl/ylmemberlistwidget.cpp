#include "ylmemberlistwidget.h"
#include <QLabel>
#include <QHeaderView>
#include <QFontMetrics>
#include "YLCommonControl/ylheadframe.h"
YLMemberListWidget::YLMemberListWidget(QWidget *parent) : QTableWidget(parent)
{
    m_last_row_color = QColor(0x00,0xff,0x00,0x00);//透明颜色
    m_previous_color_row = -1;

    setColumnCount(3);
    setShowGrid(false);                                     //设置不显示格子线
    setFocusPolicy(Qt::NoFocus);                            //去除选中时虚线
    setFrameShape(QFrame::NoFrame);                         //设置无边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   //关闭水平滚动条
    setSelectionBehavior(QAbstractItemView::SelectRows);    //设置选择行为为 以行为单位
    setSelectionMode(QAbstractItemView::SingleSelection);   //设置选择模式为单行选中
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //禁止编辑
    setMouseTracking(true);

    QStringList list;
    list << "成员" << "群名片" << "最后一次发言时间";
    setHorizontalHeaderLabels(list);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:#ECECEC;color: #777777;padding-left:5px;padding-top:3px; padding-bottom:3px;;border: 0px; font:12px;}"
                                      "QHeaderView::section:checked{background-color:#ECECEC;color: #777777;padding-left:5px;padding-top:3px; padding-bottom:3px;border: 0px; font:12px;}");

    verticalHeader()->hide();

    //设置每列的宽度
    setColumnWidth(0, 130);
    setColumnWidth(1, 95);
    setColumnWidth(2, 170);

    setStyleSheet("QTableView::item:selected{background-color:#F5F5F5;}QTableView::item{color:#777777;}" + qss_scroll_bar);

    connect(this,SIGNAL(cellEntered(int,int)),this,SLOT(cellEntered(int,int)));
}

YLMemberListWidget::~YLMemberListWidget()
{

}

void YLMemberListWidget::setRow(const QString &name, MemberNameWidgetItem::MemberType type, const QString &groupNick, const QString &lastChatTime)
{
    int row = rowCount();
    insertRow(row);

    QTableWidgetItem *c1 = new QTableWidgetItem;
    c1->setSizeHint(QSize(130, 30));
    setItem(row, 0, c1);

    MemberNameWidgetItem *w1 = new MemberNameWidgetItem;
    w1->setMemberName(name);
    w1->setMemberType(type);
    setCellWidget(rowCount() - 1, 0, w1);

    QTableWidgetItem *c2 = new QTableWidgetItem;
    c2->setText(groupNick);
    c2->setTextAlignment(Qt::AlignCenter);
    setItem(row, 1, c2);


    QTableWidgetItem *c3 = new QTableWidgetItem;
    c3->setText(lastChatTime);
    c3->setTextAlignment(Qt::AlignCenter);
    setItem(row, 2, c3);
}


void YLMemberListWidget::leaveEvent(QEvent *event)
{
    QTableWidgetItem *currentItem = item(m_previous_color_row, 0);
    if (currentItem != nullptr)
    {
        setRowColor(m_previous_color_row, m_last_row_color);
    }
}

void YLMemberListWidget::cellEntered(int row, int column)
{
    QTableWidgetItem *currentItem =  item(m_previous_color_row, 0);
    if (currentItem != nullptr)
    {
        setRowColor(m_previous_color_row, m_last_row_color);
    }

    //设置当前行的颜色
    currentItem = item(row, column);
    if (currentItem != nullptr && !currentItem->isSelected())
    {
        setRowColor(row, QColor(193,210,240));
    }

    //设置行的索引
    m_previous_color_row = row;
}

void YLMemberListWidget::setRowColor(int row, QColor color)
{
    for (int col = 0; col < columnCount(); col++)
       {
           QTableWidgetItem *currentItem = item(row, col);
           currentItem->setBackgroundColor(color);
       }
}

/*******************MemberListWidgetItem*********************/
MemberNameWidgetItem::MemberNameWidgetItem(QWidget *parent) : QWidget(parent)
{
    setFixedSize(130, 30);
    init();
}

MemberNameWidgetItem::~MemberNameWidgetItem()
{

}

void MemberNameWidgetItem::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(25, 25);
    m_head_frame->move(22, 2);

    m_member_type = new QLabel(this);
    m_member_type->setFixedSize(16, 16);
    m_member_type->move(3, 7);

    m_member_name = new QLabel(this);
    m_member_name->setFixedSize(70, 20);
    m_member_name->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    setMemberName("我是谁的某2某12345");
    m_member_name->move(50, 5);
}


void MemberNameWidgetItem::setMemberType(MemberType type)
{
    if (type == GROUPMANAGER)
    {
        m_member_type->setPixmap(QPixmap(":/res/MainFrame/trad_girl.png"));
    }
    else if (type == GROUPOWER)
    {
        m_member_type->setPixmap(QPixmap(":/res/MainFrame/trad_boy.png"));
    }
}


void MemberNameWidgetItem::setMemberName(const QString &name)
{
    //校验昵称长度，如果超过label width则使用 '...'
    QString memberName = name;
    QFontMetrics fontMetrics(m_member_name->font());
    int strWidth = fontMetrics.width(memberName);

    if (strWidth > 70)
    {
        memberName += "...";
        while (strWidth > 70) {
            memberName = memberName.remove(memberName.length() - 4, 1);
            strWidth = fontMetrics.width(memberName);
        }
    }

    m_member_name->setText("<p style='color:#777'>" + memberName + "</p>");
}


