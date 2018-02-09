/*================================================================
*   
*   文件名称: LoginConn.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月08日　 下午10:03
*   描   述: 继承至BaseConn. 实现针对登录服务器的读写操作
*
================================================================*/


#ifndef LOGINSERVER_LOGINCONN_H
#define LOGINSERVER_LOGINCONN_H

#include "network/BaseConn.h"
#include "util/util.h"
#include "pdu/BasePdu.h"

using namespace youliao::network;
using namespace youliao::pdu;
class LoginConn;

typedef __gnu_cxx::hash_map<net_handle_t, LoginConn*> ConnMap_t;

typedef enum
{
    CONN_TYPE_CLIENT = 0,
    CONN_TYPE_SERVER
}ConnType;

typedef struct
{
    std::string ip;          //消息服务器IP
    uint32_t port;           //消息服务器端口
    uint32_t max_conn_count; //消息服务器允许的最大连接数
    uint32_t cur_conn_count; //消息服务器当前的连接数
}msg_server_info_t;

class LoginConn : public BaseConn{
public:
    LoginConn();

    ~LoginConn();

    virtual void onConnect(net_handle_t handle, ConnType type);

    virtual void onWriteComplete() {}

    virtual void handlePdu(BasePdu *);

private:
    void _HandleClientLogin(BasePdu*);
    void _HandleServerInfo(BasePdu*);

    ConnType m_conn_type;

};

#endif //LOGINSERVER_LOGINCONN_H
