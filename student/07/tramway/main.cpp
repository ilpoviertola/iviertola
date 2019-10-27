/* Program for Rasse's line network
 *
 * Desc:
 * In this program the user can modify and examine Rasse's tramway network
 * in Tampere. Functions available are LINES, STATIONS, LINE <line's name>,
 * STATION <station's name>, REMOVE <station's name>, ADDLINE <line's name>,
 * ADDSTATION <line's name> <new station> (<next station>) and QUIT. If the
 * station's/line's name consists from more than one word, must the name be
 * given inside quotation marks. Space between words that aren't in a quotat-
 * ion marks are considered as different parameters.
 *
 * Program author
 * Name: Ilpo Viertola
 * Student number: 272634
 * UserID: viertoli ( Necessary due to gitlab folder naming. )
 * E-Mail: ilpo.viertola@tuni.fi
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
#include <stdio.h>
#include <ctype.h>

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

// Add station to line in the network map.
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

// Reads file. Returns 0 if it's succesful.
bool read_file(Network& network)
{
   int returnValue = 0;

    std::string inputFile = "";

    std::cout << "Give a name for input file: ";
    getline( std::cin, inputFile );

    std::ifstream fileObj( inputFile );

    if( fileObj ){
        std::string row = "";
        while( getline( fileObj, row ) ){
            std::vector<std::string> parts = split( row, ';', false );

            // Row isn't in format: Line;Station
            if( parts.size() < 2 ){
                std::cout << "Error: Invalid format in file." << std::endl;
                returnValue = EXIT_FAILURE;
                break;
            }

            // add_station returns false if the station already exists on the line.
            else if( !add_station( parts, network ) ){
                std::cout << "Error: Station/line already exists." << std::endl;
                returnValue = EXIT_FAILURE;
                break;
            }
        }

    } else {
        std::cout << "Error: File could not be read." << std::endl;
        returnValue = EXIT_FAILURE;
    }

    return returnValue;
}

// Clears user input from quotation marks. Returns a vector additionalInfo
// containing user input(s).
std::vector<std::string> clean_user_input(std::vector<std::string> tmp)
{
    std::vector<std::string> additionalInfo;
    std::string input = "";
    bool sameInput = false;

    for( std::string part : tmp ){
        if( part.front() == '"' && part.back() == '"' ){
            part = part.substr(1, part.length() - 2);
            additionalInfo.push_back(part);
        }
        else if( part.front() == '"' ){
            part = part + " ";
            input = part.substr(1, part.length() - 1);
            sameInput = true;
        }
        else if( sameInput && ( part.front() != '"' && part.back() != '"' )){
            input += part + " ";
        }
        else if( sameInput && part.back() == '"' ){
            input += part.substr(0, part.length() - 1);
            additionalInfo.push_back(input);
            input = "";
            sameInput = false;
        }
        else if( !sameInput && ( part.front() != '"' && part.back() != '"' ) ){
            additionalInfo.push_back(part);
        }
    }

    return additionalInfo;
}

// Asks for input and checks if the user given input is legit.
// Returns a dataPair which contains info about good input (bool) and
// additionalInfo (station to be added etc.)
std::pair<bool, std::vector<std::string>> user_input(std::string usrFeed)
{
    std::pair<bool, std::vector<std::string>> dataPair;
    const std::vector<std::string> single_inputs = {"QUIT", "LINES",
                                                    "STATIONS"};
    const std::vector<std::string> multi_inputs = {"LINE",
                                                   "STATION", "ADDLINE",
                                                   "ADDSTATION", "REMOVE"};

    std::vector<std::string> tmp = split(usrFeed, ' ', true);

    std::for_each(tmp.at(0).begin(), tmp.at(0).end(), [](char & c){
        c = ::toupper(c);
    });

    // User has given more than one parameter.
    if( tmp.size() > 1 ){
        for( std::string command : multi_inputs ){

            if( tmp.at(0) == command ){
                usrFeed = tmp.at(0);
                tmp.erase(tmp.begin());
                dataPair = std::make_pair(true, clean_user_input(tmp));
                break;
            }
            else {
                std::vector<std::string> additionalInfo = {};
                dataPair = std::make_pair(false, additionalInfo);
            }
        }
    }
    else {
        for( std::string command : single_inputs ){
            if( tmp.at(0) == command ){
                std::vector<std::string> additionalInfo = {};
                dataPair = std::make_pair(true, additionalInfo);
                break;
            }
            else {
                std::vector<std::string> additionalInfo = {};
                dataPair = std::make_pair(false, additionalInfo);
            }
        }
    }
    return dataPair;
}

// Prints all the routes in alphabetical order.
void print_lines(Network& network)
{
    std::cout << "All tramlines in alphabetical order:" << std::endl;
    for(std::map<std::string, Line>::iterator it = network.begin();
        it != network.end(); ++it ){
        std::cout << it->first << std::endl;
    }
}

// Prints stations along the selected route.
void print_stations_on_line(Network& network, std::string line)
{
    if(network.find(line) != network.end()){
        std::cout << "Line " << line << " goes through these stations in the "
                                        "order they are listed:" << std::endl;
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

    for(std::map<std::string, Line>::iterator itMap = network.begin();
        itMap != network.end(); ++itMap ){
        std::vector<std::string> tmp = itMap->second.get_stations();

        for( std::string station : tmp ){
            std::vector<std::string>::iterator itVec =
                    std::find(allStations.begin(), allStations.end(), station);

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

// Prints lines that goes through the user given station.
void print_lines_on_station(Network& network, std::string station)
{
    std::vector<std::string> lines;

    for(std::map<std::string, Line>::iterator itMap = network.begin();
        itMap != network.end(); ++itMap ){
        std::vector<std::string> tmp = itMap->second.get_stations();

        std::vector<std::string>::iterator itVec =
                std::find(tmp.begin(), tmp.end(), station);
        if( itVec != tmp.end() ){
            lines.push_back( itMap->first );
        }
    }

    if( lines.size() == 0 ){
        std::cout << "Error: Station could not be found." << std::endl;
    }
    else{
        std::sort(lines.begin(), lines.end());
        std::cout << "Station " << station << " can be found on the following "
                                              "lines:" << std::endl;
        for( std::string line : lines ){
            std::cout << " - " << line << std::endl;
        }
    }
}

// Adds a new line to tramway network.
void add_line(Network& network, std::string lineToAdd)
{
    if(network.find(lineToAdd) == network.end()){
        std::vector<std::string> stations = {};
        Line lineObj = Line(lineToAdd, stations);
        network.insert( { lineToAdd, lineObj } );
        std::cout << "Line was added." << std::endl;
    }
    else {
        std::cout << "Error: Station/line already exists." << std::endl;
    }
}

// Adds a new to station to tramway network.
// Data vector contains, in this specific order, name of the line,
// new station and name of the station that comes after the new station
// (which is optional).
void add_station(Network& network, std::vector<std::string> data)
{
    if( network.find(data.at(0)) != network.end() ){
        if( network.at(data.at(0)).is_station_on_line(data.at(1))){
            std::cout << "Error: Station/line already exists." << std::endl;
        }
        else if( data.size() < 3 || !network.at(data.at(0))
                 .is_station_on_line(data.at(2))){
            network.at(data.at(0)).add_station(data.at(1));
            std::cout << "Station was added." << std::endl;
        }
        else{
            network.at(data.at(0)).add_station_between(data.at(1), data.at(2));
            std::cout << "Station was added." << std::endl;
        }
    }
    else{
        std::cout << "Error: Line could not be found." << std::endl;
    }
}

// Removes station from all of the lines.
void remove_station(Network& network, std::string station)
{
    int erased = 0;

    for(std::map<std::string, Line>::iterator itMap = network.begin();
        itMap != network.end(); ++itMap ){
        erased += itMap->second.remove_station(station);
    }

    if( !erased ){
        std::cout << "Error: Station could not be found." << std::endl;
    }
    else{
        std::cout << "Station was removed from all lines." << std::endl;
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

        std::string usrFeedCapitalized = split(usrFeed, ' ', true).at(0);
        std::pair<bool, std::vector<std::string>> dataPair = user_input(usrFeed);

        // Make user input capitalized.
        std::for_each(usrFeedCapitalized.begin(), usrFeedCapitalized.end(), [](char & c){
            c = ::toupper(c);
        });

        if( dataPair.first ){            
            if( usrFeedCapitalized == "QUIT" ){
                return EXIT_SUCCESS;
                break;
            }
            else if( usrFeedCapitalized == "LINES"){
                print_lines(network);
            }
            else if( usrFeedCapitalized == "LINE" ){
                if( dataPair.second.size() == 1 ){
                    print_stations_on_line(network, dataPair.second.at(0));
                }
                else {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }
            else if( usrFeedCapitalized == "STATIONS" ){
                print_stations(network);
            }
            else if( split(usrFeed, ' ', true).at(0) == "STATION" ||
                     split(usrFeed, ' ', true).at(0) == "station" ){
                if( dataPair.second.size() == 1 ){
                    print_lines_on_station(network, dataPair.second.at(0));
                }
                else {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }
            else if( usrFeedCapitalized == "ADDLINE" ){
                if( dataPair.second.size() == 1 ){
                    add_line(network, dataPair.second.at(0));
                }
                else {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }
            else if( usrFeedCapitalized == "ADDSTATION" ){
                if( dataPair.second.size() > 1 ){
                    add_station(network, dataPair.second);
                }
                else{
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }
            else if( usrFeedCapitalized == "REMOVE" ){
                if( dataPair.second.size() == 1 ){
                    remove_station(network, dataPair.second.at(0));
                }
                else{
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }
        }

        else{
            std::cout << "Error: Invalid input." << std::endl;
        }

    }
}
