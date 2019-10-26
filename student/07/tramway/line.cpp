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
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

Line::Line(std::string name, std::vector<std::string> stations):
    name_(name), stations_(stations){
}

// Returns the name of the line.
std::string Line::get_name() const
{
    return name_;
}

// Prints out all the stations.
void Line::print_stations()
{
    for( std::string station : stations_ ){
        std::cout << " - " << station << std::endl;
    }
}

// Returns all the stations.
std::vector<std::string> Line::get_stations() const
{
    return stations_;
}

// Returns true if stationName is on the line.
bool Line::is_station_on_line(std::string stationName)
{
    std::vector<std::string>::iterator it = std::find(stations_.begin(), stations_.end(), stationName);

    if( it == stations_.end() ){
        return false;
    }
    else{
        return true;
    }
}

// Adds newStation in front of nextStation.
void Line::add_station_between(std::string newStation, std::string nextStation)
{
    std::vector<std::string>::iterator it = std::find(stations_.begin(), stations_.end(), nextStation);
    stations_.insert( it, newStation );

}

// Removes the station from the line.
int Line::remove_station(std::string station)
{
    int erased = 0;

    std::vector<std::string>::iterator it = std::find(stations_.begin(), stations_.end(), station);
    if( it != stations_.end() ){
        stations_.erase(it);
        ++ erased;
    }

    return erased;
}

// Adds a new station to the line.
bool Line::add_station(std::string stationName)
{
    std::vector<std::string>::iterator it = std::find(stations_.begin(), stations_.end(), stationName);

    // Checks that the station doesn't already exist in the line.
    // Returns true if station can be added to the line.
    if( it == stations_.end()){
        stations_.push_back(stationName);
        return true;
    }

    else{
        return false;
    }

}
