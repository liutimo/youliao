#include "test.h"
#include "ylmessageview.h"
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QClipboard>
#include <QGuiApplication>

Test::Test(QObject *parent) : QObject(parent), m_message_id(0), m_load_more_is_emit(false)
{
    initPMenu();
}

void Test::setView(YLMessageView *view)
{
    m_view = view;
}

void Test::initPMenu()
{
    m_p_menu = new QMenu();

    QAction *copy_action = new QAction("Copy");
    m_p_menu->addAction(copy_action);
//    connect(copy_action, &QAction::triggered, this, [this](){
//        QClipboard *cb = QGuiApplication::clipboard();
//        cb->setText(m_page->selectedText());
//    });
}


void Test::playAudio(uint32_t msgId)
{
    m_message_id = msgId;
    emit startPlayAudio(msgId);
}


void Test::showContentPMenu(uint32_t msgId)
{
    m_message_id = msgId;
    m_p_menu->exec(QCursor::pos());
}


void Test::loadMore()
{
    qDebug() << "load more";
    m_view->loadMore();

}
