//
// Created by liuzheng on 18-2-4.
//

#ifndef OS_H
#define OS_H


//net
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <signal.h>

//socket系列函数 返回值
enum {
    NETLIB_OK       = 0,
    NETLIB_ERROR    = -1
};

//用于回调函数
//回调函数根据传入的消息类型  调用对象的处理程序
enum
{
    NETLIB_MSG_CONNECT = 1,     //客户的建立连接
    NETLIB_MSG_CONFIRM,         //确认操作
    NETLIB_MSG_READ,            //读操作
    NETLIB_MSG_WRITE,           //写操作
    NETLIB_MSG_CLOSE,           //关闭连接
    NETLIB_MSG_TIMER,
    NETLIB_MSG_LOOP
};

typedef int SOCKET;






typedef void(*callback_t)(void* callback_data, uint8_t msg, uint32_t handle, void* pParam);

#endif //OS_H
