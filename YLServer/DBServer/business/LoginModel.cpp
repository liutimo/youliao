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
LoginModel::LoginModel()
{

}

LoginModel::~LoginModel()
{

}

bool LoginModel::doLogin(const std::string &str_name, const std::string &str_pass)
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
                ret = true;
        }

        delete resultSet;
    }

    dbManager->releaseConnection(dbConn);
    return ret;
}
