/*================================================================
*   
*   文件名称: EventDispatch.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午2:20
*   描   述: 处理事件循环, epoll ,定时任务. 单例模式
*
================================================================*/


#ifndef BASEUTIL_EVENTDISPATCH_H
#define BASEUTIL_EVENTDISPATCH_H

#include <list>
#include "type_define.h"
namespace youliao
{
    namespace network
    {

        class EventDispatch {
        public:
            virtual ~EventDispatch();

            static EventDispatch* instance();

            void addEvent(net_handle_t handle, uint8_t events = 0xFF);
            void removeEvent(net_handle_t handle, uint8_t events = 0xFF);

            void addLoop(callback_t, callback_data data);

            void eventLoop(uint32_t wait_time = 100);
        private:
            void _CheckLoop();

            typedef struct {
                callback_t      callback;
                callback_data   data;
                uint64_t        interval;
                uint64_t        next_tick;
            }EventItem;

        private:

            EventDispatch();

            int m_epfd;
            std::list<EventItem*> m_loop_list;

            static EventDispatch* m_event_dispatch;

        };

    }
}


#endif //BASEUTIL_EVENTDISPATCH_H
