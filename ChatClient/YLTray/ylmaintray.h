#ifndef YLTRAY_H
#define YLTRAY_H

#include <QSystemTrayIcon>
#include "protobuf/youliao.message.pb.h"
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTimer;
QT_END_MOC_NAMESPACE

using namespace youliao::pdu;

class YLMainTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    static YLMainTray* instance();

    //receive new message
    void receiveMessage(const message::MessageData &content);
    void updateList();
signals:
    void statusChanged();
    void quit();
    void showMain();

public slots:
    void newAddRequest();

private:
    void initActions();
    void initMenu();

private:
    explicit YLMainTray(QObject *parent = nullptr);
    static YLMainTray *m_instance;
    //action
    QAction *m_status_online;
    QAction *m_status_offline;
    QAction *m_status_invisible;

    QAction *m_show_main;
    QAction *m_quit;

    //menu
    QMenu   *m_tray_menu;
    QTimer  *m_timer;
    QString m_icon_path;
    bool flag;
};

#endif // YLTRAY_H
