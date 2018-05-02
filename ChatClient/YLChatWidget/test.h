#ifndef TEST_H
#define TEST_H

#include <QObject>
class QWebEnginePage;
class QMenu;
class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);
    void setPage(QWebEnginePage* page);
signals:

private:
    void initPMenu();

public slots:
    void showContentPMenu(uint32_t msgId);
    void loadMore();
private:
    QWebEnginePage *m_page;
    QMenu          *m_p_menu;
    uint32_t        m_message_id;
};

#endif // TEST_H
