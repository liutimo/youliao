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
class LoginModel {
public:
    LoginModel();

    ~LoginModel();

    void doLogin(const std::string &str_name, const std::string &str_pass);

private:

};


#endif //DBSERVER_LOGINMODEL_H
