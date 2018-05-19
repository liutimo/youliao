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

//bool LoginModel::doLogout(uint32_t userId)
//{
//    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");
//
//    if (conn != nullptr)
//    {
//        auto ret = conn->hdel("user_map", to_string(userId));
//        if (ret == 1)
//
//            log("用户%d注销登录!", userId);
//        else
//            log("用户%d注销登录失败!", userId);
//    }
//    CacheManager::instance()->releaseCacheConn(conn);
//}