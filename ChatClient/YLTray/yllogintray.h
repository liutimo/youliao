#ifndef YLLOGINTRAY_H
#define YLLOGINTRAY_H

#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;

QT_END_MOC_NAMESPACE


class YLLoginTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit YLLoginTray(QObject *parent = nullptr);

signals:
    void quit();
    void showMain();

private slots:
    void on_quit_trigger();

private:
    void initActions();
    void initMenu();

private:
    //action
    QAction *m_show_main;
    QAction *m_quit;

    //menu
    QMenu   *m_tray_menu;
};

#endif // YLLOGINTRAY_H
