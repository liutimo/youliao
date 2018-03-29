/*================================================================
*   
*   文件名称: ClientConn.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月09日　 下午8:45
*
================================================================*/


#include "ClientConn.h"
#include "network/netlib.h"
#include "DBServConn.h"
#include "util/SimpleBuffer.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"

using namespace youliao::util;

static ClientConnMap_t g_client_conn_map;

template <class T>
void set_attach_data(T &t, net_handle_t data)
{
    SimpleBuffer simpleBuffer;
    simpleBuffer.writeUInt32(data);
    t.set_attach_data(simpleBuffer.getBuffer(), simpleBuffer.getWriteOffest());
}

ClientConn *findConn(uint32_t handle)
{
    auto iter = g_client_conn_map.find(handle);
    if (iter != g_client_conn_map.end())
        return iter->second;
    return nullptr;
}

ClientConn::ClientConn() : BaseConn()
{

}

ClientConn::~ClientConn()
{

}

void ClientConn::onConnect(net_handle_t handle)
{
    m_handle = handle;

    g_client_conn_map.insert(std::make_pair(m_handle, this));

    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)&g_client_conn_map);
}

void ClientConn::onClose()
{
    auto iter = g_client_conn_map.find(m_handle);

    if (iter != g_client_conn_map.end())
    {
        g_client_conn_map.erase(iter);
        netlib_close(m_handle);
    }

}


void ClientConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID())
    {
        case base::CID_LOGIN_REQUEST_USERLOGIN:
            _HandlClientLoginRequest(pdu);
            break;
        case base::CID_OTHER_HEARTBEAT:
            _HandleHeartBeat(pdu);
            break;
        case base::CID_FRIENDLIST_GET_REQUEST:
            _HandleFriendListGetRequest(pdu);
            break;
        default:
            break;
    }
}

void ClientConn::_HandlClientLoginRequest(BasePdu *pdu)
{

    login::UserLoginRequest request;
    request.ParseFromString(pdu->getMessage());
    log("登录请求! 登录名: %s, 登录密码:%s", request.user_name().c_str(), request.user_password().c_str());

    server::ValidateRequest validateRequest;
    validateRequest.set_user_name(request.user_name());
    validateRequest.set_user_pwd(request.user_password());
    set_attach_data(validateRequest, m_handle);

    DBServConn *pDbServConn = get_db_server_conn();
    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(base::SID_OTHER);
    basePdu->setCID(base::CID_SERVER_VALIDATE_REQUEST);
    basePdu->writeMessage(&validateRequest);
    pDbServConn->sendBasePdu(basePdu);
    delete basePdu;

}

void ClientConn::_HandleHeartBeat(BasePdu *pdu)
{
    log("received heartbeat!");
    sendBasePdu(pdu);
}


void ClientConn::_HandleFriendListGetRequest(BasePdu *pdu)
{

    std::cout << "收到来自" << m_handle << "的好友列表请求" << std::endl;

    friendlist::FriendListRequest friendListRequest;
    friendListRequest.ParseFromString(pdu->getMessage());
    log("获取用户id=%d的好友列表", friendListRequest.user_id());

    set_attach_data(friendListRequest, m_handle);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
    {
        BasePdu *basePdu = new BasePdu;
        basePdu->setSID(base::SID_FRIEND_LIST);
        basePdu->setCID(base::CID_FRIENDLIST_GET_REQUEST);
        basePdu->writeMessage(&friendListRequest);
        dbServConn->sendBasePdu(basePdu);
        delete basePdu;
    }

}