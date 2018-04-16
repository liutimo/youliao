//
// Created by liuzheng on 18-4-15.
//

#ifndef HTTPSERVER_REQUEST_H
#define HTTPSERVER_REQUEST_H

#include <string>
#include <vector>
#include "header.h"
namespace http
{
    namespace server
    {
        struct request
        {
            std::string method;
            std::string uri;
            int http_version_major;
            int http_version_minor;
            std::vector<header> headers;
        };

    }
}


#endif //HTTPSERVER_REQUEST_H
