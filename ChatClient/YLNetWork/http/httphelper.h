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
    void download(const QString &url, bool isImage = true);
    QString upload(const QString &fileName);

    QString getFilename() const  { return m_filename;}

signals:
    void downloadFinshed();
    void urlInvalid();

public slots:


private:
    void startRequest(const QUrl &url);


    static QString                m_file_save_path;   //记录文件保存位置
    static QNetworkAccessManager *m_manager;
    QNetworkReply         *m_reply;

    QString m_filename;
    QFile   *m_file;
};

#endif // HTTPDOWNLOADER_H
