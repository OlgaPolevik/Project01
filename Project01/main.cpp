//
//  main.cpp
//  Project01
//  Итоговый проект по Блоку «Основные конструкции C++»
//

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <map>
//#include "dynamic_array.h"

using namespace std;

//класс который отвечает за информацию о пользователях чата
class User
{
public:
    /* User()
    {
        
    }
    ~User()
    {
        
    }*/
    User() = default;
    User(const string& login, const string& password, const string& name) : m_name(name), m_login(login), m_password(password)
    {
        
    }
    ~User() = default;
    
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
    /*Session()
    {
        
    }
    ~Session()
    {
        
    }*/
    Session() = default;
    ~Session() = default;
    
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
    /*Login()
    {
        
    }
    ~Login()
    {
        
    }*/
    Login() = default;
    ~Login() = default;
    //проверка на существующего юзера
    bool isUserExist (const string& login)
     {
         /*for(int i = 0; i < users.size(); ++i)
         {
             if(users[i].getlogin() == login)
             {
                 return true;
             }
         }
         return false;*/
         return users.count(login) != 0;
     }
    //реализация регистрации
    bool registerUser (const string& name, const string& login, const string& password)
    {
        if (isUserExist(login))
        {
            return false;
        }
        if (users.size() == 3)
        {
            throw exception();
        }
        /*User user;
        user.setname(name);
        user.setlogin(login);
        user.setpassword(password);
        */
        User user(name, login, password);
        //users.push_back(user);
        users.emplace(login,user);
        return true;
    }
    //инициация сессии активной? или залогинивание юзера
    Session loginUser (const string& login, const string& password)
    {
       /* for(int i = 0; i < users.size(); ++i)
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
        return Session();*/
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
    void logout (const Session& session)
    {
        /*for(int i = 0; i < sessions.size(); ++i)
        {
            if(sessions[i].getlogin() == session.getlogin())
            {
                sessions[i] = Session();
            }
        }*/
        sessions.erase(session.getlogin());
    }
private:
    // массив юзеров, или динамический массив или залезть дальше и использовать вектор, что конечно будет гораздо проще
    /*dynamic_array <User> users;
    dynamic_array <Session> sessions;*/
    map<string,User> users;
    map<string,Session> sessions;
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
    
   
private:
    string m_name;
    string m_message;
    string m_receiver_login;
};

template<class Data>
ostream& operator << (ostream& out, const vector<Data>& a )
{
    for (int i = 0; i < a.size(); ++i)
    {
        out << a[i] << endl;
    }
    return out;
}
ostream & operator << (ostream & out, const Message & m)
{
    if(m.getreceiver_login().empty())
    {
        out << "From: " << m.getname() << endl << "Text:" << m.getmessage() << endl;
        return out;
    }
    else
    {
        out << "From: " << m.getname() << endl << "Text:" << m.getmessage() << endl << "To: " << m.getreceiver_login() << endl;
        return out;
    }
}

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

   /* dynamic_array<Message> readPrivateMessage(const Session& session)
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
    }*/
    
    vector<Message> readPrivateMessage(const Session& session)
     {
         vector<Message> result;
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
    
    /*dynamic_array<Message> readPublicMessage(const Session& session)
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
    }*/
    vector<Message> readPublicMessage(const Session& session)
    {
        vector<Message> result;
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
    //dynamic_array <Message> messages;
    vector<Message> messages;
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
                    // если сообщение приватное оно отобразится только у нужного юзера
                    cout << mainchat.readPrivateMessage(usersession);
                    while (true)
                    {
                        cout << "To send private message press '1', to send public message press '2', to logout press '3' and press 'q' to exit : " << endl;
                        cin >> choice;
                        switch (choice)
                        {
                            case '1':
                            {
                                // если приватное сообщение то void sendPrivateMessage
                                cout << "Enter receiver login: " << endl;
                                string receiver_login;
                                cin >> receiver_login;
                                cin.ignore(INT_MAX, '\n');
                                cout << "Enter you message: " << endl;
                                string message_text;
                                getline(cin, message_text);
                                mainchat.sendPrivateMessage(usersession, receiver_login, message_text);
                            }
                                break;
                            case '2':
                            {
                                // если публичное сообщение то void sendPublicMessage
                                cin.ignore(INT_MAX, '\n');
                                cout << "Enter you message: " << endl;
                                string message_text;
                                getline(cin, message_text);
                                mainchat.sendPublicMessage(usersession, message_text);
                                // если сообщение публичное то оно отображается сразу Message readPublicMessage() и выкидывает к началу кейсов приглашение на ввод сообщения - перелогина или if else
                                cout << mainchat.readPublicMessage(usersession);
                            }
                                break;
                            case '3':
                            {
                                // вариант выхода из сессии но не из чата - void logout
                                mainlogin.logout (usersession);
                                cout << "You logout " << endl;
                                cout << "Press 'y' if you want to login or 'n' to quit " << endl;
                                cin >> choice;
                                if(choice == 'y')
                                {
                                    cout << "Enter your login: " << endl;
                                    string login;
                                    cin >> login;
                                    cout << "Enter you password: " << endl;
                                    string password;
                                    cin >> password;
                                    Session usersession = mainlogin.loginUser(login, password);
                                    if(usersession.getlogin().empty())
                                    {
                                        cout << "You entered wrong data!" << endl;
                                        quit = true;
                                    }
                                    else
                                    {
                                        usersession = mainlogin.loginUser(login, password);
                                        cout << "Hellow " << usersession.getname() << endl;
                                        // если сообщение приватное оно отобразится только у нужного юзера
                                        cout << mainchat.readPrivateMessage(usersession);
                                    }
                                }
                                else if (choice == 'n')
                                {
                                    quit = true;
                                }
                                else
                                {
                                    cout << "You have pressed wrong button " << endl;
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
                try
                {
                    if (mainlogin.registerUser(name, login, password))
                    {
                        cout << "you are registered!" << endl;
                    }
                    else
                    {
                        cout << "user exists." << endl;
                    }
                }
                catch (exception &ex)
                {
                    cout << "User limit reached!" << endl;
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
    }
    cout << "You quit chat" << endl;
    return 0;
}
