#include "ylquickbar.h"
#include <QPushButton>
#include "ylemoticonwidget.h"
YLQuickBar::YLQuickBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(26);
    init();
    m_emoticon_widget = new  YLEmoticonWidget();
    m_emoticon_widget->hide();

}


void YLQuickBar::init()
{
    m_face_btn = new QPushButton(this);
    m_face_btn->setObjectName("face_btn");
    m_face_btn->setFixedSize(20, 20);
    m_face_btn->setStyleSheet(m_qss_face_btn);
    connect(m_face_btn, &QPushButton::clicked, this, [this](){
        if (YLEmoticonWidget::isShow)
            return;
        QPoint point = m_face_btn->mapToGlobal(m_face_btn->rect().topLeft());
        m_emoticon_widget->move(point.x(), point.y() - 230);
        m_emoticon_widget->show();
        installEventFilter(m_emoticon_widget);
    });
}

