//
// Created by liuzheng on 18-4-15.
//

#ifndef HTTPSERVER_REQUEST_HANDLER_H
#define HTTPSERVER_REQUEST_HANDLER_H

#include <string>
#include <asio/ip/tcp.hpp>

#define CONTENT_DISPOSITION         "Content-Disposition:"
#define HTTP_END_MARK               "\r\n\r\n"

namespace http
{
    namespace server
    {
        struct reply;
        struct request;


        const char*  memfind(const char *src_str,size_t src_len, const char *sub_str, size_t sub_len, bool flag = true);


        class request_handler
        {
        public:
            request_handler(const request_handler&) = delete;
            request_handler&operator=(const request_handler&) = delete;

            explicit request_handler(const std::string &doc_root);

            void handle_request(const request& req, reply &rep, asio::ip::tcp::socket &sock);

        private:
            std::string doc_root_;

            static bool url_decode(const std::string &in, std::string &out);
        };

    }
}


#endif //HTTPSERVER_REQUEST_HANDLER_H
