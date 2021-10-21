//
//  server.cpp
//  Project01
//
//  Created by Ольга Полевик on 20.10.2021.
//

#include <stdio.h>
#include "server.h"
#include "user.h"
#include "session.h"
#include "login.h"
#include "message.h"
#include "chat.h"
#include <sys/utsname.h>
#include <fstream>
#include <ostream>
#include <vector>

Server::Server() = default;

void Server::run()
{
    setlocale (LC_ALL,"");
    Login mainlogin;
    Chat mainchat;
    int count = 0;
    // приветствие
      
    utsname utsname;
    uname(&utsname);
    cout << "OS name: " << utsname.sysname << endl;
    cout << "OS version: " << utsname.version << endl;
    cout << endl;
    fstream login_input_file( "users.txt", ios_base::in);
    if ( login_input_file.is_open() )
    {
        login_input_file >> mainlogin;
        login_input_file.close();
    }
        
    fstream chat_input_file( "messages.txt", ios_base::in);
    if ( chat_input_file.is_open() )
    {
        chat_input_file >> mainchat;
        chat_input_file.close();
    }
    
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
                    //cout << mainchat.readPrivateMessage(usersession);
                    displaymessage(cout, mainchat.readPrivateMessage(usersession));
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
                                //cout << mainchat.readPublicMessage(usersession);
                                displaymessage(cout, mainchat.readPublicMessage(usersession));
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
                                        //cout << mainchat.readPrivateMessage(usersession);
                                        displaymessage(cout, mainchat.readPrivateMessage(usersession));
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
    
    fstream login_output_file( "users.txt", ios_base::out);
    login_output_file << mainlogin;
    
    
    fstream chat_output_file( "messages.txt", ios_base::out);
    chat_output_file << mainchat;
    
    cout << "You quit chat" << endl;
}
