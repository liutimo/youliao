#ifndef MSGSERVCONN_H
#define MSGSERVCONN_H

#include "base/BaseConn.h"
#include "base/BasePdu.h"
#include <list>
#include <string>


using namespace youliao::network;
using namespace youliao::pdu;

class MsgServConn : public BaseConn
{
public:
    MsgServConn();

    void connect(const std::string &server_ip, uint16_t port);
    void handlePdu(BasePdu*) override;

    //在BaseConn中, handlePdu后,pdu被delete.
    //但是在这个类中,pdu会被放入静态链表中.pdu需要在其余地方释放
    void onRead() override;
};

extern std::list<BasePdu*> g_pdu_list;
extern Condition           g_condition;


#endif // MSGSERVCONN_H
