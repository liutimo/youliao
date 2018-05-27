//
// Created by liuzheng on 18-5-22.
//

#ifndef BASEUTIL_HTTPCLIENT_H
#define BASEUTIL_HTTPCLIENT_H

#include <string>
#include <curl/curl.h>

typedef struct AudioMsgInfo{
    uint32_t    audioId;
    uint32_t    fileSize;
    uint32_t    data_len;
    u_char *    data;
    std::string      path;

} AudioMsgInfo_t;

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

public:
    CURLcode post(const std::string &url, const std::string &post, std::string &respone);
    CURLcode get(const std::string &url, std::string &respone);

    std::string uploadByteFile(const std::string &url, void *data, int dataLen);
    bool downloadByteFile(const std::string &url, AudioMsgInfo *audioMsgInfo);
};


#endif //BASEUTIL_HTTPCLIENT_H
