/*================================================================
*   
*   文件名称: LoginModel.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月10日　 上午11:06
*   描   述:
*
================================================================*/


#include "LoginModel.h"
#include "../DBPool.h"
#include "util/util.h"

LoginModel* LoginModel::m_instance = nullptr;

LoginModel* LoginModel::instance()
{
    if (m_instance == nullptr)
        m_instance = new LoginModel;
    return m_instance;
}


LoginModel::LoginModel()
{

}

LoginModel::~LoginModel()
{

}

bool LoginModel::getUserInfo(uint32_t userId, base::UserInfo &userInfo)
{
    bool ret = false;
    DBConn *dbConn = DBManager::instance()->getConnection();
    if (dbConn)
    {

        std::string str_sql = "select * from yl_user where user_id=" + std::to_string(userId);
        printSql2Log(str_sql.c_str());
        ResultSet *resultSet = dbConn->query(str_sql);

        if (resultSet && resultSet->next())
        {
                ret = true;
                userInfo.set_user_account((uint32_t)resultSet->getInt("user_account"));
                userInfo.set_user_sex((uint32_t)resultSet->getInt("user_sex"));
                userInfo.set_user_sign_info(resultSet->getString("user_sign_info"));
                userInfo.set_user_email(resultSet->getString("user_email"));
                userInfo.set_user_header_url(resultSet->getString("user_header"));
                userInfo.set_user_phone(resultSet->getString("user_phone"));
                userInfo.set_user_nick(resultSet->getString("user_nickname"));
                userInfo.set_user_id((uint32_t)resultSet->getInt("user_id"));
            }
        }

    DBManager::instance()->releaseConnection(dbConn);
    return ret;
}


bool LoginModel::doLogin(const std::string &str_name, const std::string &str_pass, base::UserInfo &userInfo)
{
    bool ret = false;
    DBManager *dbManager = DBManager::instance();
    DBConn *dbConn = dbManager->getConnection();

    if (dbConn)
    {
        std::string str_sql = "select * from yl_user where user_account='" + str_name + "'";
        printSql2Log(str_sql.c_str());
        ResultSet *resultSet = dbConn->query(str_sql);

        std::string password;

        if (resultSet && resultSet->next())
        {
            password = resultSet->getString("user_password");

            if (str_pass == password)
            {
                ret = true;
                userInfo.set_user_account(resultSet->getInt("user_account"));
                userInfo.set_user_sex(resultSet->getInt("user_sex"));
                userInfo.set_user_sign_info(resultSet->getString("user_sign_info"));
                userInfo.set_user_email(resultSet->getString("user_email"));
                userInfo.set_user_header_url(resultSet->getString("user_header"));
                userInfo.set_user_phone(resultSet->getString("user_phone"));
                userInfo.set_user_nick(resultSet->getString("user_nickname"));
                userInfo.set_user_id(resultSet->getInt("user_id"));
            }
        }

        delete resultSet;
    }

    dbManager->releaseConnection(dbConn);
    return ret;
}


bool LoginModel::doRegister(const std::string &nickname, const std::string &password
        , const std::string &head, uint32_t& user_account)
{
    bool ret = false;
    //[1] 获得最后一条user_account
    uint32_t  account = 0;
    getMaxUserAccount(account);

    if (account == 0)
    {
        user_account = 123456;
    }
    else
    {
        user_account = account + 1;
    }

    uint32_t created = (uint32_t )time(nullptr);

    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string sql = "INSERT INTO yl_user(user_account, user_password, user_nickname,"
                          " user_header, user_created, user_updated) "
                          "VALUES(?, ?, ?, ?, ?, ?)";
        printSql2Log(sql.c_str());

        PrepareStatement *pstmt = new PrepareStatement;
        if (pstmt->init(conn->getMysql(), sql))
        {
            uint32_t index = 0;
            pstmt->setParam(index++, user_account);
            pstmt->setParam(index++, password);
            pstmt->setParam(index++, nickname);
            if (head.empty())
                pstmt->setParam(index++, "www.liutimo.cn/images/default.jpeg");
            else
                pstmt->setParam(index++, "www.liutimo.cn/images/" + head);
            pstmt->setParam(index++, created);
            pstmt->setParam(index++, created);

            ret = pstmt->executeUpdate();
        }

        delete pstmt;
    }

    DBManager::instance()->releaseConnection(conn);

    return ret;
}


void LoginModel::getMaxUserAccount(uint32_t &account)
{

    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string sql = "SELECT user_account FROM yl_user ORDER BY user_id DESC  LIMIT 1 ;";
        printSql2Log(sql.c_str());
        ResultSet *resultSet = conn->query(sql);

        if (resultSet && resultSet->next())
        {
            account = (uint32_t)resultSet->getInt("user_account");
        }

        delete resultSet;
    }

    DBManager::instance()->releaseConnection(conn);
}
