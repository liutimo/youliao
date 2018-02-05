#include "netlib.h"
#include "ConfigFileReader.h"

void client_callback(void* callback_data, uint8_t msg, uint32_t fd, void* pParam)
{
    if (msg == NETLIB_MSG_CONNECT)
    {
        //
        log("收到登录请求\n", "");
        log("正在分配最优登录服务器...\n", "");
        log("处理成功...\n", "");
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

    netlib_listen("127.0.0.1", 8002, NULL, NULL);

    netlib_eventloop();

    netlib_destroy();


    return 0;
}