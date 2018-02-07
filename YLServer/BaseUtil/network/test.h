/*================================================================
*   
*   文件名称: test.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午2:07
*   描   述: 测试
*
================================================================*/

#ifndef BASEUTIL_TEST_H
#define BASEUTIL_TEST_H

#include "BasicSocket.h"

using namespace youliao::network;

void testconnect()
{
    BaseSocket *baseSocket = new BaseSocket();

    baseSocket->connect("127.0.0.1", 8001, nullptr, nullptr);
}


#endif //BASEUTIL_TEST_H
