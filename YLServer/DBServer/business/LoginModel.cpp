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
#include "../CachePool.h"
#include "util/util.h"

LoginModel::LoginModel()
{

}

LoginModel::~LoginModel()
{

}

bool LoginModel::doLogin(const std::string &str_name, const std::string &str_pass, base::UserInfo &userInfo)
{
    bool ret = false;
    DBManager *dbManager = DBManager::instance();
    DBConn *dbConn = dbManager->getConnection();

    if (dbConn)
    {
        std::string str_sql = "select * from yl_user where user_account='" + str_name + "'";
        ResultSet *resultSet = dbConn->query(str_sql);

        std::string password;

        if (resultSet && resultSet->next())
        {
            password = resultSet->getString("user_password");

            if (str_pass == password)
            {
                ret = true;
                userInfo.set_user_sex(resultSet->getInt("user_sex"));
                userInfo.set_user_sign_info(resultSet->getString("user_sign_info"));
                userInfo.set_user_email(resultSet->getString("user_email"));
                userInfo.set_user_header_url(resultSet->getString("user_header"));
                userInfo.set_user_phone(resultSet->getString("user_phone"));
                userInfo.set_user_nick(resultSet->getString("user_nickname"));
                userInfo.set_user_id(resultSet->getInt("user_id"));
            }
        }

        //将其登录状态保存到redis
        auto conn = CacheManager::instance()->getCacheConn("OnlineUser");
        conn->sAdd("OnlineUser", resultSet->getString("user_id"));

        string value = resultSet->getString("user_id");
        log("%s", value.c_str());
        if (conn->sIsMem("OnlineUser", value))
        {
            log("%s is mem of onlineuser", value.c_str());
        } else{
            log("%s is't mem of onlineuser", value.c_str());
        }

        delete resultSet;
    }

    dbManager->releaseConnection(dbConn);
    return ret;
}
