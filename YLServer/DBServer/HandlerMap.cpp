//
// Created by liuzheng on 18-3-25.
//

#include "HandlerMap.h"
#include "business/Interface.h"
#include "pdu/protobuf/youliao.base.pb.h"
using namespace youliao::pdu::base;

HandlerMap* HandlerMap::s_handler_instance = nullptr;

HandlerMap::HandlerMap()
{

}

HandlerMap::~HandlerMap()
{

}

HandlerMap* HandlerMap::instance()
{
    if (!s_handler_instance)
    {
        s_handler_instance = new HandlerMap;
        s_handler_instance->init();
    }

    return s_handler_instance;
}

void HandlerMap::init()
{
    //login validate
    m_handler_map.insert(std::make_pair(CID_SERVER_VALIDATE_REQUEST, DB_INTERFACE::login));

    //注册
    m_handler_map.insert(std::make_pair(CID_LOGIN_REGISTER_REQUEST, DB_INTERFACE::registerUser));

    //friend group
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_GET_GROUPS_REQUEST, DB_INTERFACE::getFriendGroups));

    //friend list
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_GET_REQUEST, DB_INTERFACE::getFriendList));

    //logout
//    m_handler_map.insert(std::make_pair(CID_SERVER_USER_LOGOUT, DB_INTERFACE::logout));

    //获取在线好友
//    m_handler_map.insert(std::make_pair(CID_SERVER_GET_ONLINE_FRIENDS_REQUEST, DB_INTERFACE::getOnlineFriends));

    //修改个性签名
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_SIGNATURE_CHANGED_REQUEST, DB_INTERFACE::modifySignature));

    //新增好友列表分组
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_ADD_FRIEND_GROUP_REQUEST, DB_INTERFACE::addFriendGroup));

    //重命名好友分组
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_RENAME_FRIEND_GROUP_REQUEST, DB_INTERFACE::renameFriendGroup));

    //删除好友分组
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_DELETE_FRIEND_GROUP_REQUEST, DB_INTERFACE::deleteFriendGroup));

    //移动好友到指定分组
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_MOVE_FRIEND_TO_GROUP_REQUEST, DB_INTERFACE::moveFriendToGroup));

    //删除好友
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_DELETE_FRIEND_REQUEST, DB_INTERFACE::deleteFriend));

    //修改好友备注
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_MODIFY_FRIEND_REMARK_RQUEST, DB_INTERFACE::modifyFriendRemark));

    //转发消息
//    m_handler_map.insert(std::make_pair(CID_SERVER_GET_FRIEND_ONLINE_STATUS, DB_INTERFACE::getOnlineFriendStatus));

    //保存消息
    m_handler_map.insert(std::make_pair(CID_MESSAGE_SAVE, DB_INTERFACE::saveMessage));

    //请求session列表
    m_handler_map.insert(std::make_pair(CID_SESSIONLIST_GET_SESSIONS_REQUEST, DB_INTERFACE::getSessions));

    //删除session
    m_handler_map.insert(std::make_pair(CID_SESSIONLIST_DEL_SESSION, DB_INTERFACE::deleteSession));

    //置顶session
    m_handler_map.insert(std::make_pair(CID_SESSIONLIST_TOP_SESSION, DB_INTERFACE::topSession));

    //搜索好友
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_SEARCH_FRIEND_REQUEST, DB_INTERFACE::searchFriend));

    //添加好友
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_ADD_FRIEND_REQUEST, DB_INTERFACE::addFriend));

    //添加好友响应
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_ADD_FRIEND_RESPONE, DB_INTERFACE::addFriendRespone));

    //获取最新消息ID
    m_handler_map.insert(std::make_pair(CID_MESSAGE_GET_LATEST_MSG_ID_REQUEST, DB_INTERFACE::getLatestMsgId));

    //获取好友请求的历史记录
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_GET_REQUEST_HISTORY_REQUEST, DB_INTERFACE::getAddRequestHistory));

    //创建群组
    m_handler_map.insert(std::make_pair(CID_GROUP_CREATE_REQUEST, DB_INTERFACE::createGroup));

    //获取群组列表
    m_handler_map.insert(std::make_pair(CID_GROUP_GET_LIST_REQUEST, DB_INTERFACE::getGroupList));

    //获取群成员
    m_handler_map.insert(std::make_pair(CID_GROUP_GET_MEMBER_REQUEST, DB_INTERFACE::getGroupMember));

    //修改群名片
    m_handler_map.insert(std::make_pair(CID_GROUP_MODIFY_CARD_RESQUEST, DB_INTERFACE::modifyGroupCard));

    //搜索群组
    m_handler_map.insert(std::make_pair(CID_GROUP_SEARCH_GROUP_REQUEST, DB_INTERFACE::searchGroup));

    //添加群组
    m_handler_map.insert(std::make_pair(CID_GROUP_ADD_GROUP_REQUEST, DB_INTERFACE::addGroup));

    //消息确认
    m_handler_map.insert(std::make_pair(CID_MESSAGE_DATA_ACK, DB_INTERFACE::readMessageAck));

    //离线消息
    m_handler_map.insert(std::make_pair(CID_MESSAGE_GET_OFFLINE_MESSAGE_REQUEST, DB_INTERFACE::getOfflineMessageData));

    //修改资料
    m_handler_map.insert(std::make_pair(CID_OTHER_MODIFY_INFORMATION_REQUEST, DB_INTERFACE::modifyInformation));

    //修改头像
    m_handler_map.insert(std::make_pair(CID_OTHER_MODIFY_USER_HEADER_REQUEST, DB_INTERFACE::modifyUserIcon));

    //获取群组最新ID
    m_handler_map.insert(std::make_pair(CID_GROUP_GET_LATEST_MSG_ID_REQUEST, DB_INTERFACE::getLatestGroupMsgId));

    //退出群组
    m_handler_map.insert(std::make_pair(CID_GROUP_EXIT_GROUP_REQUEST, DB_INTERFACE::exitGroup));

    //修改群头像
    m_handler_map.insert(std::make_pair(CID_GROUP_MODIFY_HEADER_REQUEST, DB_INTERFACE::modifyGroupHeader));

    //设置管理员
    m_handler_map.insert(std::make_pair(CID_GROUP_SET_MANAGER_REQUEST, DB_INTERFACE::setGroupManager));

    //踢出群组
    m_handler_map.insert(std::make_pair(CID_GROUP_KICK_OUT_REQUEST, DB_INTERFACE::kickOutGroupMember));

    //新增sesson
    m_handler_map.insert(std::make_pair(CID_SESSIONLIST_ADD_SESSION_REQUEST, DB_INTERFACE::createNewSession));

    //验证信息处理结果
    m_handler_map.insert(std::make_pair(CID_GROUP_VERIFY_RESULT, DB_INTERFACE::handleVerifyGroupResult));

    //获取好友详细资料
    m_handler_map.insert(std::make_pair(CID_OTHER_GET_FRIEND_INFORMATION_REQUEST, DB_INTERFACE::getFriendInformation));

    //获取群组历史消息
    m_handler_map.insert(std::make_pair(CID_GROUP_GET_OFFLINE_MESSAGE_REQUEST, DB_INTERFACE::getGroupOfflineMessage));

    //离线文件传输完成
    m_handler_map.insert(std::make_pair(CID_FILE_OFFLINE_UPLOAD_COMPLETE, DB_INTERFACE::offlineFileUploadComplete));

    //获取离线文件
    m_handler_map.insert(std::make_pair(CID_FILE_GET_OFFLINE_FILE_REQUEST, DB_INTERFACE::getOfflineFile));
}

pdu_handler_t HandlerMap::getHandler(uint16_t cid)
{
    HandlerMap_t::iterator iter = m_handler_map.find(cid);
    if (iter != m_handler_map.end())
        return iter->second;
    else
        return nullptr;
}