//
//  chat.h
//  Project01
//
//  Created by Ольга Полевик on 21.10.2021.
//

//класс который отвечает за обмен сообщениями в чате

#ifndef chat_h
#define chat_h

#include <iostream>
#include <string>
#include "session.h"
#include "message.h"
#include <vector>

#include <mysqlx/xdevapi.h>

using namespace std;

class Chat
{
public:
    explicit Chat( mysqlx::Schema& database );
    
    void sendPublicMessage(const Session& session, const string& message_text);
    void sendPrivateMessage(const Session& session, const string& receiver_login, const string& message_text);
    vector<Message> readPrivateMessage(const Session& session);
    vector<Message> readPublicMessage(const Session& session);
    
private:
    //массив сообщений, пара ключ значение или динамический массив структур с тремя полями (отправитель, получатель, текст сообщения)
    //dynamic_array <Message> messages;
    //vector<Message> messages;
    
    mysqlx::Table db_messages;
    
    // friend istream& operator >>(istream& is, Chat& obj);
    // friend ostream& operator <<(ostream& os, const Chat& obj);
};

ostream & operator << (ostream & os, const Chat& chat);
istream & operator >> (istream & is, Chat& chat);

#endif /* chat_h */
