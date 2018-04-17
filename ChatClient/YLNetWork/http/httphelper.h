#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QFile;

class HttpHelper : public QObject
{
    Q_OBJECT
//    const QString file_dir = "./"
public:
    explicit HttpHelper(QObject *parent = nullptr);
    void download(const QString &url);
    QString upload(const QString &fileName);

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
