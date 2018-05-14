//
// Created by liuzheng on 18-5-13.
//

#ifndef LOGINSERVER_MSGSERVERCONN_H
#define LOGINSERVER_MSGSERVERCONN_H

#include "network/BaseConn.h"
#include "pdu/BasePdu.h"

using namespace youliao::network;
using namespace youliao::pdu;

class MsgServerConn : public BaseConn
{
public:
    MsgServerConn();
    virtual ~MsgServerConn();

    virtual void close();
    virtual void onConnect(net_handle_t handle) override;
    virtual void onClose() override;
//    virtual void onTimer() override;

    virtual void handlePdu(BasePdu *) override;

private:
    void _HandleGetFileServerIpRequest(BasePdu *);
    void _HandleMsgFileTransfreRequest(BasePdu *);
private:
    bool m_connected;
};

void initFileMsgServerConn();
void msgServerConnCallback(void *callback_data, uint8_t msg, int handle, void*);


#endif //LOGINSERVER_MSGSERVERCONN_H
