#include "ylmainwidget.h"
#include "YLCommonControl/ylheadandstatusframe.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include "ylsearchlineedit.h"
#include "ylsignaturelineedit.h"
#include "ylnavigationbar.h"

YLMainWidget::YLMainWidget(QWidget *parent) : YLBasicWidget(parent)
{
    resize(400, 800);
    init();
}

void YLMainWidget::init()
{
    min_button_ = new QPushButton(this);
    min_button_->resize(close_button_->size());
    min_button_->setObjectName("min_button_");
    min_button_->setStyleSheet(qss_min_button);

    skin_button_ = new QPushButton(this);
    skin_button_->resize(close_button_->size());
    skin_button_->setObjectName("skin_button_");
    skin_button_->setStyleSheet(qss_skin_button);

    logo_label_ = new QLabel(this);
    logo_label_->setObjectName("logo_label_");
    logo_label_->setStyleSheet(qss_logo_label);
    logo_label_->resize(QSize(21, 24));

    head_status_frame_  = new YLHeadAndStatusFrame(this);
    head_status_frame_->resize(80, 80);

    nickname_label_ = new QLabel(this);
    nickname_label_->setText("hahaha");
    nickname_label_->setObjectName("nickname_label_");
    nickname_label_->setStyleSheet(qss_nickname_label);

    signature_lineedit_ = new YLSignatureLineEdit(this);
    signature_lineedit_->setText("我是谁！！！");
    signature_lineedit_->resize(width() - 145, 30);

    search_lineedit_ = new YLSearchLineEdit(this);
    search_lineedit_->resize(width() - 1, 40);

    navigation_bar_ = new YLNavigationBar(this);
    navigation_bar_->resize(width() - 1, 40);
    connect(navigation_bar_, &YLNavigationBar::click_index, this, [this](int index){
        for (int i = 0; i < vec.size(); ++i)
        {
            if (i == index - 1)
                vec[i]->show();
            else
                vec[i]->hide();
        }
    });


    QLabel *l = new QLabel("1111", this);

    vec.push_back(l);
    vec.push_back(new QLabel("2222", this));
    vec.push_back(new QLabel("3333", this));
}


void YLMainWidget::resizeEvent(QResizeEvent *event)
{
    //因为要使用close_button的位置，此处需要先调用父类的resizeEvent
    YLBasicWidget::resizeEvent(event);
    min_button_->move(close_button_->x() - close_button_->width(), 0);
    skin_button_->move(min_button_->x() - min_button_->width(), 0);
    logo_label_->move(8, 8);
    head_status_frame_->move(25, 50);
    nickname_label_->move(115, 50);
    signature_lineedit_->move(115, 90);
    search_lineedit_->move(0, 140);
    navigation_bar_->move(0, 180);

}

void YLMainWidget::mousePressEvent(QMouseEvent *event)
{
    min_button_->setFocus();
    YLBasicWidget::mousePressEvent(event);
}

void YLMainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromHsv(123, 122, 155, 122));
    p.drawRect(rect());
}
