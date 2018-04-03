//
// Created by liuzheng on 18-3-24.
//

#ifndef MSGSERVER_USER_H
#define MSGSERVER_USER_H


#include <string>
#include <map>

class ClientConn;
class BasePdu;

class User {
public:
    typedef enum {
        Online  = 1,
        Offline = 2,
        Hide    = 3
    }Status;

    User();
    ~User();

    void setUserId(uint32_t user_id) { m_user_id = user_id; }
    uint32_t getUserId() const { return m_user_id; }
    void setConn(ClientConn *clientConn) { m_validate_conn = clientConn; }
    ClientConn* getConn() { return m_validate_conn; }
    void setStatus(Status status) { m_status = status; }
    Status getStatus() { return m_status; }


private:
    uint32_t  m_user_id;
    Status m_status;
    ClientConn *m_validate_conn;

};

class UserManager {
public:
    static UserManager* instance();
    ~UserManager(){}

    void addUser(uint32_t user_id, ClientConn *);
    void removerUser(uint32_t user_id);
    User* getUser(uint32_t user_id);

    bool isLogin(uint32_t user_id);

private:
    UserManager();
    static UserManager *m_instance;

    std::map<uint32_t, User*> m_users;
};


#endif //MSGSERVER_USER_H
