#include <iostream>
#include "ClientConn.h"
#include "network/netlib.h"
#include "pdu/protobuf/youliao.server.pb.h"

using namespace youliao::network;


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
    netlib_eventloop();

    nettlib_destory();

    return 0;
}