//
//  session.cpp
//  Project01
//
//  Created by Ольга Полевик on 20.10.2021.
//

#include <stdio.h>
#include "session.h"

Session::Session() = default;
Session::~Session() = default;

void Session::setname(const string& name)
{
    m_name = name;
}
const string& Session::getname() const
{
    return m_name;
}
void Session::setlogin(const string& login)
{
    m_login = login;
}
const string& Session::getlogin() const
{
    return m_login;
}

istream& operator >>(istream& is, Session& obj)
{
    is >> obj.m_name;
    is >> obj.m_login;
    return is;
}
ostream& operator <<(ostream& os, const Session& obj)
{
    os << obj.m_name;
    os << ' ';
    os << obj.m_login;
    return os;
}
