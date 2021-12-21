//
//  server.h
//  Project01
//
//  Created by Ольга Полевик on 20.10.2021.
//

#ifndef server_h
#define server_h

#include <sys/socket.h>
#include <arpa/inet.h>

#include <mysqlx/xdevapi.h>

#include "login.h"
#include "chat.h"

#define MESSAGE_BUFFER 1024 // Максимальный размер буфера для приема и передачи
#define CHAT_PORT 7777 // Номер порта, который будем использовать для приема и передачи

class Server
{
public:
    Server();
    ~Server();
    
    void run();
    void run2();
    
private:
    char buffer[MESSAGE_BUFFER];
    char message[MESSAGE_BUFFER];
    int socket_file_descriptor;
    struct sockaddr_in serveraddress, client;
    
    mysqlx::Session mysql_session;
    mysqlx::Schema mysql_database;

    Login mainlogin;
    Chat mainchat;
    
    void send( const std::string& data );
    std::string receive();
};


#endif /* server_h */
