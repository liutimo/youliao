#ifndef LOGINCONN_H
#define LOGINCONN_H
#include "BaseConn.h"
#include "BasePdu.h"
using namespace youliao::network;
using namespace youliao::pdu;
class LoginConn : public BaseConn
{
public:
    LoginConn();
    virtual ~LoginConn();

    void connect(const std::string &server_ip, uint16_t port);

    void handlePdu(BasePdu *) override;
private:
    void _ConnectToMsgServer(const std::string &server_ip, uint16_t port);
};

#endif // LOGINCONN_H
