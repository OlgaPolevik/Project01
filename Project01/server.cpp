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

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <sstream>

using namespace std;

Server::Server()
    : mysql_session( "localhost", 33060, "root", "" )
    , mysql_database( mysql_session.getSchema( "chat" ) )
    , mainlogin( mysql_database )
    , mainchat( mysql_database )
{
    setlocale (LC_ALL,"");
    
    /*
    
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
     */
}

Server::~Server()
{
    /*
    fstream login_output_file( "users.txt", ios_base::out);
    login_output_file << mainlogin;
    
    fstream chat_output_file( "messages.txt", ios_base::out);
    chat_output_file << mainchat;
    */
}

void Server::run2()
{
    // Создадим UDP сокет
    socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим порт для соединения
    serveraddress.sin_port = htons(CHAT_PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    if ( ::bind( socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof( serveraddress ) ) != 0 )
    {
        cout << "Unable to bind socket." << endl;
        exit( -1 );
    }
    
    while( 1 )
    {
        // NOTE: Выполняем в run() цикл общения с клиентом. Цикл должен состоять
        // из последовательности операций:
        // 1) читаем из сокета сообщение от клиента
        // 2) обрабатываем соощение от клиента
        // 3) отправляем в сокет ответ клиенту
        // 4) прерываем цикл, ЕСЛИ клиент запросил завершение, ИНАЧЕ переходим на п.1
        run();
    }

    // закрываем сокет, завершаем соединение
    cout << "Server is quitting..." << endl;
    close(socket_file_descriptor);
}

void Server::run()
{
    int count = 0;
    // приветствие
      
    /*utsname utsname;
    uname(&utsname);
    cout << "OS name: " << utsname.sysname << endl;
    cout << "OS version: " << utsname.version << endl;
    cout << endl;*/
    
    // 3 кейса свитч на выбор логин, регистрация, и выход
    char choice = 0;
    while (true)
    {
        // cout << "For login press '1', for registration press '2', and press 'q' to exit : " << endl;
        {
            receive();
            std::ostringstream os;
            os << "For login press '1', for registration press '2', and press 'q' to exit : " << endl;
            send( os.str() );
        }
        
        // cin >> choice;
        {
            std::string input = receive();
            choice = input[0];
        }

        bool quit = false;
        switch (choice)
        {
            case '1':
                //логин
            {
                // cout << "Enter your login: " << endl;
                {
                    std::ostringstream os;
                    os << "Enter your login: " << endl;
                    send( os.str() );
                }
                
                string login;
                // cin >> login;
                {
                    login = receive();
                }
                
                // cout << "Enter you password: " << endl;
                {
                    std::ostringstream os;
                    os << "Enter your password: " << endl;
                    send( os.str() );
                }
                
                string password;
                // cin >> password;
                {
                    password = receive();
                }
                
                Session usersession = mainlogin.loginUser(login, password);
                if (!usersession.getlogin().empty())
                {
                    // если вход успешен то приветствие и приглашение к вводу сообщения (или приватное или общее) и вариант выхода из сессии но не из чата (три кейса свитч) или if else
                    // cout << "Hellow " << usersession.getname() << endl;
                    {
                        std::ostringstream os;
                        os << "Hello " << usersession.getname() << endl;
                        displaymessage(os, mainchat.readPrivateMessage(usersession));
                        os << "Press a key" << endl;
                        send( os.str() );
                    }

                    // если сообщение приватное оно отобразится только у нужного юзера
                    //cout << mainchat.readPrivateMessage(usersession);
                    // displaymessage(cout, mainchat.readPrivateMessage(usersession));

                    bool quit = false;
                    while (true)
                    {
                        // cout << "To send private message press '1', to send public message press '2', to logout press '3' and press 'q' to exit : " << endl;
                        {
                            receive();
                            std::ostringstream os;
                            os << "To send private message press '1', to send public message press '2', to logout press '3' and press 'q' to exit : " << endl;
                            send( os.str() );
                        }
                        
                        // cin >> choice;
                        {
                            std::string input = receive();
                            choice = input[0];
                        }
                        
                        switch (choice)
                        {
                            case '1':
                            {
                                // если приватное сообщение то void sendPrivateMessage
                                //cout << "Enter receiver login: " << endl;
                                {
                                    std::ostringstream os;
                                    os << "Enter receiver login: " << endl;
                                    send( os.str() );
                                }
                                
                                string receiver_login;
                                //cin >> receiver_login;
                                {
                                    receiver_login = receive();
                                }
                                //cin.ignore(INT_MAX, '\n');
                                
                                //cout << "Enter you message: " << endl;
                                {
                                    std::ostringstream os;
                                    os << "Enter you message: " << endl;
                                    send( os.str() );
                                }
                                string message_text;
                                
                                //getline(cin, message_text);
                                
                                {
                                    message_text = receive();
                                }
                                mainchat.sendPrivateMessage(usersession, receiver_login, message_text);
                                {
                                    std::ostringstream os;
                                    os << "Message sent." << endl;
                                    os << "Press a key" << endl;
                                    send( os.str() );
                                }
                                
                            }
                                break;
                                
                            case '2':
                            {
                                // если публичное сообщение то void sendPublicMessage
                                // cin.ignore(INT_MAX, '\n');
                                //cout << "Enter you message: " << endl;
                                {
                                    std::ostringstream os;
                                    os << "Enter you message: " << endl;
                                    send( os.str() );
                                }
                                string message_text;
                                
                                //getline(cin, message_text);
                                {
                                    message_text = receive();
                                }
                                mainchat.sendPublicMessage(usersession, message_text);
                                // если сообщение публичное то оно отображается сразу Message readPublicMessage() и выкидывает к началу кейсов приглашение на ввод сообщения - перелогина или if else
                                //cout << mainchat.readPublicMessage(usersession);
                                //displaymessage(cout, mainchat.readPublicMessage(usersession));
                                {
                                   
                                    std::ostringstream os;
                                    displaymessage(os, mainchat.readPublicMessage(usersession));
                                    os << "Press a key" << endl;
                                    send( os.str() );
                                }
                            }
                            

                                break;
                            case '3':
                            {
                                // вариант выхода из сессии но не из чата - void logout
                                mainlogin.logout (usersession);
                                //cout << "You logout " << endl;
                                {
                                    std::ostringstream os;
                                    os << "You logout \n Press 'y' if you want to login or 'n' to quit " << endl;
                                    send( os.str() );
                                }
                                
                                //cout << "Press 'y' if you want to login or 'n' to quit " << endl;
                                
                                //cin >> choice;
                                {
                                    std::string input = receive();
                                    choice = input[0];
                                }
                                
                                if(choice == 'y')
                                {
                                    //cout << "Enter your login: " << endl;
                                    {
                                        std::ostringstream os;
                                        os << "Enter your login: " << endl;
                                        send( os.str() );
                                    }
                                    string login;
                                    
                                   // cin >> login;
                                    {
                                        login = receive();
                                    }
                                    //cout << "Enter you password: " << endl;
                                    
                                    {
                                        std::ostringstream os;
                                        os << "Enter you password: " << endl;
                                        send( os.str() );
                                    }
                                    
                                    string password;
                                    //cin >> password;
                                    {
                                        password = receive();
                                    }
                                    
                                    Session usersession = mainlogin.loginUser(login, password);
                                    if(usersession.getlogin().empty())
                                    {
                                        //cout << "You entered wrong data!" << endl;
                                        {
                                            std::ostringstream os;
                                            os << "You entered wrong data!" << endl;
                                            os << "Press a key" << endl;
                                            send( os.str() );
                                        }
                                        quit = true;
                                    }
                                    else
                                    {
                                        usersession = mainlogin.loginUser(login, password);
                                        //cout << "Hello " << usersession.getname() << endl;
                                        
                                        
                                        // если сообщение приватное оно отобразится только у нужного юзера
                                        //cout << mainchat.readPrivateMessage(usersession);
                                        //displaymessage(cout, mainchat.readPrivateMessage(usersession));
                                        {
                                            std::ostringstream os;
                                            os << "Hello" << endl;
                                            displaymessage(os, mainchat.readPrivateMessage(usersession));
                                            os << "Press a key" << endl;
                                            send( os.str() );
                                        }
                                    }
                                }
                                else if (choice == 'n') // if(choice == 'y')
                                {
                                    quit = true;
                                    // Отправить что-то клиенту
                                    {
                                        std::ostringstream os;
                                        os << "You are quit" << endl;
                                        os << "Press a key" << endl;
                                        send( os.str() );
                                    }
                                }
                                else
                                {
                                    //cout << "You have pressed wrong button " << endl;
                                    {
                                        std::ostringstream os;
                                        os << "You have pressed wrong button " << endl;
                                        os << "Press a key" << endl;
                                        send( os.str() );
                                    }
                                }
                            }
                                break;
                            case 'q':
                                // выход по какой то кнопке
                                quit = true;
                                //Отправить что-то
                                
                                {
                                    std::ostringstream os;
                                    os << "Quit" << endl;
                                    os << "Press a key" << endl;
                                    send( os.str() );
                                }
                                
                                //cout << "You quit chat" << endl;
                                break;
                            default:
                                //cout << "You have pressed wrong button " << endl;
                            {
                                std::ostringstream os;
                                os << "You have pressed wrong button " << endl;
                                os << "Press a key" << endl;
                                send( os.str() );
                            }
                                break;
                            } // switch
                            if (quit)
                            {
                                break;
                            }
                        } // while (true)
                    }
                    else // if (!usersession.getlogin().empty())
                    {
                        // cout << "Wrong login or password" << endl;
                        {
                            std::ostringstream os;
                            os << "Wrong login or password" << endl;
                            os << "Press a key" << endl;
                            send( os.str() );
                        }
                        
                        count ++;
                        if (count > 3)
                        {
                            quit = true;
                        }
                    }
            } // case '1':
                break;
            case '2':
                // если регистрация  void registerUser и или регистрирует пользователя или гооврит что такое имя существует и предлагает зарегистрироваться с другим логином
            {
                //cout << "Enter your login: " << endl;
                {
                    std::ostringstream os;
                    os << "Enter your login: " << endl;
                    send( os.str() );
                }
                string login;
                //cin >> login;
                {
                    login = receive();
                }
                
                //cout << "Enter you password: " << endl;
                {
                    std::ostringstream os;
                    os << "Enter you password: " << endl;
                    send( os.str() );
                }
                string password;
                //cin >> password;
                {
                    password = receive();
                }
                //cout << "Enter your name: " << endl;
                {
                    std::ostringstream os;
                    os << "Enter your name: " << endl;
                    send( os.str() );
                }
                string name;
                //cin >> name;
                {
                    name = receive();
                }
                try
                {
                    if (mainlogin.registerUser(name, login, password))
                    {
                        //cout << "you are registered!" << endl;
                        {
                            std::ostringstream os;
                            os << "you are registered!" << endl;
                            os << "Press a key" << endl;
                            send( os.str() );
                        }
                    }
                    else
                    {
                        //cout << "user exists." << endl;
                        {
                            std::ostringstream os;
                            os << "user exists." << endl;
                            os << "Press a key" << endl;
                            send( os.str() );
                        }
                    }
                }
                catch (exception &ex)
                {
                    //cout << "User limit reached!" << endl;
                    {
                        std::ostringstream os;
                        os << "User limit reached!" << endl;
                        os << "Press a key" << endl;
                        send( os.str() );
                    }
                }
            }
                break;
            case 'q':
                // выход по какой то кнопке
                quit = true;
                //cout << "You quit chat" << endl;
                {
                    std::ostringstream os;
                    os << "c";
                    send( os.str() );
                }
                break;
            default:
                //cout << "You have pressed wrong button " << endl;
                {
                    std::ostringstream os;
                    os << "You have pressed wrong button " << endl;
                    os << "Press a key" << endl;
                    send( os.str() );
                }
                break;
        }
        if (quit)
        {
            break;
        }
    } // while( 1 )
    
    //cout << "You quit chat" << endl;
    /*{
        std::ostringstream os;
        os << "You quit chat" << endl;
        send( os.str() );
    }*/
}

void Server::send( const std::string& data )
{
    strncpy(message, data.c_str(),MESSAGE_BUFFER);
    sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));

    cout << "server=>client: " << data << endl;
}

std::string Server::receive()
{
    // Длина сообщения от клиента
    socklen_t length = sizeof(client);
    ssize_t message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &length);
    buffer[message_size] = '\0';
    
    cout << "client=>server: " << buffer << endl;
    
    return buffer;
}
