//
// Created by liuzheng on 18-4-18.
//

#ifndef DBSERVER_SESSIONMODEL_H
#define DBSERVER_SESSIONMODEL_H


#include <cstdint>
#include <list>
#include "pdu/protobuf/youliao.base.pb.h"

using namespace youliao::pdu;

class SessionModel {
public:
    static SessionModel* instance();
    ~SessionModel();

    //获取Session id
    //flag用于判断session是否存在(但是已经删除了，即status=1)
    //type 1 好友 2群组 3 验证消息
    uint32_t getSessionId(uint32_t userId, uint32_t otherId, uint32_t type, bool flag = false);

    //新增
    uint32_t addSession(uint32_t userId, uint32_t otherId, uint32_t type);

    //更新
    bool updateSession(uint32_t sessionId);

    //删除
    bool removeSession(uint32_t sessionId);

    //置顶
    bool topSession(uint32_t sessionId);

    //获取指定用户的所有session
    bool getSessions(uint32_t userId, std::list<base::SessionInfo> &sessionList);

private:
    SessionModel();
    static SessionModel *m_instance;
};


#endif //DBSERVER_SESSIONMODEL_H
