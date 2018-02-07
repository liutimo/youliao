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

#include "type_define.h"
namespace youliao
{
    namespace network
    {

        class EventDispatch {
        public:
            virtual ~EventDispatch();

            static EventDispatch* instance();


            /**
             * 为handle添加事件
             * @param handle    socket描述符
             * @param events    实际无用,传入任意即可
             */
            void addEvent(net_handle_t handle, uint8_t events = 0xFF);

            /**
             * 移除handle上的指定事件
             * @param handle  socket描述符
             * @param events    实际无用
             */
            void removeEvent(net_handle_t handle, uint8_t events = 0xFF);


            /**
             * 开始事件循环
             * @param wait_time 阻塞时间, 默认为100ms
             */
            void eventLoop(uint32_t wait_time = 100);
        private:
            EventDispatch();

            int m_epfd;

            static EventDispatch* m_event_dispatch;

        };

    }
}


#endif //BASEUTIL_EVENTDISPATCH_H
