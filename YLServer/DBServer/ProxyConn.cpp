/*================================================================
*   
*   文件名称: ProxyConn.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月10日　 上午11:43
*   描   述:
*
================================================================*/

#include <list>
#include "ProxyConn.h"
#include "network/netlib.h"
#include "thread/ThreadPool.h"
#include "thread/Lock.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "DBProxyTask.h"
#include "HandlerMap.h"
using namespace youliao::thread;
using namespace youliao::network;
using namespace youliao::pdu;

static BaseConnMap_t g_proxy_conn_map;


Mutex g_mutex;
std::list<Task*> g_task_list;

//处理pdu
ThreadPool g_thread_pool;


ProxyConn *findProxyConn(net_handle_t handle)
{
    auto iter = g_proxy_conn_map.find(handle);
    if (iter != g_proxy_conn_map.end())
    {
        return (ProxyConn *)iter->second;
    }

    return nullptr;
}


ProxyConn::ProxyConn() : BaseConn()
{

}

ProxyConn::~ProxyConn()
{

}

void ProxyConn::onConnect(net_handle_t handle)
{
    m_handle = handle;
    g_proxy_conn_map.insert(std::make_pair(m_handle, this));


    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)&g_proxy_conn_map);
}

void ProxyConn::close()
{
    auto iter = g_proxy_conn_map.find(m_handle);

    if (iter != g_proxy_conn_map.end())
    {
        g_proxy_conn_map.erase(iter);
        netlib_close(m_handle);
    }
}

void ProxyConn::onClose()
{
    close();
}

//pdu需要在其余线程中处理,重新实现该函数
void ProxyConn::onRead()
{
    //全部读入缓冲区
    for (;;)
    {
        int free_buf_size = m_read_buf.getFreeSize();
        if (free_buf_size < NETWORK_MAX_SIZE)
            m_read_buf.extend(NETWORK_MAX_SIZE);

        int ret = netlib_recv(m_handle, m_read_buf.getCurrWritePos(), NETWORK_MAX_SIZE);
        if (ret <= 0)
            break;
        m_read_buf.incrWriteOffest(ret);
    }


    youliao::pdu::BasePdu *basePdu = nullptr;

    while ( (basePdu = youliao::pdu::BasePdu::readPduFromBuffer(m_read_buf)) != nullptr)
    {
        //读pdu,
        handlePdu(basePdu);
    }
}

void ProxyConn::handlePdu(BasePdu *pdu) {
    auto cid = pdu->getCID();

    if (cid == base::CID_OTHER_HEARTBEAT) {
        //delete pdu;
        return;
    }

    DBProxyTask *dbProxyTask = new DBProxyTask(pdu, m_handle, HandlerMap::instance()->getHandler(cid));

    g_thread_pool.addTask(dbProxyTask);
}