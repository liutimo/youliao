//
// Created by liuzheng on 18-4-15.
//
#include <iostream>
#include "connection.h"

#include "connection_manager.h"

namespace http
{
    namespace server
    {
        connection::connection(asio::ip::tcp::socket socket, connection_manager &manager, request_handler &handler)
        : socket_(std::move(socket)),
          connection_manager_(manager),
          request_handler_(handler)
        {
        }


        void connection::start()
        {
            do_read();
        }

        void connection::stop()
        {
            socket_.close();
        }

        void connection::do_read()
        {
            auto self(shared_from_this());
            socket_.async_read_some(asio::buffer(buffer_),
                [this, self](std::error_code ec, std::size_t bytes_transferred)
                {
                    if (!ec)
                    {
                        std::cout << "收到来自客户端的请求\n" << buffer_.data() << std::endl;
                        request_parser::result_type result;
                        std::tie(result, std::ignore) = request_parser_.parse(
                          request_, buffer_.data(), buffer_.data() + bytes_transferred);

                        if (result == request_parser::good)
                        {
                            request_handler_.handle_request(request_, reply_, socket_);

                            do_write();
                        }
                        else if (result == request_parser::bad)
                        {
                            reply_ = reply::stock_reply(reply::bad_request);
                            do_write();
                        }
                        else
                        {
                            do_read();
                        }
                    }
                    else if (ec != asio::error::operation_aborted)
                    {
                        connection_manager_.stop(shared_from_this());
                    }

                }
            );
        }

        void connection::do_write()
        {
            auto self(shared_from_this());
            asio::async_write(socket_, reply_.to_buffer(), [this, self](std::error_code ec, std::size_t)
            {
                if (!ec)
                {
                    asio::error_code ignored_ec;
                    socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
                }

                if (ec != asio::error::operation_aborted)
                {
                    connection_manager_.stop(shared_from_this());
                }
            });
        }



    }
}
