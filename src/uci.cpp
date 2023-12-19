#include <iostream>

#include "uci.h"
#include "yace.h"

UCI UCI::GetInstance()
{
    static UCI sInstance;

    return sInstance;
}

bool UCI::Process( std::pair<std::string, std::string> command )
{
    std::map<std::string, UCICommand>::iterator it = handlers.find( command.first );

    if ( it != handlers.end() )
    {
        auto method = ( *it ).second;
        return (this->*method)( command.second );
    }

    return true;
}

// Command handlers

bool UCI::CommandQuit( std::string arguments )
{
    LOG( "--> quit\n" );
    return false;
}

bool UCI::CommandUci( std::string arguments )
{
    LOG( "--> uci\n" );
    return true;
}