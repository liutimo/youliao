#include "yllogintray.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QEvent>
#include <QRect>

YLLoginTray::YLLoginTray(QObject *parent) : QSystemTrayIcon(parent)
{
    initActions();
    initMenu();
    setIcon(QIcon(":/res/offline.ico"));
}

void YLLoginTray::initActions()
{
    m_show_main = new QAction("打开主面板", this);
    connect(m_show_main, &QAction::triggered, this, [this](){ emit showMain(); });
    m_quit = new QAction("退出", this);
    connect(m_quit, &QAction::triggered, this, &YLLoginTray::on_quit_trigger);
}

void YLLoginTray::initMenu()
{
    m_tray_menu = new QMenu();
    m_tray_menu->addAction(m_show_main);
    m_tray_menu->addSeparator();
    m_tray_menu->addAction(m_quit);

    setContextMenu(m_tray_menu);
}



void YLLoginTray::on_quit_trigger()
{
    emit quit();
}
