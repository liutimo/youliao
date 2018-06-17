//
// Created by liuzheng on 18-3-21.
//

#ifndef MSGSERVER_DBSERVCONN_H
#define MSGSERVER_DBSERVCONN_H
#include "network/BaseConn.h"
#include "pdu/BasePdu.h"
#include "util/util.h"
#include "network/ServerInfo.h"
using namespace youliao::network;
using namespace youliao::pdu;

class DBServConn : public BaseConn
{
public:
    DBServConn();
    virtual ~DBServConn();

    void connect(const std::string &server_ip, uint16_t server_port, uint32_t serv_idx);

    virtual void close();
    void onClose() override;
    void handlePdu(BasePdu *) override;

    bool isOpen() const { return m_open; }

private:
    void _HandleValidateRespone(BasePdu *);
    void _HandleRegisterRespone(BasePdu *);
    void _HandleFriendGroupsRespone(BasePdu *);
    void _HandleFriendListRespone(BasePdu *);
    void _HandleSignatureChangedRespone(BasePdu *);
    void _HandleAddNewFriendGroupRespone(BasePdu *);
    void _HandleGetSessionsRespone(BasePdu *);
    void _HandleAddSessionRespone(BasePdu *);
    void _HandleSearchFriendRespone(BasePdu *);
    void _HandleGetLatestMsgIdRespone(BasePdu *);
    void _HandleGetAddRequestHistoryRespone(BasePdu *);
    void _HandleCreateGroupRespone(BasePdu *);
    void _HandleGetGroupListRespone(BasePdu *);
    void _HandleGetGroupMemberRespone(BasePdu *);
    void _HandleSearchGroupRespone(BasePdu *);
    void _HandleAddGroupRespone(BasePdu *);
    void _HandleVerifyNotify(BasePdu *);
    void _HandleOfflineMessageRespone(BasePdu *);
    void _HandleModifyIconRespone(BasePdu *);
    void _HandleGetLatestGroupMsgIdRespone(BasePdu *);
    void _HandleExitGroupRespone(BasePdu *);
    void _HandleModifyGroupHeaderRespone(BasePdu*);
    void _HandleSetManagerRespone(BasePdu *);
    void _HandleKcikOutMemberRespone(BasePdu *);
    void _HandleGroupAddRequestRespone(BasePdu *);
    void _HandleDeleteFriendRespone(BasePdu *);
    void _HandleGetFriendInformationRespone(BasePdu *);
    void _HandleAddFriendRespone(BasePdu *);
    void _HandleModfiyInformationRespone(BasePdu *);

    uint32_t   m_server_index;
    bool       m_open;
};


void init_db_serv_conn(serv_info_t* server_list, uint32_t server_count, uint32_t curr_conn_cnt);
DBServConn *get_db_server_conn();



#endif //MSGSERVER_DBSERVCONN_H
