//
// Created by liuzheng on 18-2-4.
//

#include "YLEventDispatch.h"
#include "YLBaseSocket.h"


YLEventDispatch* YLEventDispatch::m_pEventDispatch = nullptr;

YLEventDispatch::YLEventDispatch()
{
    m_running = false;

    //since linux 2.6.8参数无意义，但是必须大于0
    m_epfd = epoll_create(1024);

    if (m_epfd == -1)
    {
        log("epoll_create failed\n", "");
    }
}

YLEventDispatch::~YLEventDispatch()
{
    close(m_epfd);
}

YLEventDispatch* YLEventDispatch::getInstance()
{
    if (m_pEventDispatch == nullptr)
    {
        m_pEventDispatch = new YLEventDispatch();
    }

    return m_pEventDispatch;
}

void YLEventDispatch::addEvent(SOCKET fd, uint8_t socket_event)
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLPRI | EPOLLERR | EPOLLHUP;
    ev.data.fd = fd;
    if (epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &ev) != 0)
    {
        log("epoll_ctl() failed, errno=%d\n", errno);
    }
}

void YLEventDispatch::removeEvent(SOCKET fd, uint8_t socket_event)
{
    if (epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, nullptr) != 0)
    {
        log("epoll_ctl() failed, errno = %d\n", errno);
    }
}

void YLEventDispatch::startDispatch(uint32_t wait_timeout)
{
    struct epoll_event events[1024];

    int nfds;

    if (m_running)
        return;

    m_running = true;

    while (m_running)
    {
        nfds = epoll_wait(m_epfd, events, 1024, wait_timeout);

        for (int i = 0; i < nfds; ++i)
        {
            int fd = events[i].data.fd;
            YLBaseSocket *pSocket = findBaseSocket(fd);
            if (!pSocket)
                continue;

            if (events[i].events & EPOLLIN)
            {
                pSocket->onRead();
            }

            if (events[i].events & EPOLLOUT)
            {
                pSocket->onWrite();
            }

            if (events[i].events & (EPOLLPRI | EPOLLERR | EPOLLHUP))
            {
                pSocket->onClose();
            }
        }

    }

}

void YLEventDispatch::stopDispacth()
{
    m_running = false;
}