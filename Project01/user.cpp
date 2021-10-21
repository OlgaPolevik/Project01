//
//  user.cpp
//  Project01
//
//  Created by Ольга Полевик on 20.10.2021.
//

#include <stdio.h>
#include "user.h"

User::User() = default;
User::User(const string& login, const string& password, const string& name) : m_name(name), m_login(login), m_password(password)
    {
        
    }
User::~User() = default;
    
void User::setlogin(const string& login)
    {
        m_login = login;
    }
const string& User::getlogin() const
    {
        return m_login;
    }
void User::setpassword(const string& password)
    {
        m_password = password;
    }
const string& User::getpassword() const
    {
        return m_password;
    }
void User::setname(const string& name)
    {
        m_name = name;
    }
const string& User::getname() const
    {
        return m_name;
    }
    
istream& operator >>(istream& is, User& obj)
{
    is >> obj.m_name;
    is >> obj.m_login;
    is >> obj.m_password;
    return is;
}
ostream& operator <<(ostream& os, const User& obj)
{
    os << obj.m_name;
    os << ' ';
    os << obj.m_login;
    os << ' ';
    os << obj.m_password;
    os << ' ';
    return os;
}
