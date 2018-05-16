#include "yladdrequest.h"
YLAddRequest::YLAddRequest(QObject *parent) : QObject(parent)
{

}


YLAddRequest::YLAddRequest(const YLAddRequest &req)
{
    m_id = req.m_id;
    m_other_id = req.m_other_id;
    m_other_nick =req.m_other_nick;
    m_head_url = req.m_head_url;
    m_validate_data = req.m_validate_data;
    m_handle_time = req.m_handle_time;
    m_result_id = req.m_result_id;
    m_group_id = req.m_group_id;
}


YLAddRequest& YLAddRequest::operator=(const YLAddRequest &req)
{
    m_id = req.m_id;
    m_other_id = req.m_other_id;
    m_other_nick =req.m_other_nick;
    m_head_url = req.m_head_url;
    m_validate_data = req.m_validate_data;
    m_handle_time = req.m_handle_time;
    m_result_id = req.m_result_id;
    m_group_id = req.m_group_id;
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

void YLAddRequest::setId(uint32_t id)
{
    m_id = id;
}

void YLAddRequest::setHandleTime(uint32_t time)
{
    m_handle_time = time;
}

void YLAddRequest::setResultId(uint32_t resId)
{
    m_result_id = resId;
}

void YLAddRequest::setGroupId(uint32_t groupId)
{
    m_group_id = groupId;
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

uint32_t YLAddRequest::getId() const
{
    return m_id;
}

uint32_t YLAddRequest::getHandleTime() const
{
    return m_handle_time;
}

uint32_t YLAddRequest::getResultId() const
{
    return m_result_id;
}

uint32_t YLAddRequest::getGroupId() const
{
    return m_group_id;
}

