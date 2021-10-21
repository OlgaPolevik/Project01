//
//  message.h
//  Project01
//
//  Created by Ольга Полевик on 21.10.2021.
//

// класс (структура) которая содержит имя отправителя и сообщение

#ifndef message_h
#define message_h

#include <iostream>
#include <string>

using namespace std;

class Message
{
public:
    void setname(const string& name);
    const string& getname() const;
    void setmessage(const string& message);
    const string& getmessage() const;
    void setreceiver_login(const string& receiver_login);
    const string& getreceiver_login() const;
   
private:
    string m_name;
    string m_message;
    string m_receiver_login;
    
    friend istream& operator >>(istream& is, Message& obj);
    friend ostream& operator <<(ostream& os, const Message& obj);
};

istream& operator >>(istream& is, Message& obj);
ostream& operator <<(ostream& os, const Message& obj);
void displaymessage (ostream & out, const vector <Message> & msg);

#endif /* message_h */
