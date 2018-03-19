#include "ylmessageeditwidget.h"
#include <QPushButton>
#include <QTextEdit>

YLMessageEditWidget::YLMessageEditWidget(QWidget *parent) : QWidget(parent)
{
    m_text_editor = new QTextEdit(this);

    m_send_button = new QPushButton("Send", this);

    m_close_bitton = new QPushButton("Close", this);

}

void YLMessageEditWidget::resizeEvent(QResizeEvent *event)
{
    m_text_editor->move(0, 0);
    m_text_editor->resize(width(), height() - 40);

    m_send_button->move(width() - 100, height() - 42);
    m_close_bitton->move(width() - 50, height() - 42);
}
