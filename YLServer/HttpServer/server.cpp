//
// Created by liuzheng on 18-4-15.
//

#include "server.h"

namespace http
{
    namespace server
    {
        server::server(const std::string &address, const std::string &port, const std::string &doc_root)
        : io_service_(),
          signals_(io_service_),
          acceptor_(io_service_),
          connection_manager_(),
          socket_(io_service_),
          request_handler_(doc_root)
        {
            //注册信号处理
            signals_.add(SIGINT);
            signals_.add(SIGTERM);
#if defined(SIGQUIT)
            signals_.add(SIGQUIT);
#endif
            do_await_stop();

            asio::ip::tcp::resolver resolver(io_service_);
            asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
            acceptor_.open(endpoint.protocol());
            acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
            acceptor_.bind(endpoint);
            acceptor_.listen();

            do_accept();
        }

        void server::run()
        {
            io_service_.run();
        }

        void server::do_accept()
        {
            acceptor_.async_accept(socket_, [this](std::error_code ec)
            {
                if (!acceptor_.is_open())
                {
                    return;
                }

                if (!ec)
                {
                    connection_manager_.start(std::make_shared<connection>(
                            std::move(socket_), connection_manager_, request_handler_));
                }

                do_accept();
            });
        }

        void server::do_await_stop()
        {
            signals_.async_wait(
                    [this](std::error_code, int signo)
                    {
                        acceptor_.close();
                        connection_manager_.stopAll();
                    }
            );
        }

    }
}
