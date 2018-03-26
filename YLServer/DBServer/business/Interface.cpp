//
// Created by liuzheng on 18-3-25.
//

#include "Interface.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "LoginModel.h"


namespace DB_INTERFACE
{
    void login(BasePdu *basePdu, uint32_t conn_uuid)
    {
        server::ValidateRequest validateRequest;
        validateRequest.ParseFromString(basePdu->getMessage());

        server::ValidateRespone validateRespone;
        validateRespone.set_attach_data(validateRequest.attach_data());

        LoginModel loginModel;

        base::UserInfo *userInfo = new base::UserInfo;
        if (loginModel.doLogin(validateRequest.user_name(), validateRequest.user_pwd(), *userInfo))
        {
            validateRespone.set_user_name(validateRequest.user_name());
            validateRespone.set_result_code(0);
            validateRespone.set_result_string("登录成功");
            validateRespone.set_allocated_user_info(userInfo);
        }
        else
        {
            validateRespone.set_result_code(1);
            validateRespone.set_result_string("登录失败， 用户名或密码错误！");
        }

        BasePdu *pdu1 = new BasePdu;
        pdu1->setSID(base::SID_OTHER);
        pdu1->setCID(base::CID_SERVER_VALIDATE_RESPONE);
        pdu1->writeMessage(&validateRespone);

//        sendBasePdu(pdu1);
        //add to thread pool
    }
}
