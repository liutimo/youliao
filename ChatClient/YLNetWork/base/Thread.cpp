#include "Thread.h"

using namespace youliao::thread;

Thread::Thread() : m_thread_id(0), m_running(false)
{
}

Thread::~Thread()
{
}

void Thread::start()
{
    int ret = pthread_create(&m_thread_id, NULL, start_routine, this);
    if (0 == ret)
        m_running = true;
    else
        return;
}

void Thread::join()
{
    pthread_join(m_thread_id, nullptr);
}

void* Thread::start_routine(void *arg)
{
    Thread *pThread = static_cast<Thread*>(arg);
    pThread->run();
    pThread->m_running = false;
    //execute over
    //exit thread
    pthread_exit(0);
}
