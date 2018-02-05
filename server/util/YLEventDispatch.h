//
// Created by liuzheng on 18-2-4.
//
// 负责开启程序的主循环。处理YLBaseSocket的读写操作和错误处理

#ifndef UTIL_YLEVENTDISPATCH_H
#define UTIL_YLEVENTDISPATCH_H

#include "os.h"
#include "common.h"

enum {
    SOCKET_READ		= 0x1,
    SOCKET_WRITE	= 0x2,
    SOCKET_EXCEP	= 0x4,
    SOCKET_ALL		= 0x7
};

class YLEventDispatch {
public:
    ~YLEventDispatch();

    void addEvent(SOCKET fd, uint8_t socket_event);
    void removeEvent(SOCKET fd, uint8_t socket_event);

    void startDispatch(uint32_t wait_timeout = 100);
    void stopDispacth();

    bool isRunning() const { return m_running; }

    static YLEventDispatch* getInstance();

protected:
    YLEventDispatch();

private:
    int m_epfd;

    bool m_running;

    static YLEventDispatch* m_pEventDispatch;
};


#endif //UTIL_YLEVENTDISPATCH_H
