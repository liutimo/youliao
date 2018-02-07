/*================================================================
*   
*   文件名称: Thread.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午7:51
*   描   述: 封装posix线程
*
================================================================*/


#ifndef BASEUTIL_THREAD_H
#define BASEUTIL_THREAD_H

#include <pthread.h>

namespace youliao
{
    namespace thread
    {

        class Thread {
        public:
            Thread();

            virtual ~Thread();

            //start a thread
            void start();

            bool isRunning() const { return m_running;}

            void join();

            //do main work
            virtual void run() = 0;

        private:
            static void* start_routine(void *);

        protected:
            pthread_t m_thread_id;
            bool m_running;

        };
    }
}


#endif //BASEUTIL_THREAD_H
