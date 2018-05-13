#ifndef YLADDREQUEST_H
#define YLADDREQUEST_H

#include <QObject>

class YLAddRequest : public QObject
{
    Q_OBJECT
public:
    explicit YLAddRequest(QObject *parent = nullptr);
    YLAddRequest(const YLAddRequest&);
    YLAddRequest& operator=(const YLAddRequest &);
    void setOtherId(uint32_t otherId);
    void setOtherNick(const QString &nick);
    void setOtherHeadUrl(const QString &url);
    void setValidateData(const QString &validateData);
    void setId(uint32_t id);
    void setHandleTime(uint32_t time);
    void setResultId(uint32_t resId);
    void setGroupId(uint32_t groupId);

    uint32_t getOtherId() const;
    QString getOtherNick() const;
    QString getOtherHeadUrl() const;
    QString getValidateData() const;
    uint32_t getId() const;
    uint32_t getHandleTime() const;
    uint32_t getResultId() const;
    uint32_t getGroupId() const;
private:
    uint32_t m_id;
    uint32_t m_group_id;
    uint32_t m_other_id;
    uint32_t m_result_id;
    uint32_t m_handle_time;
    QString m_other_nick;
    QString m_head_url;
    QString m_validate_data;
};

#endif // YLADDREQUEST_H
