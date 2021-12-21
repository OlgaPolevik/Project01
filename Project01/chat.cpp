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

Chat::Chat( mysqlx::Schema& database )
    : db_messages( database.getTable( "messages" ) )
{
}

void Chat::sendPublicMessage(const Session& session, const string& message_text)
{
    mysqlx::Result result = db_messages
        .insert().values( nullptr, message_text, session.getname() )
        .execute();
    
    assert( result.getWarningsCount() == 0 );
    
    //проверяем активность сессии и если активна то отправить от имени юзера инициатора этой сессии сообщение в общий чат (без указания получателя)
    // Message message;
    // message.setmessage(message_text);
    // message.setname(session.getname());
    // messages.push_back(message);
}

void Chat::sendPrivateMessage(const Session& session, const string& receiver_login, const string& message_text){
    
    mysqlx::Result result = db_messages
        .insert().values( receiver_login, message_text, session.getname() )
        .execute();
    
    assert( result.getWarningsCount() == 0 );
    
    //проевряем активность сессии, наличие логина получателя и отправляем сообщение
    // Message message;
    //message.setmessage(message_text);
    //message.setname(session.getname());
    //message.setreceiver_login(receiver_login); // в мейн спрашиваем у пользователя кому отправить сообщение
    //messages.push_back(message);
}

vector<Message> Chat::readPrivateMessage(const Session& session)
{
    vector<Message> result;
    /*
    for (int i = 0; i < messages.size(); ++i)
    {
         const Message& message = messages[i];
         if (message.getreceiver_login() == session.getlogin())
         {
             result.push_back(message);
         }
     }
     //проходит по массиву сообщений, ищет сообщения в котором нужное имя получателя и возвращает
     */
    
    mysqlx::RowResult rows = db_messages
        .select( "*" )
        .where( "receiver_login = :receiver_login" )
        .bind( "receiver_login", session.getlogin() )
        .execute();
    
    auto data = rows.fetchAll();
    for ( auto row = data.begin(); row != data.end(); ++row )
    // for ( auto row : rows.fetchAll() )
    {
        Message msg;
        msg.setreceiver_login( static_cast<string>( (*row).get( 0 ) ) );
        msg.setmessage( static_cast<string>( (*row).get( 1 ) ) );
        msg.setname( static_cast<string>( (*row).get( 2 ) ) );
        
        result.push_back( std::move( msg ) );
    }
    
    return result;
}

vector<Message> Chat::readPublicMessage(const Session& session)
{
    vector<Message> result;
    
    /*
    for (int i = 0; i < messages.size(); ++i)
    {
        const Message& message = messages[i];
        if (message.getreceiver_login().empty())
        {
            result.push_back(message);
        }
    }
    //проходит по массиву сообщений, ищет сообщения в котором пустое имя получателя и возвращает
    */
    
    mysqlx::RowResult rows = db_messages
        .select( "*" )
        .where( "receiver_login = NULL" )
        .execute();
    
    for ( auto row : rows.fetchAll() )
    {
        Message msg;
        msg.setreceiver_login( static_cast<string>( row.get( 0 ) ) );
        msg.setmessage( static_cast<string>( row.get( 1 ) ) );
        msg.setname( static_cast<string>( row.get( 2 ) ) );
        
        result.push_back( std::move( msg ) );
    }
    
    return result;
}
/*
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
*/
