//
// Created by liuzheng on 18-3-24.
//

#include "User.h"

#include "ClientConn.h"

User::User()
{
    m_user_id = 0;
    m_validate_conn = nullptr;
}

User::~User()
{
    // 似乎连接的释放并不需要由User来操作.
//    m_validate_conn->onClose();
//    delete  m_validate_conn;
}

/*************UserManager*****************/

UserManager* UserManager::m_instance = nullptr;

UserManager* UserManager::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new UserManager;
    }
    return m_instance;
}

UserManager::UserManager()
{

}

void UserManager::addUser(uint32_t user_id, ClientConn *clientConn)
{
    User *user = new User;
    user->setUserId(user_id);
    user->setConn(clientConn);
    m_users.insert(std::make_pair(user_id, user));
}

void UserManager::removerUser(uint32_t user_id)
{
    auto iter = m_users.find(user_id);
    if (iter != m_users.end())
    {
        m_users.erase(iter);
    }
}

User* UserManager::getUser(uint32_t user_id)
{
    auto iter = m_users.find(user_id);
    if (iter != m_users.end())
        return iter->second;

    return nullptr;
}

bool UserManager::isLogin(uint32_t user_id)
{
    if (getUser(user_id) == nullptr)
        return false;

    return true;
}

