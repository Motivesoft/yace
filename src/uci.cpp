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
    LOG( "Processing %s\n", command.first.c_str() );

    std::map<std::string, UCICommand>::iterator it = handlers.find( command.first );

    if ( it != handlers.end() )
    {
        auto method = ( *it ).second;
        return (this->*method)( command.second );
    }

    return true;
}

// Command handlers

bool UCI::CommandPerft( std::string arguments )
{
    LOG( "--> perft\n" );
    return true;
}

bool UCI::CommandQuit( std::string arguments )
{
    LOG( "--> quit\n" );

    // TODO shutdown internal threads etc

    return false;
}

bool UCI::CommandUci( std::string arguments )
{
    LOG( "--> uci\n" );
    return true;
}