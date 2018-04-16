//
// Created by liuzheng on 18-4-15.
//

#ifndef HTTPSERVER_REPLY_H
#define HTTPSERVER_REPLY_H

#include <string>
#include <vector>
#include <asio.hpp>
#include "header.h"

namespace http
{
    namespace server
    {
        struct reply
        {
            //see https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
            enum status_type
            {
                ok = 200,
                created = 201,
                accepted = 202,
                no_content = 204,
                multiple_choices = 300,
                moved_permanently = 301,
                moved_temporarily = 302,
                not_modified = 304,
                bad_request = 400,
                unauthorized = 401,
                forbidden = 403,
                not_found = 404,
                internal_server_error = 500,
                not_implemented = 501,
                bad_gateway = 502,
                service_unavailable = 503
            } status;


            ///reply中包含的header
            std::vector<header> headers;

            ///reply中的主文本
            std::string content;

            ///将reply转换成buffer。这个buffer没有底层内存块，需要保证在发送完数据前reply对象有效、
            std::vector<asio::const_buffer> to_buffer();

            static reply stock_reply(status_type status);

        };


    }

}



#endif //HTTPSERVER_REPLY_H
