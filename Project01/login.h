//
//  login.h
//  Project01
//
//  Created by Ольга Полевик on 21.10.2021.
//

//класс который будет отвечать за регистрацию и залогинивание пользователя

#ifndef login_h
#define login_h

#include <iostream>
#include <string>
#include "user.h"
#include "session.h"
#include <map>

#include <mysqlx/xdevapi.h>

using namespace std;

class Login
{
public:
    explicit Login( mysqlx::Schema& database );
    ~Login();
    //проверка на существующего юзера
    bool isUserExist (const string& login);
    //реализация регистрации
    bool registerUser (const string& name, const string& login, const string& password);
    //инициация сессии активной? или залогинивание юзера
    Session loginUser (const string& login, const string& password);
    //разлогинивание юзера но не выход из чата
    void logout (const Session& session);
    
private:
    // массив юзеров, или динамический массив или залезть дальше и использовать вектор, что конечно будет гораздо проще
    /*dynamic_array <User> users;
    dynamic_array <Session> sessions;*/
    
    // map<string,User> users;
    map<string,Session> sessions;
    
    mysqlx::Table db_users;
    //mysqlx::Table db_sessions;
    
    // friend ostream & operator << (ostream & os, const Login& login);
    // friend istream & operator >> (istream & os, Login& login);
};

ostream& operator << (ostream & os, const Login& login);
istream& operator >> (istream & is, Login& login);

#endif /* login_h */
