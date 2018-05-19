#include <iostream>
#include <network/ServerInfo.h>
#include "RouteConn.h"
#include "network/netlib.h"
#include "util/util.h"
#include "pdu/protobuf/youliao.server.pb.h"

using namespace youliao::pdu;

void route_server_callback(callback_data callbackData, uint8_t msg, int handle, void* param)
{
    if (msg == NETWORK_CONNECT)
    {
        RouteConn *routeConn = new RouteConn;
        routeConn->onConnect(handle);
    }
    else
    {
        log("error msg: %d on handle %d ", msg, handle);
    }

}

int main() {


    netlib_init();
    netlib_listen("127.0.0.1", 7001, route_server_callback, nullptr);
    log("route server start listen...");


    netlib_eventloop();

    nettlib_destory();
    return 0;
}