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
private:
    void _HandlClientLoginRequest(BasePdu *);
    void _HandleHeartBeat(BasePdu*);

};

typedef  __gnu_cxx::hash_map<int, ClientConn*> ClientConnMap_t;

#endif //MSGSERVER_CLIENTCONN_H
