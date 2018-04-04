#include "test.h"
#include <QWebEnginePage>
#include <QMenu>
#include <QAction>
Test::Test(QObject *parent) : QObject(parent)
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
}


void Test::showContentPMenu(const QString &text)
{
    m_p_menu->exec(QCursor::pos());
}
