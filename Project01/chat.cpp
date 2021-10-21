//
//  chat.cpp
//  Project01
//
//  Created by Ольга Полевик on 21.10.2021.
//

#include <stdio.h>
#include "chat.h"
#include <vector>
#include "session.h"
#include "message.h"

void Chat::sendPublicMessage(const Session& session, const string& message_text)
{
    //проверяем активность сессии и если активна то отправить от имени юзера инициатора этой сессии сообщение в общий чат (без указания получателя)
    Message message;
    message.setmessage(message_text);
    message.setname(session.getname());
    messages.push_back(message);
}
void Chat::sendPrivateMessage(const Session& session, const string& receiver_login, const string& message_text){
    //проевряем активность сессии, наличие логина получателя и отправляем сообщение
    Message message;
    message.setmessage(message_text);
    message.setname(session.getname());
    message.setreceiver_login(receiver_login); // в мейн спрашиваем у пользователя кому отправить сообщение
    messages.push_back(message);
}
vector<Message> Chat::readPrivateMessage(const Session& session)
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
vector<Message> Chat::readPublicMessage(const Session& session)
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

ostream & operator << (ostream & os, const Chat& chat )
{
    os << chat.messages.size() << endl;
    for(const auto & m : chat.messages)
    {
        os << m;
    }
    return os;
}

istream & operator >> (istream & is, Chat& chat )
{
    size_t messages_count;
    
    is >> messages_count;
    
    for(int i = 0; i < messages_count; i++)
    {
        Message m;
        is >> m;
        chat.messages.emplace_back(m);
    }
    
    return is;
}
