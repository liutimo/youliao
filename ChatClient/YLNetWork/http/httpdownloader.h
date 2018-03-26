#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QFile;

class HttpDownloader : public QObject
{
    Q_OBJECT
//    const QString file_dir = "./"
public:
    explicit HttpDownloader(QObject *parent = nullptr);
    void start(const QString &url);
    QString getFilename() const  { return m_filename;}

signals:
    void downloadFinshed();
    void urlInvalid();

public slots:


private:
    void startRequest(const QUrl &url);

    static QNetworkAccessManager *m_manager;
    QNetworkReply         *m_reply;

    QString m_filename;
    QFile   *m_file;
};

#endif // HTTPDOWNLOADER_H
