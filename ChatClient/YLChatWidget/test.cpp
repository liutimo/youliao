#include "test.h"
#include <QWebEnginePage>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QClipboard>
#include <QGuiApplication>

Test::Test(QObject *parent) : QObject(parent), m_message_id(0)
{
    initPMenu();
}

void Test::setPage(QWebEnginePage *page)
{
    m_page = page;

//    connect(m_page, &QWebEnginePage::selectionChanged, [this](){qDebug() << m_page->selectedText();});
}

void Test::initPMenu()
{
    m_p_menu = new QMenu();

    QAction *copy_action = new QAction("Copy");
    m_p_menu->addAction(copy_action);
    connect(copy_action, &QAction::triggered, this, [this](){
        QClipboard *cb = QGuiApplication::clipboard();
        cb->setText(m_page->selectedText());
    });
   }


void Test::showContentPMenu(uint32_t msgId)
{
    m_message_id = msgId;
    m_p_menu->exec(QCursor::pos());
}


void Test::loadMore()
{
    qDebug() << "load more";
}
