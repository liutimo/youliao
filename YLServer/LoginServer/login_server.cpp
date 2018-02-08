#include <iostream>
#include <network/netlib.h>
#include "util/util.h"



using namespace youliao::network;

void listen_callback(callback_data data, uint8_t msg, net_handle_t handle, void* pParam)
{
    NO_USERD(data);
    NO_USERD(pParam);
    if (msg == NETWORK_CONNECT)
    {
        BaseSocket *pSocket = findBaseSocket(handle);
        if (pSocket == nullptr)
        {
            log("don't find handle(%d) int global conn map");
            return;;
        }

        //更改pSocket的回调函数
    }
}


int main() {


    log("login server has been starting!");

    log("init....");

    netlib_init();


    netlib_listen("127.0.0.1", 8001, listen_callback, nullptr);



    netlib_eventloop();

    nettlib_destory();


    return 0;
}