/*================================================================
*   
*   文件名称: DBPool.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月09日　 下午11:47
*   描   述: 数据库连接池
*
================================================================*/


#ifndef DBSERVER_DBPOOL_H
#define DBSERVER_DBPOOL_H

#include <mysql/mysql.h>
#include <map>
#include <string>
#include <list>
#include "thread/Lock.h"
//结果集
class ResultSet
{
public:
    ResultSet(MYSQL_RES *res);
    virtual ~ResultSet();

    bool next();
    int getInt(const std::string &key);
    std::string getString(const std::string &key);
private:
    int _GetIndex(const std::string &key);

    MYSQL_RES *m_res ;
    MYSQL_ROW  m_row;
    std::map<std::string, int> m_key_map;
};

class DBPool;

class DBConn
{
public:
    DBConn(DBPool *);
    virtual ~DBConn();

    int init();
    ResultSet* query(const std::string&);
    bool update(const std::string&);

    uint32_t getInsertId();

    std::string getPoolName();

    MYSQL* getMysql() { return m_mysql; }

private:
    MYSQL  *m_mysql;
    DBPool *m_pool;
};

class DBPool {
public:
    DBPool(const std::string &pool_name, const std::string &server_ip, uint16_t port,
           const std::string &username, const std::string &password, const std::string &db_name, int max_conn_cnt);

    virtual ~DBPool();

    int init();

    DBConn* getConnection();
    void releaseConnection(DBConn*);

    std::string getPoolName() const { return m_pool_name; }
    std::string getServerIP() const { return m_server_ip; }
    uint16_t    getPort() const { return m_port; }
    std::string getUserName() const { return m_username; }
    std::string getPassword() const { return m_password; }
    std::string getDBName() const { return m_db_name; }
private:
    std::string       m_pool_name;
    std::string       m_server_ip;
    uint16_t          m_port;
    std::string       m_username;
    std::string       m_password;
    std::string       m_db_name;
    uint32_t          m_db_cur_conn_cnt;
    uint32_t          m_db_max_conn_cnt;

    std::list<DBConn*>          m_free_conn_list;
    youliao::thread::Condition  m_conndition;
};


class DBManager
{
public:
    virtual ~DBManager();
    static DBManager* instance();

    void init();

    DBConn* getConnection();

    void releaseConnection(DBConn *conn);

private:
    DBManager();
    static DBManager *m_manager;
    DBPool *m_pool;
};
#endif //DBSERVER_DBPOOL_H
