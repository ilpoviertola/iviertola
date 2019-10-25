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

private:
    std::string name_;
    std::vector<std::string> stations_;
};

#endif // LINE_HH

