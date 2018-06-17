//
// Created by liuzheng on 18-4-17.
//

#ifndef DBSERVER_MESSAGEMODL_H
#define DBSERVER_MESSAGEMODL_H

#include <pdu/protobuf/youliao.server.pb.h>
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"
#include "pdu/protobuf/youliao.message.pb.h"
using namespace youliao::pdu;

class MessageModel {

public:
    static MessageModel* instance();
    ~MessageModel();

//    bool getFriendOnlineStatus(uint32_t friend_id, int &msg_idx);

    bool saveMessage(uint32_t senderId, uint32_t receiverId, uint32_t messageType,
                     uint32_t createTime, uint32_t messageId, const std::string &content);

    bool saveAudioMessage(uint32_t senderId, uint32_t receiverId, uint32_t createTime,
                          uint32_t messageId, const std::string &content);

    bool saveGroupMesage(uint32_t groupId, uint32_t senderId, uint32_t messageType, uint32_t createTime,
                         uint32_t messageId, const std::string &content);

    bool getLastMessage(uint32_t senderId, uint32_t receiverId, std::string &content, uint32_t &latestTime);

    bool getLastestGroupMessage(uint32_t groupId, std::string &content, uint32_t &latestTime);

    bool getLatestMsgId(uint32_t userId, uint32_t senderId, uint32_t &msgId);

    uint32_t getMsgIndex(uint32_t userId, uint32_t senderId, uint32_t msgId);

    bool messageAck(uint32_t senderId, uint32_t receiverId, uint32_t msgId);

    bool getOfflineMessage(uint32_t userId, message::GetOfflineMessageRespone &respone);
private:
    MessageModel();

    static MessageModel* m_instance;


};


#endif //DBSERVER_MESSAGEMODL_H
