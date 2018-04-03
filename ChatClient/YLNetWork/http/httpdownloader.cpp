#include "httpdownloader.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

QNetworkAccessManager* HttpDownloader::m_manager = new QNetworkAccessManager;

HttpDownloader::HttpDownloader(QObject *parent) : QObject(parent),
m_file(nullptr), m_reply(nullptr)
{
}

void HttpDownloader::start(const QString &url_)
{
    const QUrl url = QUrl::fromUserInput(url_);
    if (!url.isValid())
    {
        emit urlInvalid();
        return;
    }

    m_filename = url.fileName();
    if (m_filename.isEmpty())
    {
        emit urlInvalid();
        return;
    }

    m_file = new QFile(m_filename);

    if (m_file->exists())
    {
        emit downloadFinshed();
    }
    else
    {
        if (!m_file->open(QIODevice::WriteOnly))
            return;

        startRequest(url);
    }
}

void HttpDownloader::startRequest(const QUrl &url)
{
    m_reply = m_manager->get(QNetworkRequest(url));
    connect(m_reply, &QNetworkReply::finished, this, [this](){
        m_file->close();
        m_reply->abort();
        delete m_reply;
        emit downloadFinshed();
    });
    connect(m_reply, &QNetworkReply::readyRead, this, [this](){
        if (m_file)
        {
            m_file->write(m_reply->readAll());
        }
    });
}
