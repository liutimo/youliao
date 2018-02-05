//
// Created by liuzheng on 18-2-4.
//

#ifndef DB_PROXY_DBPOOL_H
#define DB_PROXY_DBPOOL_H

#include "common.h"

#include <mysql/mysql.h>

class YLResultSet
{
public:
    explicit YLResultSet(MYSQL_RES *res);
    virtual ~YLResultSet();

    bool next();
    int getInt(const std::string& key);
    std::string getString(const std::string& key);

private:
    int _GetIndex(const std::string& key);

    MYSQL_RES*                  m_res;
    MYSQL_ROW                   m_row;
    std::map<std::string, int>  m_key_map;
};

class YLDBPool;


class YLDBConn
{
public:
    explicit YLDBConn(YLDBPool* ylDBPool);
    virtual ~YLDBConn();
    int init();


    YLResultSet* executeQuery(const std::string sql_query);
    bool executeUpdate(const std::string sql_update);

    uint32_t  getInsertId () const;

    const std::string getPoolName() const;

    MYSQL* getMysql() const { return m_mysql; }

private:
    YLDBPool *m_pDBPool;
    MYSQL* m_mysql;
};


class YLDBPool
{
public:
    explicit YLDBPool(const std::string& pool_name, const std::string& db_server_ip, uint16_t db_server_port,
             const std::string& username, const std::string& password, const std::string& db_name, int max_conn_cnt);

    virtual ~YLDBPool();

    int init();
    YLDBConn *getConnection();
    void releaseConnection(YLDBConn *conn);

    const std::string& getPoolName()    const { return m_pool_name; }
    const std::string& getDBServerIP()  const { return m_db_server_ip; }
    uint16_t getDBServerPort()          const { return m_db_server_port; }
    const std::string& getUserName()    const { return m_username; }
    const std::string& getPassword()    const { return m_password; }
    const std::string& getDBName()      const { return m_db_name; }

private:
    std::string 		m_pool_name;
    std::string 		m_db_server_ip;
    uint16_t	        m_db_server_port;
    std::string 		m_username;
    std::string 		m_password;
    std::string 		m_db_name;
    int			        m_db_cur_conn_cnt;
    int 		        m_db_max_conn_cnt;


    //未分配的连接
    std::list<YLDBConn*>  m_free_list;

    const int MIN_DB_CONN_CNT = 2;

};

class YLDBManager
{
public:
    virtual ~YLDBManager();

    static YLDBManager* getInstance();

    int init();

    YLDBConn* getConnection(const std::string &dbpool_name);
    void releaseConnecetion(YLDBConn *conn);

private:
    YLDBManager();

private:
    static YLDBManager* m_db_manager;
    std::map<std::string, YLDBPool*> m_dbpool_map;
};


#endif //DB_PROXY_DBPOOL_H
