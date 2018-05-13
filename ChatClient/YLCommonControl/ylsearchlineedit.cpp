#include "ylsearchlineedit.h"

#include <QLabel>
#include <QPushButton>

YLSearchLineEdit::YLSearchLineEdit(QWidget *parent) : QLineEdit(parent)
{
    init();
}

void YLSearchLineEdit::init()
{

    setObjectName("YLSearchLineEdit_this");
    setStyleSheet(qss_this_no_edit);
    setPlaceholderText("搜索");

    search_label_ = new QLabel(this);
    search_label_->setFixedSize(20, 20);
    search_label_->setObjectName("search_label_");
    search_label_->setStyleSheet(qss_search_label);

    delete_button_ = new QPushButton(this);
    delete_button_->setFixedSize(22, 22);
    delete_button_->setObjectName("delete_button_");
    delete_button_->setStyleSheet(qss_delete_buton);
    delete_button_->hide();
    connect(delete_button_, &QPushButton::clicked, this, &YLSearchLineEdit::on_delete);

}

void YLSearchLineEdit::resizeEvent(QResizeEvent *event)
{
    search_label_->move(10, (height() - 20) /2);
    delete_button_->move(width() - 30, (height() - 22) / 2);
    QLineEdit::resizeEvent(event);
}

void YLSearchLineEdit::focusInEvent(QFocusEvent *event)
{
    setStyleSheet(qss_this_on_edit);
    delete_button_->show();
    setPlaceholderText("");
    QLineEdit::focusInEvent(event);
}

void YLSearchLineEdit::focusOutEvent(QFocusEvent *event)
{
    setStyleSheet(qss_this_no_edit);
    clear();
    setPlaceholderText("搜索");
    delete_button_->hide();

    QLineEdit::focusOutEvent(event);
}


void YLSearchLineEdit::on_delete()
{
    delete_button_->hide();
    clear();
}
