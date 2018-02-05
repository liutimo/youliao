//
// Created by liuzheng on 18-2-5.
//

#ifndef UTIL_YLCONN_H
#define UTIL_YLCONN_H

#include "netlib.h"
#include "common.h"
#include "YLPduBase.h"

const int SERVER_HEARTBEAT_INTERVAL     = 5000;     //服务器之间的心跳包间隔
const int SERVER_TIMEOUT                = 30000;
const int CLINET_HEARTBEAT_INTERVAL     = 30000;
const int CLIENT_TIMEOUT                = 120000;
const int READ_BUFFER_SIZE              = 2048;

class YLConn {
public:
    YLConn();
    virtual ~YLConn();

    bool isBusy() const { return m_busy; }
    int sendPdu(YLPdu* pdu) { return send(pdu->getBuffer(), pdu->getLength()); }
    int send(void* data, int len);

    //根据子类功能实现具体操作
    virtual void onConnect(int fd) { m_fd = fd; }
    virtual void OnConfirm() {}
    virtual void onRead();
    virtual void onWrite();
    virtual void onClose() { };
    virtual void onWriteCompelete() {}

    virtual void handlePdu(YLPdu *pdu) {}


protected:
    int             m_fd;
    bool            m_busy;

    std::string     m_peer_ip;
    std::string     m_peer_port;
    YLSimpleBuffer  m_in_buf;
    YLSimpleBuffer  m_out_buf;

    bool            m_policy_conn;
    uint32_t        m_recv_bytes;
    uint32_t        m_last_send_tick;
    uint32_t        m_last_recv_tick;
    uint32_t        m_last_all_use_tick;
};

typedef __gnu_cxx::hash_map<int, YLConn*> ConnMap;
typedef __gnu_cxx::hash_map<uint32_t, YLConn*> UserMap;

void conn_callback(void* callback_data, uint8_t msg, uint32_t fd, void* pParam);
void readPolicyFile();

#endif //UTIL_YLCONN_H
