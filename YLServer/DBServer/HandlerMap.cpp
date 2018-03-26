//
// Created by liuzheng on 18-3-25.
//

#include "HandlerMap.h"
#include "business/Interface.h"
#include "pdu/protobuf/youliao.base.pb.h"
using namespace youliao::pdu::base;

HandlerMap* HandlerMap::s_handler_instance = nullptr;

HandlerMap::HandlerMap()
{

}

HandlerMap::~HandlerMap()
{

}

HandlerMap* HandlerMap::instance()
{
    if (!s_handler_instance)
    {
        s_handler_instance = new HandlerMap;
        s_handler_instance->init();
    }

    return s_handler_instance;
}

void HandlerMap::init()
{
    //login validate
    m_handler_map.insert(std::make_pair(CID_SERVER_VALIDATE_REQUEST, DB_INTERFACE::login));
}

pdu_handler_t HandlerMap::getHandler(uint16_t cid)
{
    HandlerMap_t::iterator iter = m_handler_map.find(cid);
    if (iter != m_handler_map.end())
        return iter->second;
    else
        return nullptr;
}