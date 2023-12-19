#pragma once

#include <map>
#include <string>

class UCI
{
typedef bool ( UCI::*UCICommand )( std::string arguments );

public:
    static UCI GetInstance();

    bool Process( std::pair<std::string, std::string> command );

private:
    std::map<std::string, UCICommand> handlers;

    // Handlers
    bool CommandPerft( std::string arguments );
    bool CommandQuit( std::string arguments );
    bool CommandUci( std::string arguments );

    UCI()
    {
        handlers[ "perft" ] = &UCI::CommandPerft;
        handlers[ "quit" ] = &UCI::CommandQuit;
        handlers[ "uci" ] = &UCI::CommandUci;
    }
};
