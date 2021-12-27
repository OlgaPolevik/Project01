//
//  logger.cpp
//  Project01
//
//  Created by Ольга Полевик on 22.12.2021.
//

#include <stdio.h>
#include "logger.h"

Logger::Logger()
    : file( "log.txt", ios_base::out )
{
}

LoggerStream::~LoggerStream()
{
    stream << endl;
}

LoggerStream::LoggerStream( ostream& stream, shared_mutex& mutex )
    : stream( stream )
    , lock( mutex )
{
    time_t now = chrono::system_clock::to_time_t( chrono::system_clock::now() );
    
    stream << "[" << put_time( localtime( &now ), "%F %T" ) << "]: ";
}
