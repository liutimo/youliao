#ifndef YLMESSAGEVIEW_H
#define YLMESSAGEVIEW_H

#include <QWebEngineView>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QFile>
class YLMessageView : public QWebEngineView
{
//    Q_OBJECT
public:
    explicit YLMessageView(QWidget *parent = nullptr);
    void setFriendId(uint32_t friendId) { m_friend_id = friendId; }
    void setFriendIconPath(const QString &icon) { m_friend_icon_path = icon; }
    virtual ~YLMessageView();

    void addLeft(const QString &, const QString &);
    void addGroupLeft(const QString &icon, const QString &name, const QString &content);
    void loadLeft(const QString &, const QString&);
    void addLeftAudio(const QString &, uint32_t msgId, uint32_t duration);
    void addRight(const QString &, const QString&);
    void loadRight(const QString &, const QString&);
    void addCancelSend(const QString &, const QString &);
    void addCancelRecv(const QString &, const QString &);
    void sendFileSuccess(const QString &, const QString &, const QString &);
    void recvFileSuccess(const QString &, const QString &, const QString &);
    void opponentCancalSend(const QString &, const QString&);
    void opponentCancalRecv(const QString &, const QString&);
    void opponentRefuseRecv(const QString &, const QString&);
    void addLoadMore();

    void loadMore();
signals:
//    void playAudio(uint32_t msgId);

public slots:
    void copy();
    void audio(uint32_t msgId);

protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QWebChannel *channel;

    QFile  sourceFile;
    QAudioOutput *m_audio_output;
    QMediaPlayer *m_player;

    uint32_t m_friend_id;
    uint32_t m_current_page;
    uint32_t m_current_index;

    QString m_friend_icon_path;

};

#endif // YLMESSAGEVIEW_H
