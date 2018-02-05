//
// Created by liuzheng on 18-2-4.
//

#ifndef UTIL_NETLIB_H
#define UTIL_NETLIB_H

#include "os.h"

#define NETLIB_OPT_MIN_VALUE            0
#define NETLIB_OPT_SET_CALLBACK         1
#define NETLIB_OPT_SET_CALLBACK_DATA    2
#define NETLIB_OPT_GET_REMOTE_IP        3
#define NETLIB_OPT_GET_REMOTE_PORT      4
#define NETLIB_OPT_MAX_VALUE            5


#define NETLIB_MAX_SOCKET_BUF_SIZE		(128 * 1024) //允许发送的最大size

#ifdef __cplusplus
extern "C" {
#endif

int netlib_init();

int netlib_destroy();

int netlib_listen(
        const char* server_ip,
        uint16_t port,
        callback_t callback,
        void* callback_data);

int netlib_connect(
        const char* server_ip,
        uint16_t port,
        callback_t callback,
        void* callback_data);

int netlib_send(int fd, void* buf, int len);

int netlib_recv(int fd, void* buf, int len);

int netlib_close(int fd);

int netlib_option(int fd, int opt, void* opt_val);

void netlib_eventloop(uint32_t wait_time = 100); //ms

void netlib_stop_eventloop();

bool netlib_is_running();



#ifdef __cplusplus
}
#endif




#endif //UTIL_NETLIB_H
