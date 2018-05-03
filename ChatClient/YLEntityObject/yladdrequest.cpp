#include "yladdrequest.h"

YLAddRequest::YLAddRequest(QObject *parent) : QObject(parent)
{

}


YLAddRequest::YLAddRequest(const YLAddRequest &req)
{
    m_other_id = req.m_other_id;
    m_other_nick =req.m_other_nick;
    m_head_url = req.m_head_url;
    m_validate_data = req.m_validate_data;
}


YLAddRequest& YLAddRequest::operator=(const YLAddRequest &req)
{
    m_other_id = req.m_other_id;
    m_other_nick =req.m_other_nick;
    m_head_url = req.m_head_url;
    m_validate_data = req.m_validate_data;
    return *this;
}

void YLAddRequest::setOtherId(uint32_t otherId)
{
    m_other_id = otherId;
}

void YLAddRequest::setOtherNick(const QString &nick)
{
    m_other_nick = nick;
}

void YLAddRequest::setOtherHeadUrl(const QString &url)
{
    m_head_url = url;
}

void YLAddRequest::setValidateData(const QString &validateData)
{
    m_validate_data = validateData;
}

uint32_t YLAddRequest::getOtherId() const
{
    return m_other_id;
}

QString YLAddRequest::getOtherNick() const
{
    return m_other_nick;
}

QString YLAddRequest::getOtherHeadUrl() const
{
    return m_head_url;
}

QString YLAddRequest::getValidateData() const
{
    return m_validate_data;
}
