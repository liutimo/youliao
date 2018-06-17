#include "httphelper.h"
#include "globaldata.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QCryptographicHash>
#include <QStandardPaths>
#include <QThread>
QNetworkAccessManager* HttpHelper::m_manager        = new QNetworkAccessManager;
QString                HttpHelper::m_file_save_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
HttpHelper::HttpHelper(QObject *parent) : QObject(parent),
m_file(nullptr), m_reply(nullptr)
{
    connect(m_manager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply)
    {

    });
}

void HttpHelper::download(const QString &url_, bool isImage)
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

    if (isImage)
//        m_filename = m_file_save_path + "/" + QString::number(GlobalData::getCurrLoginUserId()) + "/images/"  + m_filename;
        m_filename = GlobalData::imagePath + m_filename;
    else
//        m_filename = m_file_save_path + "/" + QString::number(GlobalData::getCurrLoginUserId()) + "/audio/" + m_filename;
        m_filename = GlobalData::audioPath + m_filename;


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

    m_reply =  m_manager->post(req, multiPart);
    multiPart->setParent(m_reply);

    connect(m_reply, &QNetworkReply::uploadProgress, this, [](qint64 bytesSent, qint64 bytesTotal){
        qDebug() << bytesSent;
    });


    return uploadFileName + "." + info.suffix();
}

void HttpHelper::startRequest(const QUrl &url)
{
    m_reply = m_manager->get(QNetworkRequest(url));
    connect(m_reply, &QNetworkReply::finished, this, [this](){
        m_file->close();
        m_reply->close();
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
