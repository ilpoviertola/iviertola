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

std::string Line::get_name() const
{
    return name_;
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
