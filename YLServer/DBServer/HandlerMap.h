//
// Created by liuzheng on 18-3-25.
//

#ifndef DBSERVER_HANDLERMAP_H
#define DBSERVER_HANDLERMAP_H


#include <map>
#include "DBProxyTask.h"

typedef std::map<uint16_t, pdu_handler_t > HandlerMap_t;

class HandlerMap {
public:
    virtual ~HandlerMap();

    static HandlerMap* instance();
    void init();
    pdu_handler_t getHandler(uint16_t cid);
private:
    HandlerMap();

private:
    static HandlerMap *s_handler_instance;
    HandlerMap_t       m_handler_map;
};


#endif //DBSERVER_HANDLERMAP_H
