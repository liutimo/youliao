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
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.login.pb.h"


static ClientConnMap_t g_client_conn_map;

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
        default:
            break;
    }
}

void ClientConn::_HandlClientLoginRequest(BasePdu *pdu)
{

    login::UserLoginRequest request;
    request.ParseFromString(pdu->getMessage());
    log("登录请求! 登录名: %s, 登录密码:%s", request.user_name().c_str(), request.user_password().c_str());
    login::UserLoginRespone respone;
    respone.set_result_code(base::NONE);
    base::UserInfo *userInfo = new base::UserInfo;
    userInfo->set_user_email("779564531");
    userInfo->set_user_id(1);
    userInfo->set_user_nick("刘提莫");
    userInfo->set_user_phone("15367877419");
    userInfo->set_user_sex(1);
    userInfo->set_user_sign_info("好好学习,努力工作");
    respone.set_allocated_user_info(userInfo);
    BasePdu basePdu;
    basePdu.setCID(base::CID_LOGIN_RESPONE_USERLOGIN);
    basePdu.setSID(base::SID_LOGIN);
    basePdu.writeMessage(&respone);
    sendBasePdu(&basePdu);
}

void ClientConn::_HandleHeartBeat(BasePdu *pdu)
{
    log("received heartbeat!");
    sendBasePdu(pdu);
}