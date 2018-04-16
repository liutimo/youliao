//
// Created by liuzheng on 18-4-15.
//

#ifndef HTTPSERVER_HEADER_H
#define HTTPSERVER_HEADER_H

#include <string>

namespace http {
    namespace server {
        struct header
        {
            std::string name;
            std::string value;
        };
    }

}


#endif //HTTPSERVER_HEADER_H
