/*================================================================
*   
*   文件名称: task.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午7:48
*   描   述: 任何需要放入ThreadPool的任务都需要继承这个抽象类并且实现run()方法.
*
================================================================*/


#ifndef BASEUTIL_TASK_H
#define BASEUTIL_TASK_H

namespace youliao
{
    namespace thread
    {
        class Task
        {
        public:
            Task() {};
            virtual ~Task(){}

            virtual void run() = 0;

        };

    }
}

#endif //BASEUTIL_TASK_H
