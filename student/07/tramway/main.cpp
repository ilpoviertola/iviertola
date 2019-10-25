/* Program author
 * Name: Ilpo Viertola
 * Student number: 272634
 * UserID: viertoli ( Necessary due to gitlab folder naming. )
 * E-Mail: ilpo.viertola@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 *
 * */
#include "line.hh"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using Network = std::map<std::string, Line>;

// Split function.
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// Add station to line.
bool add_station(std::vector<std::string> parts, Network& network)
{

    // If line comes up the first time.
    if(network.find(parts.at(0)) == network.end() ){
        std::vector<std::string> stations;
        stations.push_back( parts.at(1) );
        Line lineObj = Line( parts.at(0), stations );
        network.insert( { parts.at(0), lineObj } );
        return true;
    }
    else {
        // False is returned if station has already been added to the line.
        return network.at( parts.at(0) ).add_station( parts.at(1) );
    }

}

// Reads file.
bool read_file()
{
    Network network;

    std::string inputFile = "";

    std::cout << "Give a name for input file: ";
    getline( std::cin, inputFile );

    std::ifstream fileObj( inputFile );

    if( fileObj ){
        std::string row = "";
        while( getline( fileObj, row ) ){
            std::vector<std::string> parts = split( row, ';', false );

            if( parts.size() < 2 ){
                std::cout << "Error: Invalid format in file." << std::endl;
                return EXIT_FAILURE;
                break;
            }

            else if( !add_station( parts, network ) ){
                std::cout << "Error: Station/line already exists." << std::endl;
                return EXIT_FAILURE;
                break;
            }
        }


    } else {
        std::cout << "Error: File could not be read." << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

// Short and sweet main.
int main()
{
    Network network;

    print_rasse();

    read_file();

    return EXIT_SUCCESS;
}
