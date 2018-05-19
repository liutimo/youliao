//
// Created by liuzheng on 18-4-9.
//

#ifndef ROUTESERVER_ROUTECONN_H
#define ROUTESERVER_ROUTECONN_H

#include "network/BaseConn.h"

using namespace youliao::network;
using namespace youliao::pdu;

class RouteConn : public BaseConn
{
public:
    RouteConn();
    virtual ~RouteConn();

    virtual void close();
    virtual void onConfirm() override;

    void onConnect(net_handle_t handle) override;
    void onClose() override;

    void handlePdu(BasePdu *basePdu) override ;

private:
    void _HandleUserGoOnline(BasePdu *basePdu);
    void _HandleUserGoOffline(BasePdu *basePdu);
    void _HandleGetFriendsStatusRequest(BasePdu *basePdu);


    void _HandleRouteMessage(BasePdu *basePdu);
    void _HandleMessageServerIndex(BasePdu *basePdu);
    void _HandleBroadcastMsg(BasePdu *basePdu);
};

void addRouteConn(uint32_t index, RouteConn *routeConn);
RouteConn *getRouteConn(uint32_t index);

#endif //ROUTESERVER_ROUTECONN_H
