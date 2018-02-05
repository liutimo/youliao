#include "netservice.h"
#include "netlib.h"
#include "YLConn.h"
#include "YLPduBase.h"
#include <QDebug>
#include "protobuf/YLBase.pb.h"
#include "protobuf/YLLogin.pb.h"

void conn2server(void*callback_data, uint8_t msg, uint32_t fd, void* pParam)
{
    if (msg == NETLIB_MSG_CONFIRM)
    {
        //连接成功
        //发送请求
        //请求消息服务器列表
        YL::Login::YLMsgServerRequest r;
        YLPdu pdu;
        pdu.setPBMsg(&r);
        pdu.setCID(YL::Base::CID_LOGIN_REQ_MSGSERVER);
        pdu.setSID(YL::Base::SID_LOGIN);
        pdu.setSeqNum(1);

        netlib_send(fd, pdu.getBuffer(), pdu.getLength());

        netlib_option(fd, NETLIB_OPT_SET_CALLBACK, (void*)conn_callback);
    }
}

//////////////////////////////////////////
YLNetService *YLNetService::m_service = nullptr;

YLNetService::YLNetService(QObject *parent) : QObject(parent)
{
    timer = new QTimer;
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, [this](){start();timer->stop();});
}

YLNetService* YLNetService::instance()
{
    if (m_service == nullptr)
        m_service = new YLNetService;
    return m_service;
}

void YLNetService::start()
{
    netlib_init();

    int ret = netlib_connect("127.0.0.1", 8001, conn2server, nullptr);

    if (ret == -1)
    {
        emit error(Connect2ServerFailed);
        return;
    }
    netlib_eventloop();;

    netlib_destroy();
}
