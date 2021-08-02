//
//  main.cpp
//  Project01
//  Итоговый проект по Блоку «Основные конструкции C++»
//

#include <iostream>
#include <string>

using namespace std;

//класс который отвечает за информацию о пользователях чата
class User
{
public:
    User()
    {
        
    }
    ~User()
    {
        
    }
    
    void setlogin(const string& login)
    {
        m_login = login;
    }
    const string& getlogin() const
    {
        return m_login;
    }
    
    void setpassword(const string& password)
    {
        m_password = password;
    }
    const string& getpassword()
    {
        return m_password;
    }
    
    void setname(const string& name)
    {
        m_name = name;
    }
    const string& getname()
    {
        return m_name;
    }
    
private:
    string m_name;
    string m_login;
    string m_password;
};

//класс в котором хранится информация о сессии чата
class Session
{
private:
    string m_login;
    int m_sessionId;
};

//класс который будет отвечать за регистрацию и залогинивание пользователя
class Login
{
public:
    Login()
    {
        
    }
    ~Login()
    {
        
    }
    bool registerUser (const User& newUser)
    {
        //проверка на существующего юзера
        //реализация регистрации
        return true;
    }
    Session loginUser (const string& login, const string& password)
    {
        return Session();
    }
    void logout (const Session& session)
    {
        
    }
private:
    // массив юзеров, или динамический массив или залезть дальше и использовать вектор, что конечно будет гораздо проще
    /*bool isUserExist (const string& login)
     {
        //реализация
        return false;
     };*/
};

// класс (структура) которая содержит имя отправителя и сообщение
class Message
{
public:
    //геттер и сеттер?
private:
    string m_name;
    string m_message;
};

//класс который отвечает за обмен сообщениями в чате
class Chat
{
public:
    void sendPublicMessage(const Session& session, const string& message)
    {
        //проверяем активность сессии и если активна то отправить от имени юзера инициатора этой сессии сообщение в общий чат (без указания получателя)
    }
    void sendPrivateMessage(const Session& session, const string& receiver_login, const string& message){
        //проевряем активность сессии, наличие логина получателя и отправляем сообщение
    }

    Message readPublicMessage(const Session& session)
    {
        //проходит по массиву сообщений, ищет сообщения в котором имя получателя пустое и возвращает его
        return Message();
    }
    Message readPrivateMessage(const Session& session)
    {
        //проходит по массиву сообщений, ищет сообщения в котором нужное имя получателя и возвращает
        return Message();
    }
private:
//массив сообщений, пара ключ значение или динамический массив структур с тремя полями (отправитель, получатель, текст сообщения)
};

int main(int argc, const char * argv[])
{
    setlocale (LC_ALL,"");
    // приветствие
    // 3 кейса свитч на выбор логин, регистрация, и выход
    // если логин спрашивает логин и пароль и отрабатывает Session loginUser и запоминает переменную сессии
    // если регистрация  void registerUser и или регистрирует пользователя или гооврит что такое имя существует и предлагает зарегистрироваться с другим логином
    // выход по какой то кнопке
    // если вход успешен то приветствие и приглашение к вводу сообщения (или приватное или общее) и вариант выхода из сессии но не из чата (три кейса свитч) или if else
    // если приватное сообщение то void sendPrivateMessage
    // если публичное сообщение то void sendPublicMessage
    // вариант выхода из сессии но не из чата - void logout
    // переходим к отображению сообщений
    // если сообщение публичное то оно отображается сразу Message readPublicMessage() и выкидывает к началу кейсов приглашение на ввод сообщения - перелогина или if else
    // если сообщение приватное оно отобразится только у нужного юзера
    
    return 0;
}
