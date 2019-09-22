#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>
#include <iostream>


class Player
{
public:
    Player(std::string name);
    std::string get_name() const;
    int get_points() const;
    void add_points(int pts);
    bool has_won();
private:
    std::string name_;
    int points_;
};

#endif // PLAYER_HH
