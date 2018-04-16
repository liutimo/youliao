//
// Created by liuzheng on 18-4-15.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H

#include <asio.hpp>
#include <string>
#include "connection.h"
#include "connection_manager.h"
#include "request_handler.h"

namespace http
{
    namespace server
    {
        class server
        {
        public:
            server(const server&) = delete;
            server& operator=(const server&) = delete;

            explicit server(const std::string &address, const std::string &port, const std::string &doc_root);

            void run();

        private:
            //异步accept操作
            void do_accept();

            //等待一个请求停止服务器
            void do_await_stop();

            asio::io_service io_service_;

            //处理终止
            asio::signal_set signals_;

            asio::ip::tcp::acceptor acceptor_;

            connection_manager connection_manager_;

            asio::ip::tcp::socket socket_;

            request_handler request_handler_;
        };
    }
}

#endif //HTTPSERVER_SERVER_H
