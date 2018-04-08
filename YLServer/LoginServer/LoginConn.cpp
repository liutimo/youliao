/*================================================================
*   
*   文件名称: LoginConn.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月08日　 下午10:03
*
================================================================*/


#include <pdu/BasePdu.h>
#include "LoginConn.h"
#include "network/BasicSocket.h"
#include "network/netlib.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"

using namespace youliao::pdu;


//这两个map, 会在onConnect函数中通过type参数来决定将哪个map传递给回调函数
static ConnMap_t g_client_conn_map;
static ConnMap_t g_server_conn_map;
static __gnu_cxx::hash_map<int, msg_server_info_t*> server_info_map;



LoginConn::LoginConn() : BaseConn()
{

}

LoginConn::~LoginConn()
{

}


void LoginConn::onConnect(net_handle_t handle, ConnType type)
{
    m_handle = handle;
    m_conn_type = type;

    ConnMap_t *connMap = &g_server_conn_map;

    if (type == CONN_TYPE_CLIENT)
    {
        connMap = &g_client_conn_map;
    }

    connMap->insert(std::make_pair(m_handle, this));

    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)connMap);
}


void LoginConn::handlePdu(BasePdu *basePdu)
{
    switch (basePdu->getSID())
    {
        case youliao::pdu::base::SID_LOGIN:
            _HandleClientLogin(basePdu);
            break;
        case youliao::pdu::base::SID_SERVER:
            _HandleServerInfo(basePdu);
            break;
        default:
            break;
    }

}

void LoginConn::_HandleClientLogin(BasePdu *basePdu)
{
    login::MsgServerRequest request;
    request.ParseFromString(basePdu->getMessage());

    //响应
    youliao::pdu::login::MsgServerRespone respone;
    respone.set_result_code(base::NONE);
    respone.set_msg_server_ip("127.0.0.1");

//    if (i % 2 == 0)
//        respone.set_port(8002);
//    else
//        respone.set_port(8003);
//    ++i;

    respone.set_port(8002);

    BasePdu *responePdu = new BasePdu;
    responePdu->setSID(base::SID_LOGIN);
    responePdu->setCID(base::CID_LOGIN_RESPONE_MSGSERVER);
    responePdu->writeMessage(&respone);

    sendBasePdu(responePdu);
    delete responePdu;
}

void LoginConn::_HandleServerInfo(BasePdu *basePdu)
{
    youliao::pdu::server::MsgServerInfo server_info;
    server_info.ParseFromString(basePdu->getMessage());

    msg_server_info_t *msg_server_info = new msg_server_info_t;
    msg_server_info->ip = server_info.ip();
    msg_server_info->port = server_info.port();
    msg_server_info->max_conn_count = server_info.max_conn_count();
    msg_server_info->cur_conn_count = server_info.cur_conn_count();

    server_info_map.insert(std::make_pair(m_handle, msg_server_info));
}