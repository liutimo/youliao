//
// Created by liuzheng on 18-5-7.
//

#ifndef DBSERVER_GROUPMODEL_H
#define DBSERVER_GROUPMODEL_H

#include <string>
#include <list>
#include "pdu/protobuf/youliao.base.pb.h"
using namespace youliao::pdu;
class GroupModel {
public:
    GroupModel(const GroupModel&) = delete;
    GroupModel& operator=(const GroupModel&) = delete;
    static GroupModel* instance();


    uint32_t createGroup(uint32_t userId, std::string groupName, base::GroupType type, base::GroupVerifyType verify, uint32_t max_members);

    bool addMembers(uint32_t groupId, const std::list<uint32_t> &members);

    //添加成员
    bool addMember(uint32_t groupId, uint32_t memberId);

    //添加管理员
    bool addManager(uint32_t groupId, uint32_t managerId);

    //添加群主
    bool addCreator(uint32_t groupId, uint32_t creator);

    bool getGroupInfoByGroupId(uint32_t groupId, base::GroupInfo &groupInfo);

    //获取加入的群
    bool getOtherGroupByUserId(uint32_t userId, std::list<uint32_t> &groups);

    //获取用户创建的群
    bool getSelfGroupByUserId(uint32_t userId, std::list<uint32_t> &groups);

    //获取群成员
    bool getMembersByGroupId(uint32_t groupId, std::list<base::MemberInfo> &members);

    //修改群名片
    bool modifyGroupCard(uint32_t groupId, uint32_t memberId, const std::string &groupCard);

    //搜索群
    bool searchGroup(uint32_t userId, const std::string &searchData ,base::SearchType tye, std::list<base::GroupInfo> &groupList);

    //退群
    bool exitGroup(uint32_t groupId, uint32_t userId);

    //设置管理员
    bool setGroupManager(uint32_t groupId, uint32_t memberId);


    //更换群头像
    bool modifyGroupHeader(uint32_t groupId, const std::string &url);

    //获取最新的消息ID
    uint32_t getLatestMsgIdByGroupId(uint32_t groupId);

    //获取群组验证类型
    base::GroupVerifyType getVerofyTypeByGroupId(uint32_t groupId);

    uint32_t getRelationId(uint32_t groupId, uint32_t userId);

    //保存新的加入群请求
    uint32_t addNewGroupRequest(uint32_t requestUserId, uint32_t groupId, const std::string &validateData);

    //处理加群申请
    bool updateAddGroupRequest(uint32_t requestUserId, uint32_t groupId, uint32_t handleUserId, base::GroupVerifyResult result);

    //获取加入群组的时间
    uint32_t getJoinGroupTime(uint32_t memberId, uint32_t groupId);

    //解散群组
    bool ungroup(uint32_t groupId);
private:
    bool getGroupManagers(uint32_t groupId, std::list<uint32_t> &managers);
    bool getGroupMembers(uint32_t groupId, std::list<uint32_t> &members);
    uint32_t getId(uint32_t groupId, uint32_t userId);
    bool addOne(uint32_t groupId, uint32_t userId, uint32_t type, uint32_t status);  // 0普通 1管理员 2群主

    GroupModel();
    static GroupModel* m_instance;
};


#endif //DBSERVER_GROUPMODEL_H
