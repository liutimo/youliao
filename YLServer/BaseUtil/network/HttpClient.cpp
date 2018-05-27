//
// Created by liuzheng on 18-5-22.
//

#include "HttpClient.h"
#include <cstring>
using namespace std;


size_t writeDataString(void *ptr, size_t size, size_t nmemb, void *userp)
{
    size_t len = size * nmemb;
    string* response = (string *)userp;

    response->append((char*)ptr, len);

    return len;
}


size_t writeDataBinary(void *ptr, size_t size, size_t nmemb, AudioMsgInfo* pAudio)
{
    size_t nLen = size * nmemb;
    if(pAudio->data_len + nLen <= pAudio->fileSize + 4)
    {
        memcpy(pAudio->data + pAudio->data_len, ptr, nLen);
        pAudio->data_len += nLen;
    }
    return nLen;
}



HttpClient::HttpClient()
{

}

HttpClient::~HttpClient()
{

}

static size_t onWriteData(void *buffer, size_t size, size_t nmemb, void* lpVoid)
{
    string *str = dynamic_cast<string*>((string*)lpVoid);
    if (nullptr == str || nullptr == buffer)
        return -1;

    char *data = (char*)buffer;
    str->append(data, size * nmemb);
    return nmemb;
}


CURLcode HttpClient::post(const std::string &url, const std::string &post, std::string &respone)
{
    CURLcode res;
    CURL *curl = curl_easy_init();
    if (nullptr == curl)
        return CURLE_FAILED_INIT;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, nullptr);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&respone);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

CURLcode HttpClient::get(const std::string &url, std::string &respone)
{
    CURLcode res;
    CURL *curl = curl_easy_init();
    if (nullptr == curl)
        return CURLE_FAILED_INIT;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&respone);
    /**
     * 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
     * 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。
     */
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return res;
}

std::string HttpClient::uploadByteFile(const std::string &url, void *data, int dataLen)
{
    if(url.empty())
        return "";

    CURL* curl = curl_easy_init();
    if (!curl)
        return "";
    struct curl_slist *headerlist = NULL;
    headerlist = curl_slist_append(headerlist, "Content-Type: multipart/form-data; boundary=WebKitFormBoundary8riBH6S4ZsoT69so");
    // what URL that receives this POST
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    string body = "--WebKitFormBoundary8riBH6S4ZsoT69so\r\nContent-Disposition: form-data; name=\"file\"; filename=\"1.amr\"\r\nContent-Type:image/jpg\r\n\r\n";
    body.append((char*)data, dataLen);
    string str = "\r\n--WebKitFormBoundary8riBH6S4ZsoT69so--\r\n\r\n";
    body.append(str.c_str(), str.size());

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
    string strResp;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDataString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResp);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

   //处理返回值
    return strResp;
}

bool HttpClient::downloadByteFile(const std::string &url, AudioMsgInfo *audioMsgInfo)
{
    CURL* curl = curl_easy_init();
    if (!curl)
        return false;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,2);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDataBinary);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, audioMsgInfo);
    CURLcode res = curl_easy_perform(curl);

    int retcode = 0;
    res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE , &retcode);
    if(CURLE_OK != res || retcode != 200) {
    }
    double nLen = 0;
    res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD , &nLen);
    curl_easy_cleanup(curl);
    if (nLen != audioMsgInfo->fileSize)
    {
        return false;
    }
    return true;
}