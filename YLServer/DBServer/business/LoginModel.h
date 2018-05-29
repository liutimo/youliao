/*================================================================
*   
*   文件名称: LoginModel.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月10日　 上午11:06
*   描   述:
*
================================================================*/


#ifndef DBSERVER_LOGINMODEL_H
#define DBSERVER_LOGINMODEL_H

#include <string>
#include "pdu/protobuf/youliao.base.pb.h"
using namespace youliao::pdu;
class LoginModel {
public:
    static LoginModel* instance();
    ~LoginModel();

    bool doLogin(const std::string &str_name, const std::string &str_pass, base::UserInfo &userInfo);
//    bool doLogout(uint32_t userId);
    bool getUserInfo(uint32_t userId, base::UserInfo &userInfo);

    //注册
    bool doRegister(const std::string &nickname, const std::string &password, const std::string &head, uint32_t& user_account);
private:
    void getMaxUserAccount(uint32_t &account);
    LoginModel();
    static LoginModel* m_instance;
};


#endif //DBSERVER_LOGINMODEL_H
