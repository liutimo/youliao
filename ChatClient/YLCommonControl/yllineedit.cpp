#include "yllineedit.h"
#include <QPushButton>
YLLineEdit::YLLineEdit(QWidget *parent) : QLineEdit(parent)
{
    init();
}

void YLLineEdit::init()
{
    button_custom_ = new QPushButton(this);
    button_custom_->setObjectName("button_custom_");
    button_custom_->resize(30, 30);
    connect(button_custom_, &QPushButton::clicked, this, [this](){
        emit button_clicked();
    });

    resize(200, 30);
}

void YLLineEdit::setButtonIcon(const QString &normalPath, const QString &hoverPath, const QString &pressedPath)
{
    button_custom_->setStyleSheet(qss_custom_button_.arg(normalPath, hoverPath, pressedPath));
}

void YLLineEdit::setButtonSize(const QSize &size)
{
    button_custom_->resize(size);
}

void YLLineEdit::resizeEvent(QResizeEvent *event)
{
    int w = button_custom_->width();
    int h = button_custom_->height();
    button_custom_->move(width() - w, (height() - h) / 2);

    QLineEdit::resizeEvent(event);
}
