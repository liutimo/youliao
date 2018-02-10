#include "loginconn.h"
#include "netlib.h"
#include "BasePdu.h"
#include "util.h"
#include "msgservconn.h"
#include "../protobuf/youliao.base.pb.h"
#include "../protobuf/youliao.login.pb.h"

using namespace youliao::util;
using namespace youliao::pdu;

static BaseConnMap_t login_conn_map;
LoginConn::LoginConn()
{

}

LoginConn::~LoginConn()
{

}

void LoginConn::connect(const std::string &server_ip, uint16_t port)
{
    m_handle = netlib_connect(server_ip, port, baseconn_callback, (void*)&login_conn_map);

    if (m_handle != -1)
    {
        login_conn_map.insert(std::make_pair(m_handle, this));
        //发送消息服务器请求
        login::MsgServerRequest request;
        BasePdu *basePdu = new BasePdu;
        basePdu->setSID(base::SID_LOGIN);
        basePdu->setCID(base::CID_LOGIN_REQUSET_MSGSERVER);
        basePdu->writeMessage(&request);

        sendBasePdu(basePdu);
        delete basePdu;
    }
    else
        onClose();

}

void LoginConn::handlePdu(BasePdu *pdu)
{
    if (pdu->getCID() == base::CID_LOGIN_RESPONE_MSGSERVER)
    {
        login::MsgServerRespone respone;
        respone.ParseFromString(pdu->getMessage());

        switch (respone.result_code())
        {
        case base::NONE:
            log("获取消息服务器信息成功! IP=%s, PORT=%d", respone.msg_server_ip().c_str(), respone.port());
            //连接消息服务器
            log("开始连接消息服务器");
            _ConnectToMsgServer(respone.msg_server_ip().c_str(), respone.port());
            break;
        case base::MSG_SERVER_FULL:
            log("消息服务器繁忙");
            break;
        case base::NO_MSG_SERVER:
            log("无可用消息服务器");
            break;
        default:
            break;
        }
    }
    log("关闭和登录服务器的连接");
    onClose();
}

void LoginConn::_ConnectToMsgServer(const std::string &server_ip, uint16_t port)
{
    MsgServConn *msg_serv_coonn = new MsgServConn;
    msg_serv_coonn->connect(server_ip, port);
}
