#ifndef TEST_H
#define TEST_H

#include <QObject>
class YLMessageView;
class QMenu;
class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);
    void setView(YLMessageView* page);
    uint32_t getMessageId() { return m_message_id; }
signals:
    void startPlayAudio(uint32_t msgId);
    void loadMoreMessage();

private:
    void initPMenu();

public slots:
    void showContentPMenu(uint32_t msgId);
    void loadMore();
    void playAudio(uint32_t msgId);
private:
    YLMessageView *m_view;
    QMenu          *m_p_menu;
    uint32_t        m_message_id;
    bool            m_load_more_is_emit;
};

#endif // TEST_H
