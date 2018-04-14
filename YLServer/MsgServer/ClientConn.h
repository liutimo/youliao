/*================================================================
*   
*   文件名称: ClientConn.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月09日　 下午8:45
*   描   述:
*
================================================================*/


#ifndef MSGSERVER_CLIENTCONN_H
#define MSGSERVER_CLIENTCONN_H

#include "network/BaseConn.h"
#include "pdu/BasePdu.h"
#include "util/util.h"
using namespace youliao::network;
using namespace youliao::pdu;

class ClientConn : public BaseConn{
public:
    ClientConn();
    ~ClientConn();

    void onConnect(net_handle_t handle) override;
    void onClose() override ;

    void handlePdu(BasePdu *) override ;
    uint32_t getUserId() { return m_user_id; }

private:
    void _HandleClientLoginRequest(BasePdu *);
    void _HandleClientLoginOutRequest(BasePdu *);
    void _HandleHeartBeat(BasePdu*);
    void _HandleGroupsRequest(BasePdu*);
    void _HandleFriendListGetRequest(BasePdu *);
    void _HandleMessageDataRequest(BasePdu *);
    void _HandleSignatureChangeRequest(BasePdu *);
    void _HandleAddFriendGroupRequest(BasePdu *);
    void _HandleRenameFriendGroupRequest(BasePdu *);
    void _HandleDeleteFriendGroupRequest(BasePdu *);
    void _HandleMoveFriendToGroupRequest(BasePdu *);
    void _HandleDeleteFriendRequest(BasePdu*);
    void _HandleModifyFriendRemarkRequest(BasePdu *);

public:
    uint64_t m_last_heart_beat_tick;    //最后一次收到心跳包的时间

private:
    uint32_t  m_user_id;
};

typedef  __gnu_cxx::hash_map<int, ClientConn*> ClientConnMap_t;
ClientConn *findConn(uint32_t handle);

void setMsgServIdx(uint32_t msg_serv_idx);
uint32_t  getMsgServIdx();
#endif //MSGSERVER_CLIENTCONN_H
