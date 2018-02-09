/*================================================================
*   
*   文件名称: LoginConn.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月08日　 下午10:03
*
================================================================*/


#include <pdu/BasePdu.h>
#include "LoginConn.h"
#include "network/BasicSocket.h"
#include "network/netlib.h"
#include "pdu/BasePdu.h"

using namespace youliao::pdu;

//这两个map, 会在onConnect函数中通过type参数来决定将哪个map传递给回调函数
static ConnMap_t g_client_conn_map;
static ConnMap_t g_server_conn_map;


LoginConn::LoginConn() : BaseConn()
{

}

LoginConn::~LoginConn()
{

}


void LoginConn::onConnect(net_handle_t handle, ConnType type)
{
    m_handle = handle;
    m_conn_type = type;

    ConnMap_t *connMap = &g_server_conn_map;

    if (type == CONN_TYPE_CLIENT)
    {
        connMap = &g_client_conn_map;
    }

    connMap->insert(std::make_pair(m_handle, this));

    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)connMap);
}


void LoginConn::handlePdu()
{
    pdu_header_t header;

//    header.length = (m_read_buf.getBuffer()[0] << 24) | (m_read_buf.getBuffer()[1] << 16) | (m_read_buf.getBuffer()[2] << 8) | (m_read_buf.getBuffer()[3]);
//    header.sid = (m_read_buf.getBuffer()[4] << 8) | (m_read_buf.getBuffer()[5]);
//    header.cid = (m_read_buf.getBuffer()[6] << 8) | (m_read_buf.getBuffer()[7]);
//    m_read_buf.read(nullptr, sizeof(pdu_header_t));

    header.length = m_read_buf.readUInt32();
    header.sid = m_read_buf.readUInt16();
    header.cid = m_read_buf.readUInt16();

    std::string msg = m_read_buf.readString(header.length - sizeof(pdu_header_t));

    log("m_handle = %d, pdu.length=%d, pdu.sid = %d, pdu.cid = %d  msg = %s", m_handle, header.length, header.sid, header.cid, msg.c_str());

}