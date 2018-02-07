/*================================================================
*   
*   文件名称: Lock.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午8:34
*
================================================================*/

#include "Lock.h"
#include <iostream>
using namespace youliao::thread;

Mutex::Mutex()
{
    pthread_mutexattr_init(&m_mutexattr);
    //避免死锁
    pthread_mutexattr_settype(&m_mutexattr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&m_mutex, NULL);
}

Mutex::~Mutex()
{
    std::cout << "析构Mutex" << std::endl;
    pthread_mutexattr_destroy(&m_mutexattr);
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::lock()
{
    pthread_mutex_lock(&m_mutex);
}

void Mutex::trylock()
{
    pthread_mutex_trylock(&m_mutex);
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&m_mutex);
}

//////////////////////////////////
Condition::Condition() : Mutex()
{
    pthread_cond_init(&m_cond, NULL);
}

Condition::~Condition()
{
    std::cout << "析构Condition" << std::endl;
    pthread_cond_destroy(&m_cond);
}

void Condition::wait()
{
    pthread_cond_wait(&m_cond, &m_mutex);
}

void Condition::signal()
{
    pthread_cond_signal(&m_cond);
}