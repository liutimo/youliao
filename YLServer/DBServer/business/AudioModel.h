//
// Created by liuzheng on 18-5-22.
//

#ifndef DBSERVER_AUDIOMODEL_H
#define DBSERVER_AUDIOMODEL_H

#include <list>
#include <map>
#include "pdu/protobuf/youliao.base.pb.h"
#include "util/util.h"

using namespace std;
using namespace youliao::pdu;

class AudioModel {
public:
    ~AudioModel();
    static AudioModel* instance();
    void setUrl(const string& url);

    bool readAudios();

    /**
     *
     * @param fromId        发送者ID
     * @param toId          接受者ID 群组或用户
     * @param createTime    创建时间
     * @param audioData     数据
     * @param duration      时间
     * @return
     */
    int saveAudioInfo(uint32_t fromId, uint32_t toId, uint32_t createTime, const string& audioData, uint32_t duration);

private:
    AudioModel();
    bool readAudioContent(uint32_t costTime, uint32_t size, const string &path);


private:
    static AudioModel *m_instance;
    string m_url;
};


#endif //DBSERVER_AUDIOMODEL_H
