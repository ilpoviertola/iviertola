#include "station.hh"
#include <string>
#include <vector>
#include <iostream>

Station::Station(std::string name, std::vector<std::string> stations):
    name_(name), lines_(stations){
}

std::string Station::get_name() const
{
    return name_;
}

bool Station::add_line(std::string lineName)
{
    std::vector<std::string>::iterator it = std::find( lines_.begin(), lines_.end(), lineName );

    if( it == lines_.end() ){
        lines_.push_back( lineName );
        return true;
    } else {
        return false;
    }
}
