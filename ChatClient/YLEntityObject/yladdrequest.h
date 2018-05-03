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

    uint32_t getOtherId() const;
    QString getOtherNick() const;
    QString getOtherHeadUrl() const;
    QString getValidateData() const;

private:
    uint32_t m_other_id;
    QString m_other_nick;
    QString m_head_url;
    QString m_validate_data;
};

#endif // YLADDREQUEST_H
