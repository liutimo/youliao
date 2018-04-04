#include "globaldata.h"
#include <QDir>
#include <QUrl>
youliao::pdu::base::UserInfo GlobalData::m_user = youliao::pdu::base::UserInfo();

QString GlobalData::m_header_image_path = QString();

GlobalData::GlobalData(QObject *parent) : QObject(parent)
{

}

void GlobalData::setCurrLoginUser(youliao::pdu::base::UserInfo user)
{
    m_user = user;

    QUrl url(QString(user.user_header_url().c_str()));

    m_header_image_path = "file://" + QDir::currentPath() + "/" + url.fileName();
}
