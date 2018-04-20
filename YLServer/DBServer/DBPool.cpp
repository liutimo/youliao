/*================================================================
*   
*   文件名称: DBPool.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月09日　 下午11:47
*
================================================================*/


#include "DBPool.h"
#include "util/util.h"



PrepareStatement::PrepareStatement()
{
    m_stmt = NULL;
    m_param_bind = NULL;
    m_param_cnt = 0;
}

PrepareStatement::~PrepareStatement()
{
    if (m_stmt) {
        mysql_stmt_close(m_stmt);
        m_stmt = NULL;
    }

    if (m_param_bind) {
        delete [] m_param_bind;
        m_param_bind = NULL;
    }
}

bool PrepareStatement::init(MYSQL* mysql, std::string& sql)
{
    mysql_ping(mysql);

    m_stmt = mysql_stmt_init(mysql);
    if (!m_stmt) {
        log("mysql_stmt_init failed");
        return false;
    }

    if (mysql_stmt_prepare(m_stmt, sql.c_str(), sql.size())) {
        log("mysql_stmt_prepare failed: %s", mysql_stmt_error(m_stmt));
        return false;
    }

    m_param_cnt = mysql_stmt_param_count(m_stmt);
    if (m_param_cnt > 0) {
        m_param_bind = new MYSQL_BIND [m_param_cnt];
        if (!m_param_bind) {
            log("new failed");
            return false;
        }

        memset(m_param_bind, 0, sizeof(MYSQL_BIND) * m_param_cnt);
    }

    return true;
}

void PrepareStatement::setParam(uint32_t index, int& value)
{
    if (index >= m_param_cnt) {
        log("index too large: %d", index);
        return;
    }

    m_param_bind[index].buffer_type = MYSQL_TYPE_LONG;
    m_param_bind[index].buffer = &value;
}

void PrepareStatement::setParam(uint32_t index, uint32_t& value)
{
    if (index >= m_param_cnt) {
        log("index too large: %d", index);
        return;
    }

    m_param_bind[index].buffer_type = MYSQL_TYPE_LONG;
    m_param_bind[index].buffer = &value;
}

void PrepareStatement::setParam(uint32_t index, std::string& value)
{
    if (index >= m_param_cnt) {
        log("index too large: %d", index);
        return;
    }

    m_param_bind[index].buffer_type = MYSQL_TYPE_STRING;
    m_param_bind[index].buffer = (char*)value.c_str();
    m_param_bind[index].buffer_length = value.size();
}

void PrepareStatement::setParam(uint32_t index, const std::string& value)
{
    if (index >= m_param_cnt) {
        log("index too large: %d", index);
        return;
    }

    m_param_bind[index].buffer_type = MYSQL_TYPE_STRING;
    m_param_bind[index].buffer = (char*)value.c_str();
    m_param_bind[index].buffer_length = value.size();
}

bool PrepareStatement::executeUpdate()
{
    if (!m_stmt) {
        log("no m_stmt");
        return false;
    }

    if (mysql_stmt_bind_param(m_stmt, m_param_bind)) {
        log("mysql_stmt_bind_param failed: %s", mysql_stmt_error(m_stmt));
        return false;
    }

    if (mysql_stmt_execute(m_stmt)) {
        log("mysql_stmt_execute failed: %s", mysql_stmt_error(m_stmt));
        return false;
    }

    if (mysql_stmt_affected_rows(m_stmt) == 0) {
        log("ExecuteUpdate have no effect");
        return false;
    }

    return true;
}

uint32_t PrepareStatement::getInsertId()
{
    return mysql_stmt_insert_id(m_stmt);
}


ResultSet::ResultSet(MYSQL_RES *res) : m_res(res)
{
    //获取结果集的所有字段
    int num_fields = mysql_num_fields(m_res);
    MYSQL_FIELD *fields = mysql_fetch_field(m_res);
    for (int i = 0; i < num_fields; ++i)
    {
        m_key_map.insert(std::make_pair(fields[i].name, i));
    }
}

ResultSet::~ResultSet()
{
    if (m_res != nullptr)
        mysql_free_result(m_res);
}

bool ResultSet::next()
{
    m_row = mysql_fetch_row(m_res);

    return m_row != nullptr;
}

int ResultSet::_GetIndex(const std::string &key)
{
    auto iter = m_key_map.find(key);
    if (iter == m_key_map.end())
        return -1;
    else
        return iter->second;
}

int ResultSet::getInt(const std::string &key)
{
    int index = _GetIndex(key);
    if (index == -1)
        return 0;

    return atoi(m_row[index]);
}

std::string ResultSet::getString(const std::string &key)
{
    int index = _GetIndex(key);
    if (index == -1 | m_row[index] == nullptr)
        return std::string();
    else
        return m_row[index];
}


//////////////////////////////////////
DBConn::DBConn(DBPool *pool) : m_pool(pool)
{
    m_mysql = nullptr;
}

DBConn::~DBConn()
{

}

int DBConn::init()
{
    m_mysql = mysql_init(NULL);
    if (!m_mysql)
    {
        log("mysql_init failed");
        return 1;
    }
    my_bool reconnect = true;
    mysql_options(m_mysql, MYSQL_OPT_RECONNECT, &reconnect);
    mysql_options(m_mysql, MYSQL_SET_CHARSET_NAME, "utf8mb4");

    if (!mysql_real_connect(m_mysql, m_pool->getServerIP().c_str(), m_pool->getUserName().c_str(),
        m_pool->getPassword().c_str(), m_pool->getDBName().c_str(), m_pool->getPort(), NULL, 0))
    {
        log("mysql_real_connect failed: %s ", mysql_error(m_mysql));
        return 2;
    }
    return 0;
}

std::string DBConn::getPoolName()
{
    return m_pool->getPoolName();
}

ResultSet* DBConn::query(const std::string &sql)
{
    mysql_ping(m_mysql);
    if (mysql_real_query(m_mysql, sql.c_str(), sql.length()))
    {
        log("mysql_real_query failed: %s sql: %s", mysql_error(m_mysql), sql.c_str());
        return nullptr;
    }

    MYSQL_RES *res = mysql_store_result(m_mysql);
    if (!res)
    {
        log("mysql_store_result failed: %s", mysql_error(m_mysql));
        return nullptr;
    }

    return new ResultSet(res);
}

bool DBConn::update(const std::string &sql)
{
    mysql_ping(m_mysql);
    if (mysql_real_query(m_mysql, sql.c_str(), sql.length()))
    {
        log("mysql_real_query failed: %s sql: %s", mysql_error(m_mysql), sql.c_str());
        return false;
    }

    if (mysql_affected_rows(m_mysql) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint32_t DBConn::getInsertId()
{
    return (uint32_t)mysql_insert_id(m_mysql);
}

////////////////////////////
DBPool::DBPool(const std::string &pool_name, const std::string &server_ip, uint16_t port,
               const std::string &username, const std::string &password, const std::string &db_name, int max_conn_cnt)
{
    m_pool_name = pool_name;
    m_server_ip = server_ip;
    m_port = port;
    m_username = username;
    m_password = password;
    m_db_name = db_name;
    m_db_max_conn_cnt = max_conn_cnt;
    //初始建立两个连接
    m_db_cur_conn_cnt = 2;
}

DBPool::~DBPool()
{

}

int DBPool::init()
{
    for (int i = 0; i < m_db_cur_conn_cnt; ++i)
    {
        DBConn *dbConn = new DBConn(this);
        int ret = dbConn->init();
        if (ret)
        {
            delete  dbConn;
            return ret;
        }

        m_free_conn_list.push_back(dbConn);
    }
    return  0;
}

DBConn* DBPool::getConnection()
{
    m_conndition.lock();

    while (m_free_conn_list.empty())
    {
        if (m_db_cur_conn_cnt >= m_db_max_conn_cnt)
            m_conndition.wait();
        else {
            DBConn *conn = new DBConn(this);
            int ret = conn->init();
            if (ret)
            {
                log("init dbconnection failed");
                delete conn;
                m_conndition.unlock();
                return nullptr;
            }
            else
            {
                m_free_conn_list.push_back(conn);
                log("new a connection: %s, current connection count: %d", m_pool_name.c_str(), m_db_cur_conn_cnt);

            }

        }
    }
    DBConn *conn = m_free_conn_list.front();
    m_free_conn_list.pop_front();
    ++m_db_cur_conn_cnt;

    log("获取数据库连接，当前连接数%d,总连接数%d", m_db_cur_conn_cnt, m_db_max_conn_cnt);

    m_conndition.unlock();
    return conn;
}

void DBPool::releaseConnection(DBConn *conn)
{
    if (conn == nullptr)
        return;
    m_conndition.lock();

    auto iter = m_free_conn_list.begin();
    for  (; iter != m_free_conn_list.end(); ++iter)
    {
        if (*iter == conn)
            break;
    }

    if (iter == m_free_conn_list.end())
    {
        m_free_conn_list.push_back(conn);
    }
    --m_db_cur_conn_cnt;
    log("释放数据库连接，当前连接数%d,总连接数%d", m_db_cur_conn_cnt, m_db_max_conn_cnt);
    m_conndition.signal();
    m_conndition.unlock();
}

////////////////////////////////

DBManager *DBManager::m_manager = nullptr;

DBManager::DBManager()
{

}

DBManager::~DBManager()
{

}


DBManager* DBManager::instance()
{
    if (m_manager == nullptr)
    {
        m_manager = new DBManager();
        m_manager->init();
    }

    return m_manager;
}

void DBManager::init()
{
    m_pool = new DBPool("pool", "127.0.0.1", 3306, "root", "123456", "youliao", 30);
    m_pool->init();
}

DBConn* DBManager::getConnection()
{
    return m_pool->getConnection();
}

void DBManager::releaseConnection(DBConn *conn)
{
    m_pool->releaseConnection(conn);
}