Итоговый проект по Блоку «Основные конструкции C++»

над заданием работали  Ольга Полевик и Евгений Rock
Одна из двух реализаций задания, Евгений Rock поделится своим 
В данной работе он принимал участие в разработке общей логики программы и в реализации части логина, регистрации и проверки на существующего пользователя, а также идеи насчет того где можно использовать исключения

*Описание программы*

Программа представляет собой реализацию простого чата с возможностью регистрации, входа, выхода пользователя из чата, а так же с возможностью перелогинивания (завершения конкретной активной сессии) без выхода из чата. 

Классы User, Session, Message - предсталяют собой структуры для хранения информации о пользователе, активной сесии и сообщении

Класс Login отвечает за регистрацию (bool registerUser), вход (открытие активной сессии) (Session loginUser),  проверку существующего пользователя (bool isUserExist) и завершение сессии без выхода из чата (void logout).  

Класс Chat отвечает за ввод публичных (void sendPublicMessage) и приватных (void sendPrivateMessage) сообщений и отображение публичных (dynamic_array<Message> readPublicMessage) и приватных (dynamic_array<Message> readPrivateMessage) сообщений

Отдельно реализован шаблон класса dynamic_array - динамического массива для классов User, Session, Message

Реализована перегрузка оператора ввода для шаблона динамического массива и отдельно для класса Message

Функционал программы подразумевает ограничение на количество зарегистрированных пользователей и реализовано исключение при попытке зарегистрироваться сверх указанного лимита.

Дополнительный функционал - ограничение на ввод корректных данных при входе (логин и пароль), дается три попытки, если они неудачны то чат завершает работу (выход из чата)

*Дополнения№1*

В программе использованы библиотеки STL 
vector (для класса сообщений message вместо динамического массива)
map (для классов Session и Login)

*Дополнения№2*

исправлена ошибка с сессией (вызод из чата если введены некорректные данные логин и пароль)

учтены замечания (реализован конструктор прсиваивания (в целях практики, на данный момент он не используется, как и динамический массив), исправлены конструкторы user, использована другая форма записи пустых конструкторов и деструкторов (через default))

*Дополнения№3*

сделаны мелкие исправления которые требовал компиллятор g++, сделан файл makefile с синтетическими целями

*Дополнения№4*

добавлены системные вызовы - 19 модуль

*Дополнения№5*

реализована запись в файлы users.txt и messages.txt
для этого переделана и добавлена перегрузка операторов ввода вывода и добавлена функуция, а не оператор, чтения сообщений
 
 *Дополнения от 21.10.2021*
 
 Выделены отдельно файлы для классов chat, message, login, session, user, и создан класс server
 
 *Дополнения от 02.11.2021*
 
В данном проекте реализована серверная часть чата с использованием протокола UDP, обмен данными на уровне сервер-клиент, многопоточность не реализована; работоспособность программы проверена на MacOS, потенциально работоспособна на UNIX. 
TODO: реализовать сохранение файлов с данными пользователя и сообщениями, на данный момент программа использует существующие данные, но новые данные не сохраняет и файлы не перезаписывает

 *Дополнения от 21.12.2021*
 
 Реализовано хранение некоторых данных чата в базе данных, архитектура клиент-сервер
 1. В server: устанавливается соединение с сервером mysql, с БД "chat"
 2. В login: реализовано хранение данных пользователя в таблице users
 3. В chat: реализовано хранение приватных сообщений в таблице messages
 
 OC MacOs, потенциально работоспособна под Linux,
 
 Makefile:
 g++ -o chat main.cpp chat.cpp login.cpp message.cpp server.cpp session.cpp user.cpp -x -Wall -Wextra -fpermissive

(Спасибо Ментор SF Андрей Золотых, который добавил его для сборки и проверки под Linux) 
 
 TODO: учесть замечания к заданиям 18 и 20 модуля
 
 *Дополнения от 28.12.2021*
 
 Реализован логер, который позволяет формировать записи с помощью операторов вывода стрим, который может формировать несколько строк из разных потоков без гонки данных, используя мьютекс (logger.h, logger.cpp)
 
  Makefile:
 g++ -o chat main.cpp chat.cpp login.cpp message.cpp server.cpp session.cpp user.cpp -x -Wall -Wextra -fpermissive

(Спасибо Ментор SF Андрей Золотых, который добавил его для сборки и проверки под Linux) 

! в мейкфайл добавить файлы logger.h, logger.cpp
 
 TODO: учесть замечания к заданиям 16, 18 и 20 модуля
  
16:
  
 Плюсы:
* Код собирается на Linux;
* Код запускается;
* Корректно выводит русские символы;
* Отправка приватных сообщений.

Недочеты:
* Некорректный имя отправителя.
Шаги:
Зарегистрировал 2ух пользователей с именами "aa", "bb".
aa отправил приватное сообщение bb и публичное сообщение.
bb отправил публичное сообщение аа.
"Hellow aa
To send private message press '1', to send public message press '2', to logout press '3' and press 'q' to exit :
1
Enter receiver login:
bb
Enter you message:
privet
To send private message press '1', to send public message press '2', to logout press '3' and press 'q' to exit :
2
Enter you message:
public
From: aa
Text:public
To send private message press '1', to send public message press '2', to logout press '3' and press 'q' to exit :
3
You logout
Press 'y' if you want to login or 'n' to quit
y
Enter your login:
bb
Enter you password:
bb
Hellow bb
From: aa
Text:privet
To: bb
To send private message press '1', to send public message press '2', to logout press '3' and press 'q' to exit :
2
Enter you message:
privet, all
From: aa
Text:public
From: aa ----- вот здесь ожидается пользователь bb.
Text:privet, all"

* Не показываются публичные сообщения при логине.
Шаги:
Зарегистрировались под пользователем 1. Он отправляет публичное сообщение. Логинимся под другим пользователем.
Ожидание: выводится публичное сообщение
Реальность: отсутствие.
Либо не хватает пункта в меню для вывода сообщений принадлежавшие пользователю.

* Странное ограничение на кол-во пользователей. Можно зарегистрировать только 3 пользователя.
* Для чего потребовалось узнавать ОС? Код не собирается на Windows.
* https://github.com/OlgaPolevik/Project01/blob/master/Project01/main.cpp#L687 - std::exception - слишком абстрактный для суждения о превышении лимита пользователей. https://github.com/OlgaPolevik/Project01/blob/master/Project01/main.cpp#L689. Для этого нужно было создавать отдельный класс исключений. Например, DuplicateUserException.
* registerUser - сообщает 2мя разными способами о своем результате: возвращает bool, кидает исключение. Нужно было выбрать что то одно. Если возвращает результат, то это через Enum, если состаяний больше 2. Либо исключения.


Плюсы:
* Данные инкапсулированы.
* Логика разбита на функции.

Замечания:
* Код не разбит на файлы. Все в одном файле. За это снизил балл.
* Нарушено правило 0,3,5 https://en.cppreference.com/w/cpp/language/rule_of_three. Для Users, Session, etc.
* В задании на проверку временного кода не должно быть. https://github.com/OlgaPolevik/Project01/blob/master/Project01/main.cpp#L165
* Опечатка "Hellow";

Пожелания:
* Использовать range-based for loop. https://en.cppreference.com/w/cpp/language/range-for
* https://github.com/OlgaPolevik/Project01/blob/master/Project01/main.cpp#L178 использовать auto в этом случае.

18:

Небольшие предложения по улучшению кода:
1. Когда вы задавали права доступа к файлу, то сделали это правильно
system("chmod 600 messages.txt");
Но можно это делать один раз в программе (например, при после первого обращения, после message_file_load, остальные обращения write и read не изменяют права на файлы, поэтому chmod уже вызывать не требуется)

2. В коде чата есть такой фрагмент:
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

Тут есть 2 момента:
1) вы объявляете 3 переменных с тем же именем, которые уже объявлены ранее login, password, usersession. Это нехорошо, лучше сделать переменные с новым именем, чтобы не было пересечений
2) эти три переменные будут автоматически уничтожены после выхода из оператора if внутри которого они объявлены и их значения станут недоступны. Тут возможно надо проверить такую ли логику вы хотели запрограммировать в этом случае.

20:

В Makefile добавил

g++ -o chat main.cpp chat.cpp login.cpp message.cpp server.cpp session.cpp user.cpp -x -Wall -Wextra -fpermissive

Из файла main.cpp из всего этого списка лучше оставить только #include "server.h" (ведь только этот заголовочный файл нужен, т.е. правило такое файлы инкудить только те, которые используются в данной единице компиляции – единица компиляции – это файлы cpp. На размер программы это не влияет, просто так удобнее для чтения. Смотришь, что подключено и понимаешь, что делает данный модуль программы) Это относится и к другим cpp файлам.
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <map>
#include <climits>
#include <cstdlib>
#include <stdlib.h>
#include <sys/utsname.h>
#include <fstream>
#include <ostream>
#include "user.h"
#include "server.h"
#include "session.h"
#include "login.h"
#include "message.h"
#include "chat.h"

В заголовочных файлах всё лучше вместо
#ifndef user_h
#define user_h

#pragma once – это более в стиле С++ и строк на две меньше

В классе Server.h желательно проинициализировать поля класса.
Сделать это лучше всего так:
char buffer[MESSAGE_BUFFER]{};
char message[MESSAGE_BUFFER]{};
int socket_file_descriptor{};
struct sockaddr_in serveraddress{}, client{};
Вот эти варнинги лучше элиминировать объявляя не int i а size_t i
chat.cpp:33:24: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<Message>::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
33 | for (int i = 0; i < messages.size(); ++i)
| ~~^~~~~~~~~~~~~~~~~
chat.cpp: In member function ‘std::vector<Message> Chat::readPublicMessage(const Session&)’:
chat.cpp:47:23: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<Message>::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
47 | for (int i = 0; i < messages.size(); ++i)
| ~~^~~~~~~~~~~~~~~~~
chat.cpp: In function ‘std::istream& operator>>(std::istream&, Chat&)’:
chat.cpp:75:22: warning: comparison of integer expressions of different signedness: ‘int’ and ‘size_t’ {aka ‘long unsigned int’} [-Wsign-compare]
75 | for(int i = 0; i < messages_count; i++)
| ~~^~~~~~~~~~~~~~~~
login.cpp: In function ‘std::istream& operator>>(std::istream&, Login&)’:
login.cpp:82:22: warning: comparison of integer expressions of different signedness: ‘int’ and ‘size_t’ {aka ‘long unsigned int’} [-Wsign-compare]
82 | for(int i = 0; i < users_count; i++)
| ~~^~~~~~~~~~~~~
login.cpp:93:22: warning: comparison of integer expressions of different signedness: ‘int’ and ‘size_t’ {aka ‘long unsigned int’} [-Wsign-compare]
93 | for(int i = 0; i < sessions_count; i++)
| ~~^~~~~~~~~~~~~~~~
message.cpp: In function ‘void displaymessage(std::ostream&, const std::vector<Message>&)’:
message.cpp:59:22: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<Message>::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
59 | for(int i = 0; i < msg.size(); i++)
| ~~^~~~~~~~~~~~
