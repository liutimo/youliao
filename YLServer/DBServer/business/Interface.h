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

    //获取好友分组信息
    void getFriendGroups(BasePdu *basePdu, uint32_t conn_uuid);

    //获取好友列表
    void getFriendList(BasePdu* basePdu, uint32_t conn_uuid);

    //用户离线
    void logout(BasePdu* basePdu, uint32_t conn_uuid);

    //获取在线好友
    void getOnlineFriends(BasePdu *basePdu, uint32_t conn_uid);

    //修改个性签名
    void modifySignature(BasePdu *basePdu, uint32_t conn_uid);

    //新的好友分组
    void addFriendGroup(BasePdu *basePdu, uint32_t conn_uid);

    //重命名分组
    void renameFriendGroup(BasePdu *basePdu, uint32_t conn_uid);

    //删除分组
    void deleteFriendGroup(BasePdu *basePdu, uint32_t conn_uid);
}



#endif //DBSERVER_INTERFACE_H
