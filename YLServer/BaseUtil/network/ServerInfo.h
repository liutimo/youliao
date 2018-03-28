//
// Created by liuzheng on 18-3-24.
//

#ifndef BASEUTIL_SERVERINFO_H
#define BASEUTIL_SERVERINFO_H


#include <string>
#include "BaseConn.h"

namespace youliao
{
    namespace network
    {
        typedef struct {
            std::string server_ip;
            uint16_t    server_port;
            uint32_t    idle_cnt;
            uint32_t    reconnect_cnt;
            BaseConn*   server_conn;
        }serv_info_t;

        template <class T>
        void serv_init(serv_info_t *server_list, uint32_t server_count)
        {
            for (uint32_t i = 0; i < server_count; ++i)
            {
                T *pConn = new T();
                pConn->connect(server_list[i].server_ip, server_list[i].server_port, i);
                server_list[i].server_conn = pConn;
                server_list[i].idle_cnt = 0;
                server_list[i].reconnect_cnt = 2;
            }
        }

        template <class T>
        void serv_check_reconnect(serv_info_t *server_list, uint32_t server_count)
        {
            T *pConn;
            for (uint32_t i = 0; i < server_count; ++i)
            {
                pConn = (T*)server_list[i].server_conn;
                if (!pConn)
                {
                    ++(server_list[i].idle_cnt);
                    if (server_list[i].idle_cnt >= server_list[i].reconnect_cnt)
                    {
                        pConn = new T();
                        pConn->connect(server_list[i].server_ip, server_list[i].server_port, i);
                        server_list[i].server_conn = pConn;
                    }
                }

            }
        }

        template <class T>
        void serv_reset(serv_info_t* server_list, uint32_t server_count, uint32_t serv_idx) {
            {
                if (serv_idx >= server_count) {
                    return;
                }

                server_list[serv_idx].server_conn = NULL;
                server_list[serv_idx].idle_cnt = 0;
                server_list[serv_idx].reconnect_cnt *= 2;
                if (server_list[serv_idx].reconnect_cnt > 64) {
                    server_list[serv_idx].reconnect_cnt = 2;
                }
            }

        }
    }

}




#endif //BASEUTIL_SERVERINFO_H
