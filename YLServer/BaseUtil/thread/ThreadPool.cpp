/*================================================================
*   
*   文件名称: ThreadPool.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午9:40
*
================================================================*/


#include "ThreadPool.h"
#include "Lock.h"
#include "task.h"
#include <cstdlib>
#include <iostream>
using namespace youliao::thread;

WorkThread::WorkThread() : Thread()
{
    m_condition = new Condition;
}

WorkThread::~WorkThread()
{
    delete m_condition;
}

void WorkThread::pushTask(Task *task)
{
    m_condition->lock();
    m_task_list.push_back(task);
    m_condition->signal();
    m_condition->unlock();
}

void WorkThread::run()
{
    while (1)
    {
        m_condition->lock();

        if (m_task_list.empty())
            m_condition->wait();

        Task *pTask = m_task_list.front();
        m_task_list.pop_front();
        std::cout << "线程:" << m_thread_id;
        pTask->run();

        delete pTask;

        m_condition->unlock();
    }
}


/////////////////////////////////////
ThreadPool::ThreadPool(int initCount) : m_thread_count(initCount)
{
    for (int i = 0; i < m_thread_count; ++i)
    {
        WorkThread *pWorkThread = new WorkThread;
        pWorkThread->start();
        m_workthread_list.push_back(pWorkThread);
    }
}

ThreadPool::~ThreadPool()
{
    for (int i = 0; i < m_thread_count; ++i)
    {
        delete m_workthread_list[i];
    }
    m_workthread_list.clear();
}

void ThreadPool::addTask(Task *task)
{
    //将任务随机放入线程池中的一个线程.
    //
    int idx = rand() % m_thread_count;

    std::cout << "random thread id = " << idx << std::endl;

    m_workthread_list[idx]->pushTask(task);
}


