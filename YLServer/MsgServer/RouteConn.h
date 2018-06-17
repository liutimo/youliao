//
// Created by liuzheng on 18-4-9.
//

#ifndef MSGSERVER_ROUTECONN_H
#define MSGSERVER_ROUTECONN_H
#include "network/BaseConn.h"
#include "pdu/BasePdu.h"
#include "util/util.h"
#include "network/ServerInfo.h"
using namespace youliao::network;
using namespace youliao::pdu;

class RouteConn : public BaseConn
{
public:
    RouteConn();
    virtual ~RouteConn();

    void connect(const std::string &server_ip, uint16_t server_port, uint32_t serv_idx);

    virtual void close();
    void onClose() override;
    void onConfirm() override ;
    void handlePdu(BasePdu *) override;

    bool isOpen() const { return m_open; }

private:
    void _HandleGetFriendsStatusRespone(BasePdu *basePdu);
    void _HandleRouteBroadcast(BasePdu *);
    void _HandleHandleStatusChange(BasePdu *);
    void _HandleForwardGroupMessage(BasePdu *);
    void _HandleUserInformationChange(BasePdu *);
    void _HandleUpdateGroupListRespone(BasePdu *);

    uint32_t   m_server_index;
    bool       m_open;
};


void init_route_serv_conn(serv_info_t* server_list, uint32_t server_count, uint32_t curr_conn_cnt);
RouteConn *get_route_server_conn();



#endif //MSGSERVER_ROUTECONN_H
