//
// Created by liuzheng on 18-2-4.
//

#include "DBPool.h"
#include "../util/ConfigFileReader.h"

YLResultSet::YLResultSet(MYSQL_RES *res) : m_res(res)
{
    int num_fields = mysql_num_fields(m_res);
    MYSQL_FIELD *field = mysql_fetch_field(m_res);

    for (int i = 0; i < num_fields; ++i)
    {
        m_key_map.insert(std::make_pair(field[i].name, i));
    }
}

YLResultSet::~YLResultSet()
{
    if (m_res)
    {
        mysql_free_result(m_res);
        m_res = nullptr;
    }
}

bool YLResultSet::next()
{
    m_row = mysql_fetch_row(m_res);
    if (m_row)
        return true;
    else
        return false;
}

int YLResultSet::_GetIndex(const std::string &key)
{
    auto iter = m_key_map.find(key);

    if (iter == m_key_map.end())
        return -1;
    else
        return iter->second;
}

int YLResultSet::getInt(const std::string &key)
{
    int idx = _GetIndex(key);

    if (idx == -1)
        return 0;
    else
    {
        return atoi(m_row[idx]);
    }
}

std::string YLResultSet::getString(const std::string &key)
{
    int idx = _GetIndex(key);

    if (idx == -1)
        return  std::string();
    else
        return m_row[idx];
}


/*************************YLDBConn**************************/

YLDBConn::YLDBConn(YLDBPool *ylDBPool) : m_pDBPool(ylDBPool), m_mysql(nullptr)
{

}

YLDBConn::~YLDBConn()
{

}

int YLDBConn::init()
{
    m_mysql = mysql_init(NULL);
    if (!m_mysql)
    {
        //输出日志
        return 1;
    }

    my_bool reconnect = true;
    //只在调用mysql_real_connect之前调用才会生效
    mysql_options(m_mysql, MYSQL_OPT_RECONNECT, &reconnect);
    mysql_options(m_mysql, MYSQL_SET_CHARSET_NAME, "utf8");

    if (!mysql_real_connect(m_mysql, m_pDBPool->getDBServerIP().c_str(), m_pDBPool->getUserName().c_str(),
                            m_pDBPool->getPassword().c_str(), m_pDBPool->getDBName().c_str(), m_pDBPool->getDBServerPort(), NULL, 0))
    {
        //输出日志
        return 2;
    }

    return 0;
}

const std::string YLDBConn::getPoolName() const
{
    return m_pDBPool->getPoolName();
}

YLResultSet* YLDBConn::executeQuery(const std::string sql_query)
{
    if (mysql_real_query(m_mysql, sql_query.c_str(), sql_query.length()))
    {
        //输出日志
        return nullptr;
    }

    MYSQL_RES *res = mysql_store_result(m_mysql);

    if (!res)
    {
        //输出日志
        return nullptr;
    }

    YLResultSet *r_set = new YLResultSet(res);
    return r_set;
}

bool YLDBConn::executeUpdate(const std::string sql_update)
{
    if (mysql_real_query(m_mysql, sql_update.c_str(), sql_update.length()))
    {
        //输出日志
        return false;
    }

    if (mysql_affected_rows(m_mysql) > 0)
        return true;
    else
        return false;
}

uint32_t YLDBConn::getInsertId() const
{
    return (uint32_t)mysql_insert_id(m_mysql);
}

/*************************YLDBPool**************************/
YLDBPool::YLDBPool(const std::string &pool_name, const std::string &db_server_ip, uint16_t db_server_port,
                   const std::string &username, const std::string &password, const std::string &db_name,
                   int max_conn_cnt)
{
    m_pool_name = pool_name;
    m_db_server_ip = db_server_ip;
    m_db_server_port = db_server_port;
    m_username = username;
    m_password = password;
    m_db_name = db_name;
    m_db_max_conn_cnt = max_conn_cnt;
    m_db_cur_conn_cnt = MIN_DB_CONN_CNT;
}

YLDBPool::~YLDBPool()
{
    for (auto iter = m_free_list.begin(); iter != m_free_list.end(); ++iter)
    {
        YLDBConn *pConn = *iter;
        delete pConn;
    }

    m_free_list.clear();
}

int YLDBPool::init()
{
    for (int i = 0; i < m_db_cur_conn_cnt; ++i)
    {
        YLDBConn* pConn = new YLDBConn(this);
        int ret = pConn->init();
        if (ret) {
            //日志输出

            delete pConn;
            return ret;
        }
        m_free_list.push_back(pConn);
    }

    //日志输出

    return 0;
}

YLDBConn* YLDBPool::getConnection()
{
    //需要同步
    //mutex.lock();

    while (m_free_list.empty())
    {
        //可用连接为空，等待连接释放
        if (m_db_cur_conn_cnt >= m_db_max_conn_cnt)
        {
            //条件变量
            //cond.wait();
        }
        //尚未达到可分配的最大值，创建新的连接分配
        else
        {
            YLDBConn *pConn = new YLDBConn(this);
            int ret = pConn->init();
            if (ret)
            {
                //输出日志
                delete pConn;
                //mutex.unlock();
                return nullptr;
            }
            else
            {
                m_free_list.push_back(pConn);
                ++m_db_cur_conn_cnt;
                //输出日志
            }
        }
    }

    YLDBConn* pConn = m_free_list.front();
    m_free_list.pop_front();

    //mutex.unlock();

    return pConn;

}

void YLDBPool::releaseConnection(YLDBConn *conn)
{
    //mutex.lock();

    auto iter = m_free_list.begin();
    for (; iter != m_free_list.end(); ++iter)
    {
        if (*iter == conn)
            break;
    }

    if (iter == m_free_list.end())
    {
        m_free_list.push_back(conn);
    }

    //cond.signal();
    //mutex.unlock();
}

/*************************YLDBManager**************************/
YLDBManager* YLDBManager::m_db_manager = nullptr;

YLDBManager::YLDBManager()
{

}

YLDBManager::~YLDBManager()
{

}

YLDBManager* YLDBManager::getInstance()
{
    if (!m_db_manager)
    {
        m_db_manager = new YLDBManager();

        if (m_db_manager->init())
        {
            delete m_db_manager;
            m_db_manager = nullptr;
        }
    }

    return m_db_manager;
}

int YLDBManager::init()
{
//    ConfigFileReader config("databaseproxyserver.conf");

}

YLDBConn* YLDBManager::getConnection(const std::string &dbpool_name)
{
    auto iter = m_dbpool_map.find(dbpool_name);

    if (iter == m_dbpool_map.end())
        return nullptr;
    else
        return iter->second->getConnection();
}

void YLDBManager::releaseConnecetion(YLDBConn *conn)
{
    if (!conn)
        return;

    auto iter = m_dbpool_map.find(conn->getPoolName());
    if (iter != m_dbpool_map.end())
        iter->second->releaseConnection(conn);
}