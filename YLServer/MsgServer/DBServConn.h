//
// Created by liuzheng on 18-3-21.
//

#ifndef MSGSERVER_DBSERVCONN_H
#define MSGSERVER_DBSERVCONN_H
#include "network/BaseConn.h"
#include "pdu/BasePdu.h"
#include "util/util.h"
#include "network/ServerInfo.h"
using namespace youliao::network;
using namespace youliao::pdu;

class DBServConn : public BaseConn
{
public:
    DBServConn();
    virtual ~DBServConn();

    void connect(const std::string &server_ip, uint16_t server_port, uint32_t serv_idx);

    virtual void close();
    void onClose() override;
    void handlePdu(BasePdu *) override;

    bool isOpen() const { return m_open; }

private:
    void _HandleValidateRespone(BasePdu *);
    void _HandleFriendListRespone(BasePdu *);
    void _HandleSignatureChangedResponse(BasePdu *);

    uint32_t   m_server_index;
    bool       m_open;
};


void init_db_serv_conn(serv_info_t* server_list, uint32_t server_count, uint32_t curr_conn_cnt);
DBServConn *get_db_server_conn();



#endif //MSGSERVER_DBSERVCONN_H
