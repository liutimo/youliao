//
// Created by liuzheng on 18-5-15.
//

#include "ClientConn.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.file.pb.h"
#include "TransferTaskManager.h"
#include "network/netlib.h"
#include "util/util.h"

static BaseConnMap_t g_client_conn_map;

void initClientConn()
{

}

void clientConnCallBack(callback_data data, uint8_t msg, int handle, void*)
{
    if (msg == NETWORK_CONNECT)
    {
        ClientConn *clientConn = new ClientConn;
        clientConn->onConnect(handle);
    }
}


ClientConn::ClientConn()
{
    m_auth = false;
    m_user_id = 0;
    m_transfer_task = nullptr;
}

void ClientConn::close()
{
    if (m_transfer_task)
    {
        if (m_transfer_task->getTransferMode() == base::FILE_TYPE_ONLINE)
        {
            m_transfer_task->setState(Invalid);
        }
        else
        {
            if (m_transfer_task->getState() >= UploadEnd)
            {
                m_transfer_task->setState(WaitingDownload);
            }
        }

        m_transfer_task->setConnByUserID(m_user_id, nullptr);
        TransferTaskManager::instance()->deleteTransferTaskByConnClose(m_transfer_task->getTaskId());
        m_transfer_task = nullptr;
    }
    m_auth = false;

    if (m_handle != NETWORK_ERROR)
    {
        netlib_close(m_handle);
        g_client_conn_map.erase(m_handle);
    }
}

void ClientConn::onConnect(net_handle_t handle)
{
    m_handle = handle;
    g_client_conn_map.insert(std::make_pair(handle, this));

    netlib_option(handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)&g_client_conn_map);

    uint32_t socket_buf_size = (128 * 1024);
    netlib_option(handle, NETLIB_OPT_SET_SEND_BUF_SIZE, &socket_buf_size);
    netlib_option(handle, NETLIB_OPT_SET_RECV_BUF_SIZE, &socket_buf_size);
}

void ClientConn::onClose()
{
    close();
}

void ClientConn::onTimer(uint64_t curr_tick)
{

}

void ClientConn::handlePdu(BasePdu *basePdu)
{
    switch (basePdu->getCID())
    {
        case base::CID_FILE_LOGIN_REQUEST:
            _HandleClientLoginRequest(basePdu);
            break;
        case base::CID_FILE_GET_BLOCK_REQUEST:
            _HandleClientGetFileBlockRequest(basePdu);
            break;
        case base::CID_FILE_GET_BLOCK_RESPONE:
            _HandleClientGetFileBlockRespone(basePdu);
            break;
        case base::CID_FILE_STATE:
            _HandleCLientFileStates(basePdu);
            break;
        default:
            break;
    }
}


void ClientConn::_HandleClientLoginRequest(BasePdu *basePdu)
{
    file::LoginFileServerRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId     = request.user_id();
    std::string taskId  = request.task_id();
    base::ClientFileRole  role = request.client_role();

    log("客户端登录, userId: %d, taskId:%s, clientRole:%d", userId, taskId.c_str(), role);

    BaseTransferTask *transferTask = nullptr;
    bool rv = false;
    do
    {
        transferTask = TransferTaskManager::instance()->findByTaskId(taskId);
        if (transferTask == nullptr)
        {
            if (role == base::CLIENT_OFFLINE_DOWNLOAD)
            {
                //离线文件不存在
                transferTask = TransferTaskManager::instance()->newTransferTask(taskId, userId);
                if (transferTask == nullptr)
                    break;
            }
            else
            {
                log("无法找到任务。taskId：%d, userId:%d, clientRole:%d", taskId.c_str(), userId, role);
                break;
            }

        }

        //更改任务状态
        rv = transferTask->changePullState(userId, role);
        if (!rv)
        {
            log("更改任务状态失败！");
            break;
        }

        m_auth = true;
        m_transfer_task = transferTask;
        m_user_id = userId;

        transferTask->setConnByUserID(userId, this);
        rv = true;
    }while (0);

    file::LoginFileServerRespone respone;
    respone.set_result_code(rv ? 0 : 1);
    respone.set_task_id(taskId);

    BasePdu basePdu1;
    basePdu1.setSID(base::SID_FILE);
    basePdu1.setCID(base::CID_FILE_LOGIN_RESPONE);
    basePdu1.writeMessage(&respone);
    sendBasePdu(&basePdu1);

    if (rv)
    {
        if(transferTask->getTransferMode() == base::FILE_TYPE_ONLINE)
        {
            if(transferTask->getState() == WaittingTransfer)
            {
                BaseConn *conn = transferTask->getToConn();
                if (conn)
                {
                    //通知接收方，发送方准备好了
                    _StatesNotify(base::CLIENT_FILE_PEER_READY, taskId, transferTask->getFromUserId(), conn);
                }
                else
                {
                    log("to conn close");
                    close();
                }
            }
        }
        else if (transferTask->getState() == WaitingUpload)
        {
            OfflineTransferTask *offlineTransferTask = reinterpret_cast<OfflineTransferTask*>(transferTask);

            file::GetFileBlockRequest request1;
            request1.set_task_id(taskId);
            request1.set_user_id(userId);
            request1.set_trans_mode(base::FILE_TYPE_OFFLINE);
            request1.set_offest(0);
            request1.set_data_size(offlineTransferTask->getNextSegmentBlockSize());

            BasePdu basePdu2;
            basePdu2.setSID(base::SID_FILE);
            basePdu2.setCID(base::CID_FILE_GET_BLOCK_REQUEST);
            basePdu2.writeMessage(&request1);
            sendBasePdu(&basePdu2);
        }
    }
    else
    {
        close();
    }

}


void ClientConn::_HandleClientGetFileBlockRequest(BasePdu *basePdu)
{
    //校验任务是否已经建立
    if (!m_auth || !m_transfer_task)
        return;

    file::GetFileBlockRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId     = request.user_id();
    std::string taskId  = request.task_id();
    uint32_t offest     = request.offest();
    uint32_t dataSize   = request.data_size();
    base::TransferFileType mode = request.trans_mode();

    log("接收端同意接收文件, userId:%d, taskId:%s, offest:%d, dataSize:%d", userId, taskId.c_str(), offest, dataSize);

    file::GetFileBlockRespone respone;
    respone.set_result_code(1);
    respone.set_task_id(taskId);
    respone.set_user_id(userId);
    respone.set_offest(offest);
    respone.set_file_data("");

    int rv = -1;

    do
    {
        if (userId != m_user_id)
            break;

        if (m_transfer_task->getTaskId() != taskId)
            break;

        if (!m_transfer_task->checkToUserID(userId))
            break;

        rv = 0;

//
        if (rv == -1)
            break;

        respone.set_result_code(0);

        if (m_transfer_task->getTransferMode() == base::FILE_TYPE_ONLINE)
        {
            //在线传输。将请求转发到客户端
            BaseConn *conn = m_transfer_task->getOpponentConn(userId);
            if (conn)
                sendMessage(conn, request, base::SID_FILE, base::CID_FILE_GET_BLOCK_REQUEST);
        }
        else
        {
            BasePdu basePdu1;
            basePdu1.setSID(base::SID_FILE);
            basePdu1.setCID(base::CID_FILE_GET_BLOCK_RESPONE);
            basePdu1.writeMessage(&respone);
//            if (rv == 1)
//            {
//                _StatesNotify(base::CLIENT_FILE_DONE, taskId, m_transfer_task->getFromUserId(), this);
//            }
        }

    }while (0);


    if (rv != 0)
        close();
}


void ClientConn::_HandleClientGetFileBlockRespone(BasePdu *basePdu)
{
    if (!m_auth || !m_transfer_task)
        return;

    file::GetFileBlockRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t userId     = respone.user_id();
    std::string taskId  = respone.task_id();
    uint32_t offest     = respone.offest();
    uint32_t dataSize   = (uint32_t)respone.file_data().length();
    const char *data    = respone.file_data().data();

    int rv = -1;
    do
    {
         if (userId != m_user_id)
             break;

         if (m_transfer_task->getTaskId() != taskId)
             break;

         rv = m_transfer_task->doRecvData(userId, offest, data, dataSize);

         if (rv == -1)
             break;

         if (m_transfer_task->getTransferMode() == base::FILE_TYPE_ONLINE)
         {
             //在线，直接转发
             BaseConn *conn = m_transfer_task->getToConn();
             if (conn)
                sendMessage(conn, respone, base::SID_FILE, base::CID_FILE_GET_BLOCK_RESPONE);

         }
         else
         {
             //离线文件
             //发送pull请求到客户端，获取下一次的数据
             if (rv == 1)
             {
                 _StatesNotify(base::CLIENT_FILE_DONE, taskId, userId, this);
             }
             else
             {
                OfflineTransferTask* offlineTransferTask = reinterpret_cast<OfflineTransferTask*>(m_transfer_task);
                file::GetFileBlockRequest request;
                request.set_task_id(taskId);
                request.set_user_id(userId);
                request.set_trans_mode(static_cast<base::TransferFileType>(offlineTransferTask->getTransferMode()));
                request.set_offest(offlineTransferTask->getNextOffest());
                request.set_data_size(offlineTransferTask->getNextSegmentBlockSize());

                BasePdu basePdu1;
                basePdu1.setSID(base::SID_FILE);
                basePdu1.setCID(base::CID_FILE_GET_BLOCK_REQUEST);
                basePdu1.writeMessage(&request);
                sendBasePdu(&basePdu1);
             }


         }


    }while (0);


    //-1 出错， 0 正常， 1 离线传输完成
    if (rv != 0)
    {
        close();
    }

}


void ClientConn::_HandleCLientFileStates(BasePdu *basePdu)
{
    if (!m_auth || !m_transfer_task)
        return;

    file::ClientFileState fileState;
    fileState.ParseFromString(basePdu->getMessage());

    std::string taskId  = fileState.task_id();
    uint32_t userId     = fileState.user_id();
    uint32_t fileStat   = fileState.state();

    log("Recv FileState, user_id=%d, task_id=%s, file_stat=%d", userId, taskId.c_str(), fileStat);

    bool rv = false;

    do
    {
        if (userId != m_user_id)
            break;

        if (m_transfer_task->getTaskId() != taskId)
            break;

        switch (fileStat)
        {
            case base::CLIENT_FILE_CANCEL:
            case base::CLIENT_FILE_DONE:
            case base::CLIENT_FILE_REFUSE:
            {
                BaseConn *conn = m_transfer_task->getOpponentConn(userId);
                if (conn)
                {
                    sendMessage(conn, fileState, base::SID_FILE, base::CID_FILE_STATE);
                }
                rv = true;
                break;
            }
            default:
                break;
        }

    }while (0);

    //关闭连接
    close();


}



int ClientConn::_StatesNotify(int state, const std::string& task_id, uint32_t user_id, BaseConn* conn)
{
    ClientConn *clientConn = reinterpret_cast<ClientConn*>(conn);

    file::ClientFileState fileState;
    fileState.set_state(static_cast<base::ClientFileState>(state));
    fileState.set_task_id(task_id);
    fileState.set_user_id(user_id);

    sendMessage(clientConn, fileState, base::SID_FILE, base::CID_FILE_STATE);

    log("通知用户%d, taskId:%s, state:%d", user_id, task_id.c_str(), state);
    return  0;
}