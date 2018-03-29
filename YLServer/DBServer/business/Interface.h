//
// Created by liuzheng on 18-3-25.
//

#ifndef DBSERVER_INTERFACE_H
#define DBSERVER_INTERFACE_H

#include "pdu/BasePdu.h"

using namespace youliao::pdu;

namespace DB_INTERFACE
{
    //用户登录
    void login(BasePdu* basePdu, uint32_t conn_uuid);

    //获取好友列表
    void getFriendList(BasePdu* basePdu, uint32_t conn_uuid);
}



#endif //DBSERVER_INTERFACE_H
