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
#include <numeric>
#include <sstream>
#include <iterator>

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
bool read_file(Network& network)
{

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

// Asks for input and checks if the user given input is legit.
// Returns a dataPair which contains info about good input (bool) or
// additionalInfo (station to be added etc.)
std::pair<bool, std::string> user_input(std::string usrFeed)
{
    std::pair<bool, std::string> dataPair;
    const std::vector<std::string> single_inputs = {"QUIT", "LINES", "STATIONS"};
    const std::vector<std::string> multi_inputs = {"LINE", "STATION", "ADDLINE", "ADDSTATION", "REMOVE"};

    std::vector<std::string> tmp = split(usrFeed, ' ', true);

    if( tmp.size() > 1 ){
        for( std::string command : multi_inputs ){

            if( tmp.at(0) == command ){
                usrFeed = tmp.at(0);
                tmp.erase(tmp.begin());
                std::ostringstream vts;
                std::copy(tmp.begin(), tmp.end()-1, std::ostream_iterator<std::string>(vts, " "));
                vts << tmp.back();
                // additionalInfo can be station to be added etc.
                std::string additionalInfo = vts.str();
                // Delete quotation marks from station name.
                std::string::size_type size = additionalInfo.length();
                if( additionalInfo.substr(0,1) == "\"" && additionalInfo.substr(size-1,1) == "\""){
                    additionalInfo.erase(size-1);
                    additionalInfo.erase(0, 1);
                }
                dataPair = std::make_pair(true, additionalInfo);
                break;
            }

            else {
                dataPair = std::make_pair(false, "");
            }
        }
    }
    else {
        for( std::string command : single_inputs ){
            if( tmp.at(0) == command ){
                dataPair = std::make_pair(true, "");
                break;
            }
            else {
                dataPair = std::make_pair(false, "");
            }
        }
    }
    return dataPair;
}

// Prints all the routes in alphabetical order.
void print_lines(Network& network)
{
    std::cout << "All tramlines in alphabetical order:" << std::endl;
    for(std::map<std::string, Line>::iterator it = network.begin(); it != network.end(); ++it ){
        std::cout << it->first << std::endl;
    }
}

// Prints stations along the selected route.
void print_stations_on_line(Network& network, std::string line)
{
    if(network.find(line) != network.end()){
        std::cout << "Line " << line << " goes through these stations in the order they are listed:" << std::endl;
        network.at(line).print_stations();
    }
    else {
        std::cout << "Error: Line could not be found." << std::endl;
    }
}

//Prints all the stations in the network.
void print_stations(Network& network)
{
    std::vector<std::string> allStations;

    for(std::map<std::string, Line>::iterator itMap = network.begin(); itMap != network.end(); ++itMap ){
        std::vector<std::string> tmp = itMap->second.get_stations();

        for( std::string station : tmp ){
            std::vector<std::string>::iterator itVec = std::find(allStations.begin(), allStations.end(), station);

            if(itVec == allStations.end() ){
                allStations.push_back(station);
            }
        }
    }

    std::sort(allStations.begin(), allStations.end());
    std::cout << "All stations in alphabetical order:" << std::endl;

    for( std::string station : allStations ){
        std::cout << station << std::endl;
    }
}

void print_lines_on_station(Network& network, std::string station)
{
    std::vector<std::string> lines;

    for(std::map<std::string, Line>::iterator itMap = network.begin(); itMap != network.end(); ++itMap ){
        std::vector<std::string> tmp = itMap->second.get_stations();

        std::vector<std::string>::iterator itVec = std::find(tmp.begin(), tmp.end(), station);
        if( itVec != tmp.end() ){
            lines.push_back( itMap->first );
        }
    }

    if( lines.size() == 0 ){
        std::cout << "Error: Station could not be found." << std::endl;
    }
    else{
        std::sort(lines.begin(), lines.end());
        std::cout << "Station " << station << " can be found on the following lines:" << std::endl;
        for( std::string line : lines ){
            std::cout << " - " << line << std::endl;
        }
    }
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

    bool exit = read_file(network);

    while( not exit ){

        std::string usrFeed = "";
        std::cout << "tramway> ";
        getline( std::cin, usrFeed );

        std::pair<bool, std::string> dataPair = user_input(usrFeed);

        if( dataPair.first ){
            if( usrFeed == "QUIT" ){
                return EXIT_SUCCESS;
                break;
            }
            else if( usrFeed == "LINES" ){
                print_lines(network);
            }
            else if( split(usrFeed, ' ', true).at(0) == "LINE" ){
                if( user_input(usrFeed).second.size() > 0 ){
                    print_stations_on_line(network, user_input(usrFeed).second);
                }
                else {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }
            else if( usrFeed == "STATIONS" ){
                print_stations(network);
            }
            else if( split(usrFeed, ' ', true).at(0) == "STATION" ){
                if( user_input(usrFeed).second.size() > 0 ){
                    print_lines_on_station(network, user_input(usrFeed).second);
                }
                else {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }
        }

        else{
            std::cout << "Error: Invalid input." << std::endl;
        }

    }
}
