#include "httphelper.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QCryptographicHash>
QNetworkAccessManager* HttpHelper::m_manager = new QNetworkAccessManager;

HttpHelper::HttpHelper(QObject *parent) : QObject(parent),
m_file(nullptr), m_reply(nullptr)
{
}

void HttpHelper::download(const QString &url_)
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


QString HttpHelper::upload(const QString &fileName)
{
    QFile *file1 = new QFile(fileName);
    file1->open(QIODevice::ReadOnly);

    QByteArray array = QCryptographicHash::hash(file1->readAll(), QCryptographicHash::Md5);
    QString uploadFileName = QString(array.toHex());
    file1->close();

    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->setBoundary("youliao_youliao");

    QFileInfo info(*file);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"file\"; filename=\"%1\"").arg(uploadFileName + "." + info.suffix())));
    imagePart.setBodyDevice(file);

    file->setParent(multiPart);
    multiPart->append(imagePart);


    QNetworkRequest req(QUrl("http://www.liutimo.cn/uploadImage.php"));

    QNetworkReply *reply =  m_manager->post(req, multiPart);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        qDebug() << reply->readAll();
    });
    multiPart->setParent(reply);

    return uploadFileName + "." + info.suffix();
}

void HttpHelper::startRequest(const QUrl &url)
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
