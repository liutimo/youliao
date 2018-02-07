/*================================================================
*   
*   文件名称: ThreadPool.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午9:40
*   描   述:
*
================================================================*/


#ifndef BASEUTIL_THREADPOOL_H
#define BASEUTIL_THREADPOOL_H

#include <list>
#include <vector>
#include "Thread.h"
namespace youliao
{
    namespace thread
    {

        class Task;
        class Condition;

        class WorkThread : public Thread
        {
        public:
            WorkThread();
            ~WorkThread();

            void run() override;
            void pushTask(Task *task);

        private:
            Condition*          m_condition;
            std::list<Task*>    m_task_list;
        };


        class ThreadPool {
        public:
            ThreadPool(int initCount = 20);
            ~ThreadPool();

            void addTask(Task *task);

        private:
            std::vector<WorkThread*>  m_workthread_list;
            int     m_thread_count;
        };
    }
}


#endif //BASEUTIL_THREADPOOL_H
