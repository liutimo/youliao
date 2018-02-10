/*================================================================
*   
*   文件名称: EventDispatch.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午2:20
*
================================================================*/


#include "EventDispatch.h"
#include <unistd.h>
#include <sys/epoll.h>
#include "../util/util.h"
#include "BasicSocket.h"

using namespace youliao::network;

EventDispatch* EventDispatch::m_event_dispatch = nullptr;

EventDispatch::EventDispatch()
{
    //从linux 2.6.8开始,epoll_create的参数无意义,但是必须大于0
    m_epfd = epoll_create(1024);

    if (m_epfd == -1)
    {
        log("epoll_create failed, err_str = %s", strerror(errno));
    }
}

EventDispatch::~EventDispatch()
{
    close(m_epfd);
}

void EventDispatch::addEvent(net_handle_t handle, uint8_t events)
{
    epoll_event ev;
    ev.data.fd = handle;
    ev.events = EPOLLET | EPOLLOUT | EPOLLIN | EPOLLHUP | EPOLLERR | EPOLLPRI;

    if (epoll_ctl(m_epfd, EPOLL_CTL_ADD, handle, &ev) != 0)
    {
        log("add event to %d failed, error str = %s", handle, strerror(errno));
    }
}

void EventDispatch::removeEvent(net_handle_t handle, uint8_t events)
{
    if (epoll_ctl(m_epfd, EPOLL_CTL_DEL, handle, NULL) != 0)
    {
        log("remove event to %d failed, error str = %s", handle, strerror(errno));
    }
}

void EventDispatch::_CheckTimer()
{

}

void EventDispatch::eventLoop(uint32_t wait_time)
{
    epoll_event events[1024];
    int nfds;

    for(;;)
    {
        nfds = epoll_wait(m_epfd, events, 1024, wait_time);
        for (int i = 0; i < nfds; ++i)
        {
            net_handle_t t_handle = events[i].data.fd;
            BaseSocket *pSock = findBaseSocket(t_handle);
            if (!pSock)
                continue;

            //可读
            if (events[i].events & EPOLLIN)
            {
                pSock->onRead();
            }

            //可写
            if (events[i].events & EPOLLOUT)
            {
                pSock->onWrite();
            }

            //错误
            if (events[i].events & (EPOLLHUP | EPOLLERR | EPOLLPRI))
            {
                pSock->onClose();
            }
        }

    }
}

EventDispatch* EventDispatch::instance()
{
    if (m_event_dispatch == nullptr)
        m_event_dispatch = new EventDispatch;

    return m_event_dispatch;
}