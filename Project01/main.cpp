//
//  main.cpp
//  Project01
//  Итоговый проект по Блоку «Основные конструкции C++»
//

#include <iostream>
#include <string>
#include "dynamic_array.h"

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
    const string& getpassword() const
    {
        return m_password;
    }
    
    void setname(const string& name)
    {
        m_name = name;
    }
    const string& getname() const
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
public:
    Session()
    {
        
    }
    ~Session()
    {
        
    }
    void setname(const string& name)
    {
        m_name = name;
    }
    const string& getname() const
    {
        return m_name;
    }
    
    void setlogin(const string& login)
    {
        m_login = login;
    }
    const string& getlogin() const
    {
        return m_login;
    }

private:
    string m_login;
    string m_name;
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
    
    
   /* bool registerUser (const User& newUser)
    {
        return true;
    }*/
    
    //проверка на существующего юзера
    bool isUserExist (const string& login)
     {
         for(int i = 0; i < users.size(); ++i)
         {
             if(users[i].getlogin() == login)
             {
                 return true;
             }
         }
         return false;
     }
    //реализация регистрации
    bool registerUser (const string& name, const string& login, const string& password)
    {
        if (isUserExist(login))
        {
            return false;
        }
        
        User user;
        user.setname(name);
        user.setlogin(login);
        user.setpassword(password);
        users.push_back(user);
        return true;
    }
    //инициация сессии активной? или залогинивание юзера
    Session loginUser (const string& login, const string& password)
    {
        for(int i = 0; i < users.size(); ++i)
        {
            if(users[i].getlogin() == login && users[i].getpassword() == password)
            {
                //coздаем сессию для пользователя у которого совпадают логин и пароль
                Session session;
                session.setlogin(login);
                session.setname(users[i].getname());
                sessions.push_back(session);
                return session;
            }
        }
        return Session();
    }
    //разлогинивание юзера но не выход из чата
    void logout (const Session& session)
    {
        for(int i = 0; i < sessions.size(); ++i)
        {
            if(sessions[i].getlogin() == session.getlogin())
            {
                sessions[i] = Session();
            }
        }
    }
private:
    // массив юзеров, или динамический массив или залезть дальше и использовать вектор, что конечно будет гораздо проще
    dynamic_array <User> users;
    dynamic_array <Session> sessions;
};

// класс (структура) которая содержит имя отправителя и сообщение
class Message
{
public:
    void setname(const string& name)
    {
        m_name = name;
    }
    const string& getname() const
    {
        return m_name;
    }
    
    void setmessage(const string& message)
    {
        m_message = message;
    }
    const string& getmessage() const
    {
        return m_message;
    }
    
    void setreceiver_login(const string& receiver_login)
    {
        m_receiver_login = receiver_login;
    }
    const string& getreceiver_login() const
    {
        return m_receiver_login;
    }
    
    ostream & operator << (ostream & out)
    {
        out << "From: " << m_name << endl << "Text:" << m_message << endl << "To: " << m_receiver_login << endl;
        return out;
    }
private:
    string m_name;
    string m_message;
    string m_receiver_login;
};

//класс который отвечает за обмен сообщениями в чате
class Chat
{
public:
    
    void sendPublicMessage(const Session& session, const string& message_text)
    {
        //проверяем активность сессии и если активна то отправить от имени юзера инициатора этой сессии сообщение в общий чат (без указания получателя)
        Message message;
        message.setmessage(message_text);
        message.setname(session.getname());
        messages.push_back(message);
    }
    void sendPrivateMessage(const Session& session, const string& receiver_login, const string& message_text){
        //проевряем активность сессии, наличие логина получателя и отправляем сообщение
        Message message;
        message.setmessage(message_text);
        message.setname(session.getname());
        message.setreceiver_login(receiver_login); // в мейн спрашиваем у пользователя кому отправить сообщение
        messages.push_back(message);
    }

    dynamic_array<Message> readPrivateMessage(const Session& session)
    {
        dynamic_array<Message> result;
        for (int i = 0; i < messages.size(); ++i)
        {
            const Message& message = messages[i];
            if (message.getreceiver_login() == session.getlogin())
            {
                result.push_back(message);
            }
        }
        //проходит по массиву сообщений, ищет сообщения в котором нужное имя получателя и возвращает
        return result;
    }
    dynamic_array<Message> readPublicMessage(const Session& session)
    {
        dynamic_array<Message> result;
        for (int i = 0; i < messages.size(); ++i)
        {
            const Message& message = messages[i];
            if (message.getreceiver_login().empty())
            {
                result.push_back(message);
            }
        }
        //проходит по массиву сообщений, ищет сообщения в котором пустое имя получателя и возвращает
        return result;
    }
private:
    //массив сообщений, пара ключ значение или динамический массив структур с тремя полями (отправитель, получатель, текст сообщения)
    dynamic_array <Message> messages;
};

int main(int argc, const char * argv[])
{
    setlocale (LC_ALL,"");
    Login mainlogin;
    Chat mainchat;
    int count = 0;
    // приветствие
    cout << "Welcome to chat!" << endl;
    // 3 кейса свитч на выбор логин, регистрация, и выход
    char choice = 0;
    while (true)
    {
        cout << "For login press '1', for registration press '2', and press 'q' to exit : " << endl;
        cin >> choice;
        bool quit = false;
        switch (choice)
        {
            case '1':
                //логин
            {
                cout << "Enter your login: " << endl;
                string login;
                cin >> login;
                cout << "Enter you password: " << endl;
                string password;
                cin >> password;
                Session usersession = mainlogin.loginUser(login, password);
                if (!usersession.getlogin().empty())
                {
                    // если вход успешен то приветствие и приглашение к вводу сообщения (или приватное или общее) и вариант выхода из сессии но не из чата (три кейса свитч) или if else
                    cout << "Hellow " << usersession.getname() << endl;
                    cout << "To send private message press '1', to send private message press '2', to logout press '3' and press 'q' to exit : " << endl;
                    cin >> choice;
                    switch (choice)
                    {
                    case '1':
                        {
                            
                        }
                        break;
                    case '2':
                        {
                                
                        }
                        break;
                    case '3':
                        {
                                    
                        }
                        break;
                    case 'q':
                    // выход по какой то кнопке
                    quit = true;
                    //cout << "You quit chat" << endl;
                    break;
                    default:
                            cout << "You have pressed wrong button " << endl;
                            break;
                            
                    }
                    
                }
                else
                {
                    cout << "Wrong login or password" << endl;
                    count ++;
                    if (count > 3)
                    {
                        quit = true;
                    }
                }
            }
                                
                break;
            case '2':
                // если регистрация  void registerUser и или регистрирует пользователя или гооврит что такое имя существует и предлагает зарегистрироваться с другим логином
            {
                cout << "Enter your login: " << endl;
                string login;
                cin >> login;
                cout << "Enter you password: " << endl;
                string password;
                cin >> password;
                cout << "Enter your name: " << endl;
                string name;
                cin >> name;
                if (mainlogin.registerUser(name, login, password))
                {
                    cout << "you are registered!" << endl;
                }
                else
                {
                    cout << "user exists." << endl;
                }
            }
                break;
            case 'q':
                // выход по какой то кнопке
                quit = true;
                //cout << "You quit chat" << endl;
                break;
            default:
                cout << "You have pressed wrong button " << endl;
                break;
        }
        if (quit)
        {
            break;
        }
    
    
    
   
    // если приватное сообщение то void sendPrivateMessage
    // если публичное сообщение то void sendPublicMessage
    // вариант выхода из сессии но не из чата - void logout
    // переходим к отображению сообщений
    // если сообщение публичное то оно отображается сразу Message readPublicMessage() и выкидывает к началу кейсов приглашение на ввод сообщения - перелогина или if else
    // если сообщение приватное оно отобразится только у нужного юзера
    
    }
    cout << "You quit chat" << endl;
    return 0;
}
