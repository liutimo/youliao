#ifndef LOGINCONN_H
#define LOGINCONN_H
#include "../base/BaseConn.h"
#include "../base/BasePdu.h"
using namespace youliao::network;
using namespace youliao::pdu;
class LoginConn : public BaseConn
{
public:
    LoginConn();
    virtual ~LoginConn();

    bool connect(const std::string &server_ip, uint16_t port);
    void onConfirm();
    void handlePdu(BasePdu *) override;
private:
    void _ConnectToMsgServer(const std::string &server_ip, uint16_t port);
};

#endif // LOGINCONN_H
