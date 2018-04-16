//
// Created by liuzheng on 18-4-15.
//

#ifndef HTTPSERVER_CONNECTION_H
#define HTTPSERVER_CONNECTION_H

#include <array>
#include <memory>
#include <asio.hpp>
#include "reply.h"
#include "request.h"
#include "request_parser.h"
#include "request_handler.h"

namespace http
{
    namespace server
    {
        class connection_manager;

        class connection : public std::enable_shared_from_this<connection>
        {
        public:
            connection(const connection&) = delete;
            connection& operator=(const connection&) = delete;

            explicit connection(asio::ip::tcp::socket socket, connection_manager &manager, request_handler &handler);

            //开始连接的第一个异步操作
            void start();

            //停止和当前连接所有相关联的异步操作
            void stop();

        private:
            void do_read();

            void do_write();



            asio::ip::tcp::socket socket_;

            connection_manager &connection_manager_;

            request_handler &request_handler_;

            std::array<char, 8192> buffer_;

            request request_;

            request_parser request_parser_;

            reply reply_;
        };

        typedef std::shared_ptr<connection> connection_ptr;
    }
}

#endif //HTTPSERVER_CONNECTION_H
