//
//  logger.h
//  Project01
//
//  Created by Ольга Полевик on 22.12.2021.
//

#ifndef logger_h
#define logger_h

#include <iostream>
#include <shared_mutex>
#include <mutex>
#include <chrono>
#include <fstream>

using namespace std;

class LoggerStream
{
public:
    template<typename T>
    LoggerStream& operator << ( const T& data )
    {
        stream << data;
        return *this;
    }
    
    ~LoggerStream();
   
private:
    LoggerStream( ostream& stream, shared_mutex& mutex );

    friend class Logger;
    
    ostream& stream;
    unique_lock<shared_mutex> lock;
};

class Logger
{
public:
    Logger();
    
    LoggerStream log()
    {
        return LoggerStream( file, mutex );
    }
    
private:
    fstream file;
    shared_mutex mutex;
};

#endif /* logger_h */
