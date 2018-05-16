//
// Created by liuzheng on 18-5-15.
//

#ifndef LOGINSERVER_CLIENTCONN_H
#define LOGINSERVER_CLIENTCONN_H


#include "network/BaseConn.h"
#include "TransferTask.h"
#include "pdu/BasePdu.h"

using namespace youliao::pdu;
using namespace youliao::network;

class ClientConn : public BaseConn
{
public:
    ClientConn();

    virtual ~ClientConn(){}

    virtual void close();

    virtual void onConnect(net_handle_t handle);

    virtual void onClose();

    virtual void onTimer(uint64_t curr_tick);


    void clearTransferTask();


private:
    virtual void handlePdu(BasePdu *);
    void _HandleClientLoginRequest(BasePdu *);
    void _HandleClientGetFileBlockRequest(BasePdu *);
    void _HandleClientGetFileBlockRespone(BasePdu *);


    int _StatesNotify(int state, const std::string& task_id, uint32_t user_id, BaseConn* conn);


private:
    bool m_auth;

    uint32_t m_user_id;
    BaseTransferTask *m_transfer_task;
};

void initClientConn();
void clientConnCallBack(callback_data data, uint8_t, int, void*);

#endif //LOGINSERVER_CLIENTCONN_H
