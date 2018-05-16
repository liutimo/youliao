//
// Created by liuzheng on 18-5-13.
//

#include <network/ServerInfo.h>
#include <pdu/protobuf/youliao.server.pb.h>
#include <pdu/protobuf/youliao.file.pb.h>
#include "network/netlib.h"
#include "ClientConn.h"
#include "FileServerConn.h"
#include "util/util.h"
#include "User.h"

static BaseConnMap_t g_file_server_conn_map;

static serv_info_t* g_file_server_list;
static uint32_t     g_file_server_count;

void init_file_server_conn(serv_info_t *server_list, uint32_t server_count)
{
    g_file_server_list = server_list;
    g_file_server_count = server_count;

    serv_init<FileServerConn>(g_file_server_list, g_file_server_count);
}

bool is_file_server_availabel()
{
    FileServerConn *conn = nullptr;

    for (uint32_t i = 0; i < g_file_server_count; ++i)
    {
        conn = (FileServerConn*)g_file_server_list[i].server_conn;
        if (conn && conn->isOpen())
            return true;
    }

    return false;
}

FileServerConn *get_random_file_server_conn()
{
    FileServerConn *conn = nullptr;

    return (FileServerConn*)g_file_server_list[0].server_conn;
    if (0 == g_file_server_count)
    {
        return conn;
    }

    int32_t randomNum = rand() % g_file_server_count;
    conn = (FileServerConn*)g_file_server_list[randomNum].server_conn;
    if (conn != nullptr && conn->isOpen())
        return conn;
    else
    {
        for (uint32_t i = 0; i < g_file_server_count; ++i)
        {
            int j = (randomNum + i + 1) % g_file_server_count;
            conn = (FileServerConn*)g_file_server_list[j].server_conn;
            if (conn && conn->isOpen())
            {
                return conn;
            }
        }
    }
    return nullptr;
}

FileServerConn::FileServerConn() : m_open(false), m_server_index(0)
{

}

FileServerConn::~FileServerConn()
{

}

void FileServerConn::connect(const std::string &serverIp, uint16_t serverPort, uint32_t serverIndex)
{
    log("连接文件服务器 %s:%d", serverIp.c_str(), serverPort);
    m_server_index = serverIndex;
    m_handle = netlib_connect(serverIp, serverPort, baseconn_callback, (void*)&g_file_server_conn_map);

    if (m_handle != NETWORK_ERROR)
    {
        g_file_server_conn_map.insert(std::make_pair(m_handle, this));


        log("连接消息服务器成功");
        m_open = true;
        m_connect_time = get_tick_count();
        g_file_server_list[m_server_index].reconnect_cnt = 2;

        //成功连接,发送pdu获取ip地址信息
        server::FileServerIPRequest request;
        BasePdu basePdu;
        basePdu.setSID(base::SID_SERVER);
        basePdu.setCID(base::CID_SERVER_FILE_SERVER_IP_REQUEST);
        basePdu.writeMessage(&request);
        sendBasePdu(&basePdu);
    }

}

void FileServerConn::close()
{
    serv_reset<FileServerConn>(g_file_server_list, g_file_server_count, m_server_index);
    m_open = false;
    if (m_handle != NETWORK_ERROR)
    {
        netlib_close(m_handle);
        g_file_server_conn_map.erase(m_handle);
    }
}



void FileServerConn::onClose()
{
    close();
}

void FileServerConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID())
    {
        case base::CID_SERVER_FILE_SERVER_IP_RESPONE:
            _HandleGetFileServerIpRespone(pdu);
            break;
        case base::CID_SERVER_FILE_TRANSFER_RESPONE:
            _HandleFileMsgTransferRespone(pdu);
            break;
        default:
            log("位置的CID:%d", pdu->getCID());
            break;
    }
}

void FileServerConn::_HandleGetFileServerIpRespone(BasePdu *basePdu)
{
    server::FileServerIPRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t ipAddressCount = respone.ip_addr_list_size();

    for (uint32_t i = 0; i < ipAddressCount; ++i)
    {
        base::IpAddress address = respone.ip_addr_list(i);
        m_ip_list.push_back(address);
    }
}


void FileServerConn::_HandleFileMsgTransferRespone(BasePdu *basePdu)
{
    server::FileTransferRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t resultCode = respone.result_code();
    uint32_t fromId     = respone.from_user_id();
    uint32_t toId       = respone.to_user_id();
    std::string fileName= respone.file_name();
    uint32_t fileSize   = respone.file_size();
    std::string taskId  = respone.task_id();
    base::TransferFileType transMode  = respone.trans_mode();

    log("收到文件服务器文件传输响应：result: %u, from_user_id: %u, to_user_id: %u, file_name: %s, \
        task_id: %s, trans_mode: %u. ", resultCode, fromId, toId,
        fileName.c_str(), taskId.c_str(), transMode);


    const std::list<base::IpAddress> *ipAddressList = getFileServerIPList();

    file::SendFileRespone fileRespone;
    fileRespone.set_result_code(resultCode);
    fileRespone.set_from_user_id(fromId);
    fileRespone.set_to_user_id(toId);
    fileRespone.set_file_name(fileName);
    fileRespone.set_task_id(taskId);
    fileRespone.set_trans_mode(transMode);

    for (auto iter = ipAddressList->begin(); iter != ipAddressList->end(); ++iter)
    {
        auto addr = fileRespone.add_ip_addr_list();
        addr->set_ip(iter->ip());
        addr->set_port(iter->port());
    }

    auto user = UserManager::instance()->getUser(fromId);
    if (user)
    {
        auto conn = user->getConn();
        if (conn)
        {
            sendMessage(conn, fileRespone, base::SID_FILE, base::CID_FILE_RESPONE);
        }
    }

    //创建成功
    //通知接受者
    if (resultCode == 0)
    {
        file::FileNotify fileNotify;
        fileNotify.set_from_user_id(fromId);
        fileNotify.set_to_user_id(toId);
        fileNotify.set_file_name(fileName);
        fileNotify.set_file_size(fileSize);
        fileNotify.set_trans_mode(transMode);
        fileNotify.set_offline_ready(0);
        fileNotify.set_task_id(taskId);

        for (auto iter = ipAddressList->begin(); iter != ipAddressList->end(); ++iter)
        {
            auto addr = fileNotify.add_ip_addr_list();
            addr->set_ip(iter->ip());
            addr->set_port(iter->port());
        }

        auto toUser = UserManager::instance()->getUser(toId);
        if (toUser)
        {
            auto conn = toUser->getConn();
            if (conn)
            {
                sendMessage(conn, fileNotify, base::SID_FILE, base::CID_FILE_NOTIFY);
            }
        }
        else
        {
            //发送到路由服务器
        }
    }
}