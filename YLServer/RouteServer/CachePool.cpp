//
// Created by liuzheng on 18-4-8.
//

#include "CachePool.h"
#include "util/util.h"
#define MIN_CACHE_CONN_CNT 2

CacheConn::CacheConn(CachePool *cachePool)
{
    m_cache_pool    = cachePool;
    m_redis_context = nullptr;
    m_last_connect_time = 0;
}

CacheConn::~CacheConn()
{
    if (m_redis_context)
    {
        redisFree(m_redis_context);
        m_redis_context = nullptr;
    }
}

int CacheConn::init()
{
    if (m_redis_context != nullptr)
        return 0;

    //4s重连一次
//    uint64_t curr_time = (uint64_t)time(nullptr);
//    if (m_last_connect_time < curr_time + 4)
//        return 1;
//    m_last_connect_time = curr_time;

    //200 ms超时
    struct timeval timeOut = {0, 200000};
    m_redis_context = redisConnectWithTimeout(m_cache_pool->getServerIp().c_str(), m_cache_pool->getServerPort(), timeOut);

    if (!m_redis_context || m_redis_context->err) {
        if (m_redis_context) {
            log("redisConnect failed: %s", m_redis_context->errstr);
            free();
        } else {
            log("redisConnect failed");
        }
        return 1;
    }

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "SELECT %d", 1);
    if (reply && (reply->type == REDIS_REPLY_STATUS) && (strncmp(reply->str, "OK", 2) == 0))
    {
        freeReplyObject(reply);
        return 0;
    }
    else
    {
        log("select cache db failed");
        return 2;
    }
}

const string& CacheConn::getPoolName()
{
    return m_cache_pool->getPoolName();
}

string CacheConn::get(string key)
{
    string value;

    if (init())
    {
        return value;
    }

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "GET %s", key.c_str());

    if (!reply)
    {
        log("redisCommand failed:%s", m_redis_context->errstr);
        free();
        return value;
    }

    if (reply->type == REDIS_REPLY_STRING)
    {
        value.append(reply->str, reply->len);
    }

    freeReplyObject(reply);
    return value;
}

string CacheConn::setex(string key, int timeout, string value)
{
    string retValue;

    if (init())
    {
        return retValue;
    }

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "SETEX %s %d %s", key.c_str(), timeout, value.c_str());
    if (!reply)
    {
        log("redisCommand SETEX falied: %s ", m_redis_context->errstr);
        free();

        return retValue;
    }

    retValue.append(reply->str, reply->len);
    freeReplyObject(reply);
    return retValue;
}

string CacheConn::set(string key, string &value)
{
    string retValue;

    if (init()) {
        return retValue;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "SET %s %s", key.c_str(), value.c_str());
    if (!reply) {
        log("redisCommand failed:%s", m_redis_context->errstr);
        free();
        return retValue;
    }

    retValue.append(reply->str, reply->len);
    freeReplyObject(reply);
    return retValue;
}


bool CacheConn::mget(const vector<string> &keys, map<string, string> &ret_value)
{
    if (init())
        return false;

    if (keys.empty())
        return false;

    string key;
    bool bFirst = true;
    for (auto iter = keys.begin(); iter != keys.end(); ++iter)
    {
        if (bFirst)
        {
            bFirst = false;
            key = *iter;
        }
        else
        {
            key += " " + *iter;
        }
    }

    if (key.empty())
    {
        return false;
    }

    key = "MGET " + key;
    redisReply *reply = (redisReply*)redisCommand(m_redis_context, key.c_str());
    if (!reply)
    {
        log("redisCommand MGET failed:%d", m_redis_context->err);
        free();
        return false;
    }

    if (reply->type == REDIS_REPLY_ARRAY)
    {
        for (size_t i = 0; i < reply->elements; ++i)
        {
            redisReply *childReply = reply->element[i];
            if (childReply->type == REDIS_REPLY_STRING)
                ret_value[keys[i]] = childReply->str;
        }
    }

    freeReplyObject(reply);
    return true;
}

bool CacheConn::isExists(string &key)
{
    if (init())
        return false;

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "EXISTS %s", key.c_str());

    if (!reply)
    {
        log("redisCommand failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        return false;
    }

    long retValue = reply->integer;
    freeReplyObject(reply);

    if (0 == retValue)
        return false;
    else
        return true;
}

long CacheConn::hdel(const string &key, string field)
{
    if (init())
        return 0;

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "HDEL %s %s", key.c_str(), field.c_str());

    if (!reply)
    {
        log("redisCommand HDEL failed: %s", m_redis_context->errstr);
        free();
        return 0;
    }

    long retValue = reply->integer;
    freeReplyObject(reply);
    return retValue;
}

string CacheConn::hget(const string &key, string field)
{
    string retValue;
    if (init()) {
        return retValue;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "HGET %s %s", key.c_str(), field.c_str());
    if (!reply) {
        log("redisCommand HGET failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return retValue;
    }

    if (reply->type == REDIS_REPLY_STRING) {
        retValue.append(reply->str, reply->len);
    }

    freeReplyObject(reply);
    return retValue;
}


bool CacheConn::hgetAll(const string &key, map<string, string>& ret_value)
{
    if (init()) {
        return false;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "HGETALL %s", key.c_str());
    if (!reply) {
        log("redisCommand HGETALL failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return false;
    }

    if ( (reply->type == REDIS_REPLY_ARRAY) && (reply->elements % 2 == 0) ) {
        for (size_t i = 0; i < reply->elements; i += 2) {
            redisReply* field_reply = reply->element[i];
            redisReply* value_reply = reply->element[i + 1];

            string field(field_reply->str, field_reply->len);
            string value(value_reply->str, value_reply->len);
            ret_value.insert(make_pair(field, value));
        }
    }

    freeReplyObject(reply);
    return true;
}

long CacheConn::hset(const string &key, string field, string value)
{
    if (init()) {
        return -1;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "HSET %s %s %s", key.c_str(), field.c_str(), value.c_str());
    if (!reply) {
        log("redisCommand HSET failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CacheConn::hincrBy(const string &key, string field, long value)
{
    if (init()) {
        return -1;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "HINCRBY %s %s %ld", key.c_str(), field.c_str(), value);
    if (!reply) {
        log("redisCommand HINCRBY failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CacheConn::incrBy(const string &key, long value)
{
    if(init())
    {
        return -1;
    }

    redisReply* reply = (redisReply*)redisCommand(m_redis_context, "INCRBY %s %ld", key.c_str(), value);
    if(!reply)
    {
        log("redis Command INCRBY failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return -1;
    }
    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

string CacheConn::hmset(const string &key, map<string, string> &hash)
{
    string ret_value;

    if (init()) {
        return ret_value;
    }

    int argc = hash.size() * 2 + 2;
    const char** argv = new const char* [argc];
    if (!argv) {
        return ret_value;
    }

    argv[0] = "HMSET";
    argv[1] = key.c_str();
    int i = 2;
    for (map<string, string>::iterator it = hash.begin(); it != hash.end(); it++) {
        argv[i++] = it->first.c_str();
        argv[i++] = it->second.c_str();
    }

    redisReply* reply = (redisReply *)redisCommandArgv(m_redis_context, argc, argv, NULL);
    if (!reply) {
        log("redisCommand HMSET failed:%s", m_redis_context->errstr);
        delete [] argv;

        redisFree(m_redis_context);
        m_redis_context = NULL;
        return ret_value;
    }

    ret_value.append(reply->str, reply->len);

    delete [] argv;
    freeReplyObject(reply);
    return ret_value;
}


bool CacheConn::hmget(const string &key, list<string> &fields, list<string> &ret_value)
{
    if (init()) {
        return false;
    }

    int argc = fields.size() + 2;
    const char** argv = new const char* [argc];
    if (!argv) {
        return false;
    }

    argv[0] = "HMGET";
    argv[1] = key.c_str();
    int i = 2;
    for (list<string>::iterator it = fields.begin(); it != fields.end(); it++) {
        argv[i++] = it->c_str();
    }

    redisReply* reply = (redisReply *)redisCommandArgv(m_redis_context, argc, (const char**)argv, NULL);
    if (!reply) {
        log("redisCommand HMGET failed:%s", m_redis_context->errstr);
        delete [] argv;

        redisFree(m_redis_context);
        m_redis_context = NULL;

        return false;
    }

    if (reply->type == REDIS_REPLY_ARRAY) {
        for (size_t i = 0; i < reply->elements; i++) {
            redisReply* value_reply = reply->element[i];
            string value(value_reply->str, value_reply->len);
            ret_value.push_back(value);
        }
    }

    delete [] argv;
    freeReplyObject(reply);
    return true;
}

long CacheConn::incr(const string &key)
{
    if(init())
    {
        return -1;
    }

    redisReply* reply = (redisReply*)redisCommand(m_redis_context, "INCR %s", key.c_str());
    if(!reply)
    {
        log("redis Command INCR failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return -1;
    }
    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CacheConn::decr(const string &key)
{
    if(init())
    {
        return -1;
    }

    redisReply* reply = (redisReply*)redisCommand(m_redis_context, "DECR %s", key.c_str());
    if(!reply)
    {
        log("redis  Command  DECR failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return -1;
    }
    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CacheConn::lpush(const string &key, string value)
{
    if (init()) {
        return -1;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "LPUSH %s %s", key.c_str(), value.c_str());
    if (!reply) {
        log("redisCommand LPUSH failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CacheConn::rpush(const string &key, string value)
{
    if (init()) {
        return -1;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "RPUSH %s %s", key.c_str(), value.c_str());
    if (!reply) {
        log("redisCommand RPUSH failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CacheConn::llen(const string &key)
{
    if (init()) {
        return -1;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "LLEN %s", key.c_str());
    if (!reply) {
        log("redisCommand LLEN failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

bool CacheConn::lrange(const string &key, long start, long end, list<string> &ret_value)
{
    if (init()) {
        return false;
    }

    redisReply* reply = (redisReply *)redisCommand(m_redis_context, "LRANGE %s %d %d", key.c_str(), start, end);
    if (!reply) {
        log("redisCommand  LRANGE failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return false;
    }

    if (reply->type == REDIS_REPLY_ARRAY) {
        for (size_t i = 0; i < reply->elements; i++) {
            redisReply* value_reply = reply->element[i];
            string value(value_reply->str, value_reply->len);
            ret_value.push_back(value);
        }
    }

    freeReplyObject(reply);
    return true;
}

long CacheConn::sAdd(const string &setName, string value)
{
    if (init())
        return 0;

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "SADD %s %s", setName.c_str(), value.c_str());

    if (!reply) {
        log("redisCommand  LRANGE failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return 0;
    }

    auto retValue = reply->integer;
    freeReplyObject(reply);
    return retValue;
}

bool CacheConn::sIsMem(const string &setName, string value)
{
    if (init())
        return 0;

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "SISMEMBER %s %s", setName.c_str(), value.c_str());

    if (!reply) {
        log("redisCommand  LRANGE failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return 0;
    }

    auto retValue = reply->integer;
    freeReplyObject(reply);

    if (retValue == 1)
        return true;
    else
        return false;


}

long CacheConn::sRem(const string &setName, string value)
{
    if (init())
        return 0;

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "SREM %s %s", setName.c_str(), value.c_str());

    if (!reply) {
        log("redisCommand  LRANGE failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return 0;
    }

    auto retValue = reply->integer;
    freeReplyObject(reply);
    return retValue;
}


std::list<std::uint32_t > CacheConn::sMembers(const string &setName)
{

    std::list<std::uint32_t> members;

    if (init())
        return members;

    redisReply *reply = (redisReply*)redisCommand(m_redis_context, "SMEMBERS %s", setName.c_str());

    if (!reply) {
        log("redisCommand  SMEMBERS failed:%s", m_redis_context->errstr);
        redisFree(m_redis_context);
        m_redis_context = NULL;
        return members;
    }

    for (int i = 0; i < reply->elements; ++i)
    {
        auto reply1 = reply->element[i];
        members.push_back(atoi(reply1->str));
    }
    freeReplyObject(reply);
    return members;
}


////////////////////////////////////////
CachePool::CachePool(const string &poolName, const string &serverIp, int serverPort, int dbNum, int maxConnCnt)
{
    m_pool_name = poolName;
    m_server_ip = serverIp;
    m_server_port = serverPort;
    m_db_num = dbNum;
    m_max_conn_cnt = maxConnCnt;
    m_cur_conn_cnt = MIN_CACHE_CONN_CNT;
}

CachePool::~CachePool()
{
    m_free_notify.lock();
    for (auto iter = m_free_list.begin(); iter != m_free_list.end(); ++iter)
    {
        auto *conn = *iter;
        delete conn;
    }

    m_free_list.clear();
    m_cur_conn_cnt = 0;
    m_free_notify.unlock();
}

int CachePool::init()
{
    for(int i = 0; i < m_cur_conn_cnt; ++i)
    {
        auto *conn = new CacheConn(this);
        if (conn->init())
        {
            delete conn;
            return 1;
        }
        m_free_list.push_back(conn);
    }

    log("cache pool: %s, list size: %lu", m_pool_name.c_str(), m_free_list.size());
    return 0;
}

CacheConn* CachePool::getCacheConn()
{
    m_free_notify.lock();

    while (m_free_list.empty()) {
        if (m_cur_conn_cnt >= m_max_conn_cnt) {
            m_free_notify.wait();
        } else {
            auto conn = new CacheConn(this);
            int ret = conn->init();
            if (ret) {
                log("init cacheConn failed");
                delete conn;
                m_free_notify.unlock();
                return nullptr;
            } else {
                m_free_list.push_back(conn);
                log("new cache conn: %s, conn_cnt: %d", m_pool_name.c_str(), m_cur_conn_cnt);
            }
        }
    }

    auto conn = m_free_list.front();
    if (m_cur_conn_cnt >= 2)
        ++m_cur_conn_cnt;
    m_free_list.pop_front();
    m_free_notify.unlock();
    log("获取cache连接， 当前连接数%d, 最大连接数%d", m_cur_conn_cnt, m_max_conn_cnt);
    return conn;
}

void CachePool::releaseCacheConn(CacheConn *cacheConn)
{
    m_free_notify.lock();

    auto iter = m_free_list.begin();

    for (; iter != m_free_list.end(); ++iter)
    {
        if (*iter == cacheConn)
            break;
    }

    if (iter == m_free_list.end())
        m_free_list.push_back(cacheConn);
    if (m_cur_conn_cnt > 2)
        --m_cur_conn_cnt;
    m_free_notify.signal();
    m_free_notify.unlock();

    log("释放cache连接， 当前连接数%d, 最大连接数%d", m_cur_conn_cnt, m_max_conn_cnt);
}
//////////////////////////////

CacheManager* CacheManager::s_cache_manager = nullptr;

CacheManager::CacheManager()
{

}

CacheManager::~CacheManager()
{

}

CacheManager* CacheManager::instance()
{
    if (!s_cache_manager)
    {
        s_cache_manager = new CacheManager();
        if (s_cache_manager->init())
        {
            delete s_cache_manager;
            s_cache_manager = nullptr;
        }
    }

    return s_cache_manager;
}

int CacheManager::init()
{
    CachePool *cachePool = new CachePool("OnlineUser", "127.0.0.1", 6379, 1, 16);

    m_cache_pool_map.insert(make_pair("OnlineUser", cachePool));

    return 0;
}

CacheConn* CacheManager::getCacheConn(const string &poolName)
{
    auto iter = m_cache_pool_map.find(poolName);
    if (iter != m_cache_pool_map.end())
        return iter->second->getCacheConn();
    else
        return nullptr;
}

void CacheManager::releaseCacheConn(CacheConn *cacheConn)
{
    if (!cacheConn)
        return;

    auto iter = m_cache_pool_map.find(cacheConn->getPoolName());

    if (iter != m_cache_pool_map.end())
    {
        iter->second->releaseCacheConn(cacheConn);
    }

}