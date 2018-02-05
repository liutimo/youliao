//
// Created by liuzheng on 18-2-5.
//

#include "YLLoginConn.h"
#include "protobuf/YLLogin.pb.h"

static ConnMap g_client_conn_map;
static ConnMap g_msg_serv_conn_map;
static uint32_t g_total_online_user_cnt = 0; //当前在线人数

std::map<int, MsgServInfo*> g_msg_serv_info;

YLLoginConn::YLLoginConn()
{

}

YLLoginConn::~YLLoginConn()
{

}

void YLLoginConn::close()
{
    if (m_fd != -1)
    {
        netlib_close(m_fd);
        if (m_conn_type == LOGIN_CONN_TYPE_CLIENT)
        {
            g_client_conn_map.erase(m_fd);
        }
        else
        {
            g_msg_serv_conn_map.erase(m_fd);
            //与消息服务器服务器断开连接. 需要更新在线人数

            auto iter = g_msg_serv_info.find(m_fd);
            if (iter != g_msg_serv_info.end())
            {
                auto pMsgServInfo = iter->second;
                g_total_online_user_cnt -= pMsgServInfo->cur_conn_cnt;
                delete pMsgServInfo;
                g_msg_serv_info.erase(iter);
             }
        }
    }
}

void YLLoginConn::onConnect(int fd, int conn_type)
{
    m_fd = fd;
    m_conn_type = conn_type;
    ConnMap *conn_map = &g_msg_serv_conn_map;

    if (m_conn_type == LOGIN_CONN_TYPE_CLIENT)
    {
        conn_map = &g_client_conn_map;
    }

    conn_map->insert(std::make_pair(m_fd, this));

    netlib_option(m_fd, NETLIB_OPT_SET_CALLBACK, (void*)conn_callback);
    netlib_option(m_fd, NETLIB_OPT_SET_CALLBACK_DATA, (void*)conn_map);
}

void YLLoginConn::onClose()
{
    close();
}

void YLLoginConn::handlePdu(YLPdu *pPdu)
{
    switch (pPdu->getCID())
    {
        case YL::Base::CID_LOGIN_REQ_MSGSERVER:
            _HandleMsgServRequest(pPdu);
            break;
        default:
            break;
    }
}

void YLLoginConn::_HandleMsgServInfo(YLPdu *pPdu)
{

}


void YLLoginConn::_HandleUserCntUpdate(YLPdu *pPdu)
{

}

void YLLoginConn::_HandleMsgServRequest(YLPdu *pPdu)
{
    YL::Login::YLMsgServerRequest msg;
    msg.ParseFromArray(pPdu->getBodyData(), pPdu->getBodyLength());

    if (g_msg_serv_info.size() == 0)
    {
        YL::Login::YLMsgServerRespone rsp_msg;
        rsp_msg.set_result_code(YL::Base::REFUSE_REASON_NO_MSG_SERVER);
        YLPdu pdu;
        pdu.setPBMsg(&rsp_msg);
        pdu.setSID(YL::Base::SID_LOGIN);
        pdu.setCID(YL::Base::CID_LOGIN_RES_MSGSERVER);
        pdu.setSeqNum(pPdu->getSeqNum());
        sendPdu(&pdu);
        close();
        return;
    }

    MsgServInfo *pMsgServInfo;
    uint32_t min_user_cnt = (uint32_t)-1;
    auto iter_min_conn = g_msg_serv_info.end();


    for (auto iter = g_msg_serv_info.begin(); iter != g_msg_serv_info.end(); ++iter)
    {
        pMsgServInfo = iter->second;

        if ( (pMsgServInfo->cur_conn_cnt < pMsgServInfo->max_conn_cnt) &&
             (pMsgServInfo->cur_conn_cnt < min_user_cnt))
        {
            iter_min_conn = iter;
            min_user_cnt = pMsgServInfo->cur_conn_cnt;
        }
    }

    //消息服务器全部满负荷运行
    if (iter_min_conn == g_msg_serv_info.end())
    {
        YL::Login::YLMsgServerRespone rsp_msg;
        rsp_msg.set_result_code(YL::Base::REFUSE_REASON_MSG_SERVER_FULL);
        YLPdu pdu;
        pdu.setPBMsg(&rsp_msg);
        pdu.setSID(YL::Base::SID_LOGIN);
        pdu.setCID(YL::Base::CID_LOGIN_RES_MSGSERVER);
        pdu.setSeqNum(pPdu->getSeqNum());
        sendPdu(&pdu);
    }
    else
    {
        YL::Login::YLMsgServerRespone rsp_msg;
        rsp_msg.set_result_code(YL::Base::REFUSE_REASON_NONE);
        rsp_msg.set_prior_ip(iter_min_conn->second->ip);
        rsp_msg.set_port(iter_min_conn->second->port);

        YLPdu pdu;
        pdu.setPBMsg(&rsp_msg);
        pdu.setSID(YL::Base::SID_LOGIN);
        pdu.setCID(YL::Base::CID_LOGIN_RES_MSGSERVER);
        pdu.setSeqNum(pPdu->getSeqNum());
        sendPdu(&pdu);
    }

    close();
}