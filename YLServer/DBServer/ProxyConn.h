/*================================================================
*   
*   文件名称: ProxyConn.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月10日　 上午11:43
*   描   述:
*
================================================================*/


#ifndef DBSERVER_PROXYCONN_H
#define DBSERVER_PROXYCONN_H

#include "network/BaseConn.h"
#include "pdu/BasePdu.h"

using namespace youliao::pdu;
using namespace youliao::network;
class ProxyConn : public BaseConn{
public:
    ProxyConn();
    ~ProxyConn();

    void onRead() override;
    void onConnect(net_handle_t handle) override ;
    void close();
    void onClose() override ;

    void handlePdu(BasePdu *) override;
private:

};

ProxyConn *findProxyConn(net_handle_t handle);

#endif //DBSERVER_PROXYCONN_H
