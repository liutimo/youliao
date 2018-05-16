/*================================================================
*   
*   文件名称: type_define.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午11:50
*   描   述:
*
================================================================*/


#ifndef BASEUTIL_TYPE_DEFINE_H
#define BASEUTIL_TYPE_DEFINE_H

#include <stdint.h>

namespace youliao
{
    namespace network
    {
        //socket handle 实质是描述符
        typedef int net_handle_t;

        typedef void* callback_data;

        const int NETWORK_ERROR = -1;
        const int NETWORK_OK = 0;

        //回调函数,根据type来调用
        typedef void(*callback_t)(void* callback_data, uint8_t type, int handle, void *pParam);

        enum
        {
            NETWORK_CONNECT = 0,    //连接进入
            NETWORK_CONFIRM,        // 连接成功建立后的第一次写
            NETWORK_READ,           //可读
            NETWORK_WRITE,          //可写
            NETWORK_CLOSE           //关闭连接
        };


    }
}

#endif //BASEUTIL_TYPE_DEFINE_H
