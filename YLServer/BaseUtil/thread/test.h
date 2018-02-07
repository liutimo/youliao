/*================================================================
*   
*   文件名称: test.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午10:03
*   描   述: 测试thread模块
*
================================================================*/


#ifndef BASEUTIL_TEST_H
#define BASEUTIL_TEST_H


#include <iostream>
#include <list>

#include "Thread.h"
#include "Lock.h"
#include "ThreadPool.h"
#include "task.h"

#include <unistd.h>

static youliao::thread::Condition condition;
static youliao::thread::Mutex mutex;

static std::list<int> g_list;

static int c = 0;

class MThread : public youliao::thread::Thread
{
public:
    MThread()
    {

    }

    ~MThread()
    {
        std::cout << "析构MThread" << std::endl;
    }

    void run() override
    {
        for (int i = 0; i < 10000; ++i)
        {
            mutex.lock();
            ++c;
            mutex.unlock();
        }
    }

private:

};

class PushThread : public youliao::thread::Thread
{
public:
    PushThread()
    {

    }
    ~PushThread()
    {

    }

    void run() override
    {
        for (int i = 1; i < 1000; ++i)
        {
            condition.lock();
            g_list.push_back(i);
            std::cout << "push " << i << std::endl;
            condition.signal();
            condition.unlock();
        }

        mutex.lock();
        c = 1;
        mutex.unlock();
    }
};

class PopThread : public youliao::thread::Thread
{
public:
    PopThread()
    {

    }
    ~PopThread()
    {

    }

    void run() override
    {

        while (1)
        {
            condition.lock();

            if (g_list.empty())
                condition.wait();

            std::cout << "pop: " << g_list.front() << std::endl;
            g_list.pop_front();

            condition.unlock();

            mutex.lock();
//            if (c == 1  && g_list.empty())
//                break;
            mutex.unlock();
        }

    }
};

void testMutex()
{
    MThread *m;
    MThread* threads[100];
    for(int i = 0; i < 100; ++i)
    {
        m = new MThread();
        m->start();
        threads[i] = m;
    }

    while (1)
    {
        int i = 0;
        for (i; i < 100; ++i)
        {
            if (threads[i]->isRunning())
                break;
        }

        if (i == 100)
            break;
    }

    std::cout << c << std::endl;
}


class MTask : public youliao::thread::Task
{
public:
    MTask()
    {

    }

    ~MTask()
    {

    }

    void run() override
    {
        sleep(1);
        mutex.lock();
        ++c;
        std::cout << "c = " << c << std::endl;
        mutex.unlock();
    }
};


void testCondition()
{
    PushThread *pushThread = new PushThread;
    pushThread->start();

    PopThread *popThread = new PopThread;
    popThread->start();

    popThread->join();
    pushThread->join();

}


void testThreadPool()
{
    youliao::thread::ThreadPool *pThreadPool = new youliao::thread::ThreadPool(100);

    for (int i = 0; i < 200; ++i)
    {
        MTask *pMTask = new MTask;
        pThreadPool->addTask(pMTask);
    }

    while (1)
    {
        int i = 0;
        ++i;
        if  (i > 100)
            i = 0;
        if (i == -1)
            break;
    }
}

#endif //BASEUTIL_TEST_H
