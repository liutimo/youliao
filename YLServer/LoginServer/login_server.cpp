#include <iostream>
#include <network/netlib.h>
#include "util/util.h"
#include "LoginConn.h"

using namespace youliao::network;

void listen_client_callback(callback_data data, uint8_t msg, net_handle_t handle, void* pParam)
{
    NO_USERD(data);
    NO_USERD(pParam);
    if (msg == NETWORK_CONNECT)
    {
        LoginConn *loginConn = new LoginConn;
        loginConn->onConnect(handle, ConnType::CONN_TYPE_CLIENT);
    }
}

void listen_server_callback(callback_data data, uint8_t msg, net_handle_t handle, void* pParam)
{
    NO_USERD(data);
    NO_USERD(pParam);
    if (msg == NETWORK_CONNECT)
    {
        LoginConn *loginConn = new LoginConn;
        loginConn->onConnect(handle, ConnType::CONN_TYPE_SERVER);
    }
}



int main()
{


    log("login server has been starting!");

    log("init....");

    netlib_init();


    netlib_listen("127.0.0.1", 8001, listen_client_callback, nullptr);



    netlib_eventloop();

    nettlib_destory();



    return 0;
}