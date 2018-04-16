//
// Created by liuzheng on 18-4-15.
//

#ifndef HTTPSERVER_CONNECTION_MANAGER_H
#define HTTPSERVER_CONNECTION_MANAGER_H


#include <set>
#include "connection.h"


namespace http
{
    namespace server
    {
        class connection_manager {
        public:
            connection_manager(const connection_manager&) = delete;
            connection_manager& operator=(const connection_manager&) = delete;

            connection_manager();

            void start(connection_ptr c);

            void stop(connection_ptr c);

            void stopAll();

        private:
            std::set<connection_ptr> connetions_;
        };
    }
}





#endif //HTTPSERVER_CONNECTION_MANAGER_H
