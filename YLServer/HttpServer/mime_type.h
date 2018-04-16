//
// Created by liuzheng on 18-4-15.
//

#ifndef HTTPSERVER_MIME_TYPE_H
#define HTTPSERVER_MIME_TYPE_H

#include <string>

namespace http
{
    namespace server
    {
        namespace mime_types
        {
            std::string extension_to_type(const std::string &extension);
        }
    }
}



#endif //HTTPSERVER_MIME_TYPE_H
