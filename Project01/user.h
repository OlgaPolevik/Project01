//
//  user.h
//  Project01
//
//  Created by Ольга Полевик on 20.10.2021.
//

//класс который отвечает за информацию о пользователях чата

#ifndef user_h
#define user_h

#include <iostream>
#include <string>

using namespace std;

class User
{
public:
    User();
    User(const string& login, const string& password, const string& name); 
    ~User();
    
    void setlogin(const string& login);
    const string& getlogin() const;
    void setpassword(const string& password);
    const string& getpassword() const;
    void setname(const string& name);
    const string& getname() const;

private:
    string m_name;
    string m_login;
    string m_password;
    
    friend istream& operator >>(istream& is, User& obj);
    friend ostream& operator <<(ostream& os, const User& obj);
};

istream& operator >>(istream& is, User& obj);
ostream& operator <<(ostream& os, const User& obj);

#endif /* user_h */
