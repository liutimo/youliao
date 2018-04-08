//
// Created by liuzheng on 18-4-8.
//

#ifndef DBSERVER_CACHEPOOL_H
#define DBSERVER_CACHEPOOL_H

#include "hiredis.h"
#include <string>
#include <list>
#include <map>
#include <vector>
#include "thread/Lock.h"

using namespace youliao::thread;
using namespace std;

class CachePool;

class CacheConn {
public:
    CacheConn(CachePool *cachePool);
    virtual ~CacheConn();

    int init();
    const string& getPoolName();

    string get(string key);
    //设置生存时长
    string setex(string key, int timeout, string value);
    string set(string key, string& value);

    //批量获取
    bool mget(const vector<string>& keys, map<string, string>& ret_value);
    // 判断一个key是否存在
    bool isExists(string &key);

    // Redis hash structure
    long hdel(const string &key, string field);
    string hget(const string &key, string field);
    bool hgetAll(const string &key, map<string, string>& ret_value);
    long hset(const string &key, string field, string value);
    string hmset(const string &key, map<string, string>& hash);
    bool hmget(const string &key, list<string>& fields, list<string>& ret_value);
    long hincrBy(const string &key, string field, long value);
    long incrBy(const string &key, long value);

    //原子加减1
    long incr(const string &key);
    long decr(const string &key);

    // Redis list structure
    long lpush(const string &key, string value);
    long rpush(const string &key, string value);
    long llen(const string &key);
    bool lrange(const string &key, long start, long end, list<string>& ret_value);

    //Redis set structure
    long sAdd(const string &setName, string value);
    bool sIsMem(const string &setName, string value);
    long sRem(const string &setName, string value);
private:
    void free()
    {
        redisFree(m_redis_context);
        m_redis_context = nullptr;
    }

    CachePool       *m_cache_pool;
    redisContext    *m_redis_context;
    uint64_t         m_last_connect_time;
};


class CachePool
{
public:
    CachePool(const string &poolName, const string &serverIp, int serverPort, int dbNum, int maxConnCnt);
    virtual ~CachePool();

    int init();

    CacheConn *getCacheConn();
    void releaseCacheConn(CacheConn *cacheConn);

    const string& getPoolName() { return m_pool_name; }
    const string& getServerIp() { return m_server_ip; }
    int getServerPort() { return m_server_port; }
    int getDbNum() { return  m_db_num; }

private:
    string  m_pool_name;
    string  m_server_ip;
    int     m_server_port;
    int     m_db_num;

    int     m_cur_conn_cnt;
    int     m_max_conn_cnt;
    list<CacheConn*>    m_free_list;
    Condition           m_free_notify;
};

class CacheManager
{
public:
    virtual ~CacheManager();

    static CacheManager* instance();

    int init();
    CacheConn *getCacheConn(const string& poolName);
    void releaseCacheConn(CacheConn *cacheConn);

private:
    CacheManager();

private:
    static CacheManager*    s_cache_manager;
    map<string, CachePool*> m_cache_pool_map;
};


#endif //DBSERVER_CACHEPOOL_H
