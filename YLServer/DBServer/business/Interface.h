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

    //注册
    void registerUser(BasePdu *basePdu, uint32_t conn_uuid);


    //获取好友分组信息
    void getFriendGroups(BasePdu *basePdu, uint32_t conn_uuid);

    //获取好友列表
    void getFriendList(BasePdu* basePdu, uint32_t conn_uuid);


    //修改个性签名
    void modifySignature(BasePdu *basePdu, uint32_t conn_uid);

    //新的好友分组
    void addFriendGroup(BasePdu *basePdu, uint32_t conn_uid);

    //重命名分组
    void renameFriendGroup(BasePdu *basePdu, uint32_t conn_uid);

    //删除分组
    void deleteFriendGroup(BasePdu *basePdu, uint32_t conn_uid);

    //移动好友到指定分组
    void moveFriendToGroup(BasePdu *basePdu, uint32_t conn_uid);

    //删除好友
    void deleteFriend(BasePdu *basePdu, uint32_t conn_uid);

    //修改好友备注
    void modifyFriendRemark(BasePdu *basePdu, uint32_t conn_uid);



    //获取好友状态
//    void getOnlineFriendStatus(BasePdu *basePdu, uint32_t conn_uid);

    /*****************添加好友*****************/

    //搜索好友
    void searchFriend(BasePdu *basePdu, uint32_t conn_uuid);

    //添加好友
    void addFriend(BasePdu *basePdu, uint32_t conn_uuid);

    //添加好友响应
    void addFriendRespone(BasePdu *basePdu, uint32_t conn_uuid);

    //获取好友历史记录
    void getAddRequestHistory(BasePdu *basePdu, uint32_t conn_uuid);

    //加群请求处理结果
    void handleVerifyGroupResult(BasePdu *basePdu, uint32_t conn_uuid);

    /*******************消息************************/
    //保存消息记录
    void saveMessage(BasePdu *basePdu, uint32_t conn_uuid);

    //消息确认
    void readMessageAck(BasePdu *basePdu, uint32_t conn_uuid);

    //获取消息ID
    void getLatestMsgId(BasePdu *basePdu, uint32_t conn_uuid);

    //获取历史消息
    void getOfflineMessageData(BasePdu *basePdu, uint32_t conn_uuid);

    //获取群组历史消息
    void getGroupOfflineMessage(BasePdu *basePdu, uint32_t conn_uuid);

    /*******************session************************/\
    //获取session列表
    void getSessions(BasePdu *basePdu, uint32_t conn_uid);

    //删除session
    void deleteSession(BasePdu *basePdu, uint32_t conn_uid);

    //置顶session
    void topSession(BasePdu *basePdu, uint32_t conn_uid);

    //新增session
    void createNewSession(BasePdu *basePdu, uint32_t conn_uid);



    /*******************群组************************/
    //创建群组
    void createGroup(BasePdu *basePdu, uint32_t conn_uid);

    //获取群组list
    void getGroupList(BasePdu *basePdu, uint32_t conn_uid);

    //获取群成员
    void getGroupMember(BasePdu *basePdu, uint32_t conn_uuid);

    //修改群名片
    void modifyGroupCard(BasePdu *basePdu, uint32_t conn_uuid);

    //搜索群组
    void searchGroup(BasePdu *basePdu, uint32_t conn_uuid);

    //添加群组
    void addGroup(BasePdu *basePdu, uint32_t conn_uuid);

    //获取群组最新消息ID
    void getLatestGroupMsgId(BasePdu *basePdu, uint32_t conn_uuid);

    //退出群组
    void exitGroup(BasePdu *basePdu, uint32_t conn_uuid);

    //修改群头像
    void modifyGroupHeader(BasePdu *basePdu, uint32_t conn_uuid);

    //设置管理员
    void setGroupManager(BasePdu *basePdu, uint32_t conn_uuid);

    //踢出群组
    void kickOutGroupMember(BasePdu *basePdu, uint32_t conn_uuid);



    /**********************其他************************/
    //修改用户信息
    void modifyInformation(BasePdu *basePdu, uint32_t conn_uuid);

    //修改用户头像
    void modifyUserIcon(BasePdu *basePdu, uint32_t conn_uuid);

    //获取好友详细信息
    void getFriendInformation(BasePdu *basePdu, uint32_t conn_uuid);

}

namespace DB_PRIVATE
{
    void AddValidateMessageSession(uint32_t userId, const std::string &userNick,
                                   const std::string &groupName,uint32_t connUuid);
}



#endif //DBSERVER_INTERFACE_H
