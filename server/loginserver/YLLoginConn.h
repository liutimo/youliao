//
// Created by liuzheng on 18-2-5.
//

#ifndef LOGINSERVER_YLLOGINCONN_H
#define LOGINSERVER_YLLOGINCONN_H

#include "YLConn.h"

enum
{
    LOGIN_CONN_TYPE_CLIENT = 1,   //客户端的连接
    LOGIN_CONN_TYPE_MSG_SERV      //来自消息服务器的连接
};

typedef struct
{
    std::string ip;               //服务器ip
    uint16_t    port;             //服务器端口
    uint32_t    max_conn_cnt;     //服务器允许最大连接数
    uint32_t    cur_conn_cnt;     //服务器当前连接数
}MsgServInfo;

class YLLoginConn : public YLConn{
public:
    YLLoginConn();
    virtual ~YLLoginConn();
    virtual void close();

    void onConnect(int fd, int conn_type);
    virtual void onClose();

    virtual void handlePdu(YLPdu *pPdu);

private:
    void _HandleMsgServInfo(YLPdu *pPdu);
    void _HandleUserCntUpdate(YLPdu *pPdu);
    void _HandleMsgServRequest(YLPdu *pPdu);

private:
    int m_conn_type;
};

void init_login_conn();

#endif //LOGINSERVER_YLLOGINCONN_H
