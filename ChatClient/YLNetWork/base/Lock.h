/*================================================================
*   
*   文件名称: Lock.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午8:34
*   描   述: 封装互斥量, 条件变量
*
================================================================*/


#ifndef BASEUTIL_LOCK_H
#define BASEUTIL_LOCK_H

#include <pthread.h>
namespace youliao
{
    namespace thread
    {
        //mutex
        class Mutex
        {
        public:
            Mutex();
            virtual ~Mutex();

            void lock();
            void trylock();
            void unlock();

            const pthread_mutex_t& getMutex() const { return m_mutex; }

        protected:
            pthread_mutex_t         m_mutex;
            pthread_mutexattr_t     m_mutexattr;
        };

        class AutoLock
        {
        public:
            AutoLock(Mutex &mutex);
            ~AutoLock();

        private:
            Mutex &m_mutex;
        };

        class Condition : public Mutex
        {
        public:
            Condition();
            ~Condition();

            void wait();
            void signal();

        private:
            pthread_cond_t      m_cond;
        };

    }

}


#endif //BASEUTIL_LOCK_H
