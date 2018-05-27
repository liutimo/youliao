//
// Created by liuzheng on 18-5-13.
//

#ifndef MSGSERVER_FILESERVERCONN_H
#define MSGSERVER_FILESERVERCONN_H

#include "pdu/BasePdu.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "network/BaseConn.h"
#include "network/ServerInfo.h"

using namespace youliao::network;
using namespace youliao::pdu;

class FileServerConn : public BaseConn
{
public:
    FileServerConn();
    virtual ~FileServerConn();

    bool isOpen() { return m_open;}

    void connect(const std::string &serverIp, uint16_t serverPort, uint32_t serverIndex);
    virtual void close();
    void onConfirm() override;
    virtual void onClose() override;
//    virtual void onTimer();

    virtual void handlePdu(BasePdu *) override;
    const std::list<base::IpAddress>* getFileServerIPList() { return &m_ip_list; }

private:
    void _HandleGetFileServerIpRespone(BasePdu *);
    void _HandleFileMsgTransferRespone(BasePdu *);


private:
    bool        m_open;
    uint32_t    m_server_index;
    uint64_t    m_connect_time;
    std::list<base::IpAddress> m_ip_list;
};

void init_file_server_conn(serv_info_t *server_list, uint32_t server_count);
bool is_file_server_availabel();
FileServerConn *get_random_file_server_conn();


#endif //MSGSERVER_FILESERVERCONN_H
