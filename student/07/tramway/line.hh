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
#ifndef LINE_HH
#define LINE_HH
#include <vector>
#include <string>
#include <iostream>



class Line
{
public:

    Line(std::string name, std::vector<std::string> stations);
    std::string get_name() const;
    bool add_station(std::string stationName);
    void print_stations();
    std::vector<std::string> get_stations() const;
    bool is_station_on_line(std::string stationName);
    void add_station_between(std::string newStation, std::string nextStation);
    int remove_station(std::string station);

private:

    std::string name_;
    std::vector<std::string> stations_;
};

#endif // LINE_HH

