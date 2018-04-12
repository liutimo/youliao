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

    //friend group
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_GET_GROUPS_REQUEST, DB_INTERFACE::getFriendGroups));

    //friend list
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_GET_REQUEST, DB_INTERFACE::getFriendList));

    //logout
    m_handler_map.insert(std::make_pair(CID_SERVER_USER_LOGOUT, DB_INTERFACE::logout));

    //获取在线好友
    m_handler_map.insert(std::make_pair(CID_SERVER_GET_ONLINE_FRIENDS_REQUEST, DB_INTERFACE::getOnlineFriends));

    //修改个性签名
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_SIGNATURE_CHANGED_REQUEST, DB_INTERFACE::modifySignature));

    //新增好友列表分组
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_ADD_FRIEND_GROUP_REQUEST, DB_INTERFACE::addFriendGroup));

    //重命名好友分组
    m_handler_map.insert(std::make_pair(CID_FRIENDLIST_RENAME_FRIEND_GROUP_REQUEST, DB_INTERFACE::renameFriendGroup));
}

pdu_handler_t HandlerMap::getHandler(uint16_t cid)
{
    HandlerMap_t::iterator iter = m_handler_map.find(cid);
    if (iter != m_handler_map.end())
        return iter->second;
    else
        return nullptr;
}