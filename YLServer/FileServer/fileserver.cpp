#include <iostream>
#include <network/ServerInfo.h>

#include "ClientConn.h"
#include "MsgServerConn.h"
#include "network/netlib.h"
#include "network/ServerInfo.h"
int main() {
    netlib_init();

    serv_info_t *serv_info = new serv_info_t;
    serv_info->server_ip = "127.0.0.1";
    serv_info->server_port = 9001;

    netlib_listen("127.0.0.1", 9001, msgServerConnCallback, nullptr);

    netlib_listen("127.0.0.1", 9002, clientConnCallBack, nullptr);


    netlib_eventloop();

    nettlib_destory();
    return 0;
}