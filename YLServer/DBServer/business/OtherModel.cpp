//
// Created by liuzheng on 18-6-5.
//

#include "OtherModel.h"
#include "../DBPool.h"
#include "util/util.h"

OtherModel* OtherModel::m_instance = nullptr;


OtherModel* OtherModel::instance()
{
    if (m_instance == nullptr)
        m_instance = new OtherModel();
    return m_instance;
}


OtherModel::OtherModel()
{

}

OtherModel::~OtherModel()
{

}


bool OtherModel::modifyUserInformation(uint32_t userId, const base::UserInfo &userInfo)
{
    bool ret = false;

    uint32_t userSex = userInfo.user_sex();
    uint32_t updateTime = (uint32_t)time(nullptr);

    DBConn *conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string updateSql = "UPDATE yl_user SET user_nickname = ?, "
                                "user_phone = ?, user_sex = ?, user_email = ?, "
                                "user_updated = ?, user_sign_info = ?, "
                                "user_birthday = ?, user_hometown = ?, "
                                "user_location = ?, user_school = ? WHERE user_id = ?";

        PrepareStatement *pstm = new PrepareStatement;
        if (pstm->init(conn->getMysql(), updateSql))
        {
            uint32_t index = 0;
            pstm->setParam(index++, userInfo.user_nick());
            pstm->setParam(index++, userInfo.user_phone());
            pstm->setParam(index++, userSex);
            pstm->setParam(index++, userInfo.user_email());
            pstm->setParam(index++, updateTime);
            pstm->setParam(index++, userInfo.user_sign_info());
            pstm->setParam(index++, userInfo.user_birthday());
            pstm->setParam(index++, userInfo.user_hometown());
            pstm->setParam(index++, userInfo.user_location());
            pstm->setParam(index++, userInfo.user_school());
            pstm->setParam(index++, userId);

            ret = pstm->executeUpdate();
        }
        delete pstm;
    }
    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool OtherModel::modifyUserIcon(uint32_t userId, const std::string &url)
{
    bool ret = false;
    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string updateSql = "UPDATE yl_user SET user_header = '" + url + "' WHERE user_id = " + std::to_string(userId);
        printSql2Log(updateSql.c_str());

        ret = conn->update(updateSql);
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool OtherModel::saveOfflineFile(uint32_t senderId, uint32_t receiverId, const std::string &task_id)
{
    bool ret = false;
    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string updateSql = "INSERT INTO youliao.yl_offline_file(sender_id, receiver_id, task_id) "
                                " VALUES( " + std::to_string(senderId) + ", "
                                                                         + std::to_string(receiverId) + ", '" + task_id + "')";

        printSql2Log(updateSql.c_str());
        ret = conn->update(updateSql);
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool OtherModel::getOfflineFile(uint32_t receiverId, file::GetOfflineFileRespone &respone)
{
    bool ret = false;
    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string updateSql = "SELECT id, sender_id, task_id FROM yl_offline_file "
                                "WHERE receiver_id = " + std::to_string(receiverId) + " AND task_status = 0";


        printSql2Log(updateSql.c_str());

        ResultSet *resultSet = conn->query(updateSql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                file::OfflineFile *offlineFile =  respone.add_offline_files();
                offlineFile->set_sender_id(resultSet->getInt("sender_id"));
                offlineFile->set_task_id(resultSet->getString("task_id"));
            }

            delete resultSet;
        }
        ret = true;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}