//
// Created by liuzheng on 18-6-5.
//

#ifndef DBSERVER_OTHERMODEL_H
#define DBSERVER_OTHERMODEL_H

#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.file.pb.h"

using namespace youliao::pdu;

class OtherModel {
public:
    static OtherModel* instance();
    ~OtherModel();

    bool modifyUserInformation(uint32_t userId, const base::UserInfo &userInfo);
    bool modifyUserIcon(uint32_t userId, const std::string &url);

    bool saveOfflineFile(uint32_t senderId, uint32_t receiverId, const std::string &task_id);

    bool getOfflineFile(uint32_t receiverId, file::GetOfflineFileRespone &respone);
private:
    OtherModel();
    static OtherModel* m_instance;

};


#endif //DBSERVER_OTHERMODEL_H
