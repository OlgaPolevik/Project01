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

using namespace std;




int main(int argc, const char * argv[])
{
    Server server;
    server.run();
    
    return 0;
}
