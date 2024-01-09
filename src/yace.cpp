// yace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "constants.h"
#include "uci.h"
#include "yace.h"

// Internal methods
std::string trim( std::string input );
std::pair<std::string, std::string> split( std::string input );
bool process( std::pair<std::string, std::string> command );

int main( int argc, char** argv )
{
    std::string input;

    std::istream& stream = std::cin;
    Constants::getInstance();
    while ( std::getline( stream, input ) )
    {
        std::string trimmed = trim( input );
        std::pair<std::string, std::string> command = split( trimmed );

        LOG( "[%s] [%s]\n", command.first.c_str(), command.second.c_str() );

        if ( !process( command ) )
        {
            break;
        }
    }
}

/// <summary>
/// Returns a string that is based on the input but with superfluous spaces and tabs removed
/// </summary>
/// <param name="input">the raw input</param>
/// <returns>a copy of the input but with leading, trailing and unwanted spaces and tabs removed</returns>
std::string trim( std::string input )
{
    std::string worker;

    for ( std::string::const_iterator it = input.cbegin(); it != input.cend(); it++ )
    {
        if ( *it == '\t' || *it == ' ' )
        {
            if ( !worker.empty() && worker[ worker.length() - 1 ] != ' ' )
            {
                worker += ' ';
            }
        }
        else
        {
            worker += *it;
        }
    }

    while ( worker.starts_with( ' ' ) )
    {
        worker = worker.substr( 1 );
    }
    while ( worker.ends_with( ' ' ) )
    {
        worker = worker.substr( 0, worker.length() - 1 );
    }

    return worker;
}

/// <summary>
/// Takes the input and returns a pair with the first 'word' of input separated from the remainder
/// </summary>
/// <param name="input">the raw input, expected to be trimmed</param>
/// <returns>a pair with the first element being the first word from the input, and the second element containing the rest</returns>
std::pair<std::string, std::string> split( std::string input )
{
    std::pair<std::string, std::string> worker;
    std::string::iterator space = std::find( input.begin(), input.end(), ' ' );
    
    // Populate the first field until we hit a space
    bool first = true;

    for ( std::string::const_iterator it = input.cbegin(); it != input.cend(); it++ )
    {
        // Once we hit a space, start populating the second field
        if ( it == space )
        {
            first = false;
            continue;
        }

        if ( first )
        {
            // It looks like we can afford to be case-sensitive - Shredder is.
            // Use this if we want case-insensitivty in commands
            //   worker.first += std::tolower( *it );
            worker.first += std::tolower( *it );
        }
        else
        {
            worker.second += *it;
        }
    }

    return worker;
}

/// <summary>
/// Call the handler for the provided command
/// </summary>
/// <param name="command">the command and its arguments</param>
/// <returns>true to continue taking input and processing it, false as a signal to exit</returns>
bool process( std::pair<std::string, std::string> command )
{
    return UCI::GetInstance().Process( command );
}
