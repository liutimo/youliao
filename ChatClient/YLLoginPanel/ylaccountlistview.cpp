#include "ylaccountlistview.h"

#include "YLCommonControl/ylheadframe.h"
#include <QLabel>
#include <QPushButton>

YLAccountListView::YLAccountListView(QWidget *parent) : QListWidget(parent)
{
    //取消选中效果
    setFocusPolicy(Qt::NoFocus);
    setSelectionMode(QAbstractItemView::NoSelection);
    setWindowFlags(Qt::FramelessWindowHint);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(qss_this);

    hide();
}

void YLAccountListView::setData(const QVector<QStringList> &data)
{
    for (auto str_list : data)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(200, 40));
        addItem(item);
        YLAccountListViewItem *item_widget = new YLAccountListViewItem;
        item_widget->setHeadPicture(str_list[0]);
        item_widget->setNickName(str_list[1]);
        item_widget->setAccount(str_list[2]);
        setItemWidget(item, item_widget);

        connect(item_widget, &YLAccountListViewItem::selected, this, [this](const QString &account){
            emit selected(account);
            this->hide();
        });
    }

    unsigned int size = data.size() * 40;

    resize(QSize(200, size > 120 ?  120 : size));
}

void YLAccountListView::focusOutEvent(QFocusEvent *event)
{
    this->hide();
    QListWidget::focusOutEvent(event);
}

//-------------------------------------------------------------------------------
YLAccountListViewItem::YLAccountListViewItem(QWidget *parent) : QWidget(parent)
{
    init();

    setAccount("779564531");
    setNickName("刘提莫");
}

void YLAccountListViewItem::init()
{
    head_frame_ = new YLHeadFrame(this);
    head_frame_->resize(34, 34);

    label_account_ = new QLabel(this);
    label_account_->setObjectName("label_account_");
    label_account_->setStyleSheet(qss_account_label);

    label_nick_name_ = new QLabel(this);

    button_delete_ = new QPushButton(this);
    button_delete_->resize(20, 20);
    button_delete_->setObjectName("button_delete_");
    button_delete_->setStyleSheet(qss_delete_button);
    button_delete_->setTabletTracking(true);
    button_delete_->hide();
    connect(button_delete_, &QPushButton::clicked, this, [this]()
    {
        emit deleteItem(label_account_->text());
    });

    this->setObjectName("YLAccountListViewItem");
}

void YLAccountListViewItem::setHeadPicture(const QString &path)
{
    head_frame_->setHeadFromLocal(path);
}

void YLAccountListViewItem::setNickName(const QString &nickname)
{
    label_nick_name_->setText(nickname);
}

void YLAccountListViewItem::setAccount(const QString &account)
{
    label_account_->setText(account);
}

void YLAccountListViewItem::resizeEvent(QResizeEvent *event)
{
    head_frame_->move(5, 3);
    label_nick_name_->move(50, 0);
    label_account_->move(50, 20);
    button_delete_->move(width() - 35, 10);
    QWidget::resizeEvent(event);
}

void YLAccountListViewItem::enterEvent(QEvent *event)
{
    button_delete_->show();
    QWidget::enterEvent(event);
}

void YLAccountListViewItem::leaveEvent(QEvent *event)
{
    button_delete_->hide();
    QWidget::leaveEvent(event);
}

void YLAccountListViewItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit selected(label_account_->text());
}

void YLAccountListViewItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit selected(label_account_->text());
}
