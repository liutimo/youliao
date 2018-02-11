/*================================================================
*   
*   文件名称: Login.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月10日　 上午10:39
*   描   述:
*
================================================================*/


#ifndef DBSERVER_LOGIN_H
#define DBSERVER_LOGIN_H

#include "pdu/BasePdu.h"

using namespace youliao::pdu;
namespace DB_PROXY
{
   void doLogin(BasePdu *pdu, uint32_t conn_uuid);
}




#endif //DBSERVER_LOGIN_H
