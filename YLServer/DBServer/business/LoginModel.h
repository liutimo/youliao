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
    LoginModel();

    ~LoginModel();

    bool doLogin(const std::string &str_name, const std::string &str_pass, base::UserInfo &userInfo);
    bool doLogout(uint32_t userId);
    bool getUserInfo(uint32_t userId, base::UserInfo &userInfo);
private:

};


#endif //DBSERVER_LOGINMODEL_H
