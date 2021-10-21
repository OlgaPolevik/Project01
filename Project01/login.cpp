//
//  login.cpp
//  Project01
//
//  Created by Ольга Полевик on 21.10.2021.
//

#include <stdio.h>
#include "login.h"

Login::Login() = default;
Login::~Login() = default;

//проверка на существующего юзера
bool Login::isUserExist (const string& login)
{
     return users.count(login) != 0;
}
//реализация регистрации
bool Login::registerUser (const string& name, const string& login, const string& password)
{
    if (isUserExist(login))
    {
        return false;
    }
    if (users.size() == 3)
    {
        throw exception();
    }    
    User user(name, login, password);
    //users.push_back(user);
    users.emplace(login,user);
    return true;
}
//инициация сессии активной? или залогинивание юзера
Session Login::loginUser (const string& login, const string& password)
{
    map<string,User>::iterator user = users.find(login);
    if(user == users.end())
    {
        return Session();
    }
    if(user -> second.getpassword() == password)
    {
        //coздаем сессию для пользователя у которого совпадают логин и пароль
        Session session;
        session.setlogin(login);
        session.setname(user -> second.getname());
        sessions.emplace(login,session);
        return session;
    }
    return Session();
}

//разлогинивание юзера но не выход из чата
void Login::logout (const Session& session)
{
    sessions.erase(session.getlogin());
}

ostream& operator << (ostream & os, const Login& login )
{
    os << login.users.size() << endl;
    for(const auto & u : login.users)
    {
        os << u.second;
    }
    os << login.sessions.size();
    for(const auto & s : login.sessions)
    {
        os << s.second;
    }
    return os;
}

istream& operator >> (istream & is, Login& login )
{
    size_t users_count;
    
    is >> users_count;
    
    for(int i = 0; i < users_count; i++)
    {
        User u;
        is >> u;
        login.users.emplace(u.getlogin(), u);
    }
    
    size_t sessions_count;
    
    is >> sessions_count;
    
    for(int i = 0; i < sessions_count; i++)
    {
        Session s;
        is >> s;
        login.sessions.emplace(s.getlogin(), s);
    }
    return is;
}
