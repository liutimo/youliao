#include "ylquickbar.h"
#include <QPushButton>
#include "ylemoticonwidget.h"
YLQuickBar::YLQuickBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(26);
    init();
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
        YLEmoticonWidget *w = new  YLEmoticonWidget;
        QPoint point = m_face_btn->mapToGlobal(m_face_btn->rect().topLeft());
        w->move(point.x(), point.y() - 230);
        w->show();
    });
}
