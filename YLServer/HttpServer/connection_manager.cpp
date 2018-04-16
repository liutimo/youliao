//
// Created by liuzheng on 18-4-15.
//

#include "connection_manager.h"
namespace http
{
    namespace server
    {
        connection_manager::connection_manager()
        {

        }

        void connection_manager::start(connection_ptr c)
        {
            connetions_.insert(c);
            c->start();
        }

        void connection_manager::stop(connection_ptr c)
        {
            connetions_.erase(c);
            c->stop();
        }

        void connection_manager::stopAll()
        {
            for (auto c : connetions_)
            {
                c->stop();
            }
            connetions_.clear();
        }
    }
}
