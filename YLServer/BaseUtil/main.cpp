#include <iostream>
#include "network/netlib.h"
#include "util/util.h"
using namespace youliao::network;


//该回调函数在 BaseSocket::_AcceptNewConn 中被调用,
//其作用是设置 BaseSocket::onRead中的回调函数.
void listen_callback(void *callback_data, uint8_t msg,  net_handle_t handle, void *pParam)
{
    if (msg == NETWORK_CONNECT)
    {
        BaseSocket *pSocket = findBaseSocket(handle);
        if (!pSocket)
        {
            log("don't find this handle %d in global connect map", handle);
            delete pSocket;
            return;
        }
    }
    else
    {
        log("recv a error msg(msg = %d)", msg);
    }

}

int main() {

    netlib_init();

    netlib_listen("127.0.0.1", 8001, listen_callback, nullptr);

    netlib_eventloop();

    nettlib_destory();

    return 0;
}