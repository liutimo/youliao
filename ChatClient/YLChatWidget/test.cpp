#include "test.h"
#include <QWebEnginePage>
#include <QDebug>
Test::Test(QObject *parent) : QObject(parent)
{

}

void Test::setPage(QWebEnginePage *page)
{
    m_page = page;

//    connect(m_page, &QWebEnginePage::selectionChanged, [this](){qDebug() << m_page->selectedText();});
}

void Test::copy()
{
}
