//
//  session.h
//  Project01
//
//  Created by Ольга Полевик on 20.10.2021.
//

//класс в котором хранится информация о сессии чата

#ifndef session_h
#define session_h

#include <iostream>
#include <string>

using namespace std;

class Session
{
public:
    Session();
    ~Session();
    
    void setname(const string& name);
    const string& getname() const;
    void setlogin(const string& login);
    const string& getlogin() const;

private:
    string m_login;
    string m_name;
    
    friend istream& operator >>(istream& is, Session& obj);
    friend ostream& operator <<(ostream& os, const Session& obj);
};

istream& operator >>(istream& is, Session& obj);
ostream& operator <<(ostream& os, const Session& obj);

#endif /* session_h */
