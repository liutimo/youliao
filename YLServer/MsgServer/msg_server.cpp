#include <iostream>
#include "network/ServerInfo.h"
#include "ClientConn.h"
#include "network/netlib.h"
#include "DBServConn.h"
#include "util/SimpleBuffer.h"
#include "pdu/protobuf/youliao.server.pb.h"

using namespace youliao::network;
using namespace youliao::util;

void clientconn_callback(callback_data data, uint8_t msg, net_handle_t handle, void *pParam)
{
    if (msg == NETWORK_CONNECT)
    {
        ClientConn *clientConn = new ClientConn;
        clientConn->onConnect(handle);
    }
}

int main() {

    netlib_init();
    netlib_listen("127.0.0.1", 8002, clientconn_callback, nullptr);

    serv_info_t *s = new serv_info_t;
    s->server_ip = "127.0.0.1";
    s->server_port = 6001;

    init_db_serv_conn(s, 1, 2);


    netlib_eventloop();

    nettlib_destory();

    return 0;
}