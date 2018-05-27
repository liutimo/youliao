#include <iostream>
#include "DBPool.h"
#include "business/LoginModel.h"
#include "network/netlib.h"
#include "ProxyConn.h"

#include "pdu/protobuf/youliao.friendlist.pb.h"

#include "business/Interface.h"
#include "business/AudioModel.h"
#include "network/HttpClient.h"
using namespace youliao::pdu;

using  namespace youliao::network;

void new_conn(callback_data data, uint8_t msg, net_handle_t handle, void *pParam)
{
    if (msg == NETWORK_CONNECT)
    {
        std::cout << "新连接" << std::endl;
        ProxyConn *proxyConn = new ProxyConn;
        proxyConn->onConnect(handle);
    }
}


int main() {
    netlib_init();

    AudioModel::instance()->setUrl("http://www.liutimo.cn/uploadAudio.php");




    netlib_listen("127.0.0.1", 6001, new_conn, nullptr);
    netlib_eventloop();

    nettlib_destory();


    return 0;
}