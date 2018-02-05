#include "netlib.h"
#include "ConfigFileReader.h"
#include "YLLoginConn.h"

void client_callback(void* callback_data, uint8_t msg, uint32_t fd, void* pParam)
{
    if (msg == NETLIB_MSG_CONNECT)
    {
        YLLoginConn *loginConn = new YLLoginConn;
        loginConn->onConnect(fd, LOGIN_CONN_TYPE_CLIENT);
    }
    else
    {
        log("错误的消息类型 type = %d\n", msg);
    }

}

int main() {

    signal(SIGPIPE, SIG_IGN);

    netlib_init();

    netlib_listen("127.0.0.1", 8001, client_callback, NULL);

//    netlib_listen("127.0.0.1", 8002, NULL, NULL);

    netlib_eventloop();

    netlib_destroy();


    return 0;
}