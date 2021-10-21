//
//  message.cpp
//  Project01
//
//  Created by Ольга Полевик on 21.10.2021.
//

#include <stdio.h>
#include "message.h"
#include <vector>

void Message::setname(const string& name)
{
    m_name = name;
}
const string& Message::getname() const
{
    return m_name;
}

void Message::setmessage(const string& message)
{
    m_message = message;
}
const string& Message::getmessage() const
{
    return m_message;
}

void Message::setreceiver_login(const string& receiver_login)
{
    m_receiver_login = receiver_login;
}
const string& Message::getreceiver_login() const
{
    return m_receiver_login;
}

istream& operator >>(istream& is, Message& obj)
{
    is >> obj.m_name;
    is >> obj.m_message;
    is >> obj.m_receiver_login;
    return is;
}
ostream& operator <<(ostream& os, const Message& obj)
{
    os << obj.m_name;
    os << ' ';
    os << obj.m_message;
    os << ' ';
    os << obj.m_receiver_login;
    os << ' ';
    return os;
}

void displaymessage (ostream & out, const vector <Message> & msg)
{
    for(int i = 0; i < msg.size(); i++)
    {
        const Message& m = msg[i];
        if(m.getreceiver_login().empty())
        {
            out << "From: " << m.getname() << endl << "Text:" << m.getmessage() << endl;
        }
        else
        {
            out << "From: " << m.getname() << endl << "Text:" << m.getmessage() << endl << "To: " << m.getreceiver_login() << endl;
        }
    }
}
