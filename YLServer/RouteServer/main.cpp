#include <iostream>
#include <network/ServerInfo.h>
#include "RouteConn.h"
#include "network/netlib.h"
#include "util/util.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "DBServConn.h"

using namespace youliao::pdu;

void route_server_callback(callback_data callbackData, uint8_t msg, int handle, void* param)
{
    if (msg == NETWORK_CONNECT)
    {
        RouteConn *routeConn = new RouteConn;
        routeConn->onConnect(handle);

        server::GetServerIndexRequest getServerIndexRequest;
        BasePdu basePdu;
        basePdu.setSID(base::SID_SERVER);
        basePdu.setCID(base::CID_SERVER_GET_SERVER_INDEX_REQUEST);
        basePdu.writeMessage(&getServerIndexRequest);
        routeConn->sendBasePdu(&basePdu);
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

    serv_info_t *s = new serv_info_t;
    s->server_ip = "127.0.0.1";
    s->server_port = 6001;

    init_db_serv_conn(s, 1, 2);


    netlib_eventloop();

    nettlib_destory();
    return 0;
}