/*================================================================
*   
*   文件名称: ProxyConn.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月10日　 上午11:43
*   描   述:
*
================================================================*/


#include "ProxyConn.h"
#include "network/netlib.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"

#include "business/LoginModel.h"

using namespace youliao::network;
using namespace youliao::pdu;

static BaseConnMap_t g_proxy_conn_map;

ProxyConn::ProxyConn() : BaseConn()
{

}

ProxyConn::~ProxyConn()
{

}

void ProxyConn::onConnect(net_handle_t handle)
{
    m_handle = handle;
    g_proxy_conn_map.insert(std::make_pair(m_handle, this));


    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)&g_proxy_conn_map);
}

void ProxyConn::close()
{
    auto iter = g_proxy_conn_map.find(m_handle);

    if (iter != g_proxy_conn_map.end())
    {
        g_proxy_conn_map.erase(iter);
        netlib_close(m_handle);
    }
}

void ProxyConn::onClose()
{
    close();
}

void ProxyConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID() ) {
        case base::CID_OTHER_HEARTBEAT:
            std::cout << "心跳包" << std::endl;
            break;
        case base::CID_SERVER_VALIDATE_REQUEST:
        {
            server::ValidateRequest validateRequest;
            validateRequest.ParseFromString(pdu->getMessage());

            server::ValidateRespone validateRespone;
            validateRespone.set_attach_data(validateRequest.attach_data());

            LoginModel loginModel;

            if (loginModel.doLogin(validateRequest.user_name(), validateRequest.user_pwd()))
            {
                std::cout << "login success!" << std::endl;

                validateRespone.set_user_name(validateRequest.user_name());
                validateRespone.set_result_code(0);
                validateRespone.set_result_string("登录成功");

                base::UserInfo *userInfo = new base::UserInfo;
                userInfo->set_user_nick("刘提莫");
                userInfo->set_user_sign_info("carry");
                userInfo->set_user_email("77956431@qq.com");
                userInfo->set_user_header_url("http://www.11.com/1.png");
                userInfo->set_user_id(1);
                userInfo->set_user_sex(1);
                userInfo->set_user_phone("15367877419");

                validateRespone.set_allocated_user_info(userInfo);
            }
            else
            {
                std::cout << "login error!" << std::endl;
                validateRespone.set_result_code(1);
                validateRespone.set_result_string("登录失败， 用户名或密码错误！");
            }

            BasePdu *pdu1 = new BasePdu;
            pdu1->setSID(base::SID_OTHER);
            pdu1->setCID(base::CID_SERVER_VALIDATE_RESPONE);
            pdu1->writeMessage(&validateRespone);

            sendBasePdu(pdu1);
            delete pdu1;
        }
    }
}