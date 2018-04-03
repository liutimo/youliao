//
// Created by liuzheng on 18-3-21.
//

#include <network/ServerInfo.h>
#include <pdu/protobuf/youliao.friendlist.pb.h>
#include "DBServConn.h"
#include "ClientConn.h"
#include "network/netlib.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/BasePdu.h"

using namespace youliao::pdu;

static BaseConnMap_t g_db_server_conn_map;

serv_info_t*  g_db_server_list = nullptr;
uint32_t      g_db_server_count = 0;
uint32_t      g_db_server_login_count = 0;

//serv_info_t *s = new serv_info_t;
//s->server_ip = "127.0.0.1";
//s->server_port = 6001;
//
//init_db_serv_conn(s, 1, 2);

void init_db_serv_conn(serv_info_t* server_list, uint32_t server_count, uint32_t curr_conn_cnt) {
    g_db_server_list = server_list;
    g_db_server_count = server_count;

    uint32_t total_db_instance = server_count / curr_conn_cnt;
    g_db_server_login_count = (total_db_instance / 2) * curr_conn_cnt;

    serv_init<DBServConn>(g_db_server_list, g_db_server_count);


    base::HeartBeat heartBeat;
    BasePdu *pdu = new BasePdu;
    pdu->setSID(base::SID_OTHER);
    pdu->setCID(base::CID_OTHER_HEARTBEAT);
    pdu->writeMessage(&heartBeat);
    g_db_server_list->server_conn->sendBasePdu(pdu);
}

template <class T>
uint32_t get_attach_data(T &t)
{
    SimpleBuffer simpleBuffer;
    simpleBuffer.write((void*)t.attach_data().c_str(), t.attach_data().length());
    return simpleBuffer.readUInt32();
}

DBServConn* get_db_server_conn()
{
    uint32_t i = 0;
    DBServConn* pDbConn = NULL;

    // determine if there is a valid DB server connection
    for (i = 0; i < g_db_server_count; i++) {
        pDbConn = (DBServConn*)g_db_server_list[i].server_conn;
        if (pDbConn && pDbConn->isOpen()) {
            break;
        }
    }

    if (i == g_db_server_count) {
        return NULL;
    }

    while (true) {
        int i = rand() % g_db_server_count;
        pDbConn = (DBServConn*)(g_db_server_list[i].server_conn);
        if (pDbConn && pDbConn->isOpen()) {
            break;
        }
    }

    return (DBServConn*)(g_db_server_list->server_conn);
}



DBServConn::DBServConn()
{
    m_open = false;
}

DBServConn::~DBServConn()
{

}

void DBServConn::connect(const std::string &server_ip, uint16_t server_port, uint32_t serv_idx)
{
    m_server_index = serv_idx;
    m_handle = netlib_connect(server_ip, server_port, baseconn_callback, (void*)&g_db_server_conn_map);

    if (m_handle != NETWORK_ERROR)
    {
        g_db_server_conn_map.insert(std::make_pair(m_handle, this));
    }

    m_open = true;
}

void DBServConn::close()
{
    if (m_handle != -1)
    {
        netlib_close(m_handle);
        g_db_server_conn_map.erase(m_handle);
        m_open = false;
    }
}

void DBServConn::onClose()
{
    close();

    delete this;
}

void DBServConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID())
    {
        case base::CID_SERVER_VALIDATE_RESPONE:
            _HandleValidateRespone(pdu);
            break;
        case base::CID_FRIENDLIST_GET_RESPONE:
            _HandleFriendListRespone(pdu);
            break;
        default:
            break;
    }

}


void DBServConn::_HandleValidateRespone(BasePdu *pdu)
{
    server::ValidateRespone validateRespone;
    validateRespone.ParseFromString(pdu->getMessage());

    uint32_t handle = get_attach_data(validateRespone);

    ClientConn *clientConn = findConn(handle);
    if (clientConn) {
        base::UserInfo *userInfo = new base::UserInfo(validateRespone.user_info());
        login::UserLoginRespone userLoginRespone;
        if (validateRespone.result_code() == 1)
            userLoginRespone.set_result_code(base::MSG_SERVER_FULL);
        else
            userLoginRespone.set_result_code(base::NONE);
        userLoginRespone.set_allocated_user_info(userInfo);

        BasePdu *basePdu = new BasePdu;
        basePdu->setCID(base::CID_LOGIN_RESPONE_USERLOGIN);
        basePdu->setSID(base::SID_OTHER);
        basePdu->writeMessage(&userLoginRespone);
        clientConn->sendBasePdu(basePdu);
        delete basePdu;
    }
    std::cout << validateRespone.result_string() << std::endl;
}


void DBServConn::_HandleFriendListRespone(BasePdu *pdu)
{
    friendlist::FriendListRespone friendListRespone;
    friendListRespone.ParseFromString(pdu->getMessage());

    uint32_t handle = get_attach_data(friendListRespone);


    std::cout << "向" << handle << "发送的好友列表响应" << std::endl;

    ClientConn *clientConn = findConn(handle);
    if (clientConn)
    {

        BasePdu *basePdu = new BasePdu;
        basePdu->setSID(base::SID_FRIEND_LIST);
        basePdu->setCID(base::CID_FRIENDLIST_GET_RESPONE);
        basePdu->writeMessage(&friendListRespone);

        clientConn->sendBasePdu(basePdu);
        delete basePdu;
    }
}