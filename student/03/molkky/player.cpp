#include "player.hh"
#include <iostream>
#include <string>

Player::Player(std::string name):
    name_(name), points_(0){
}

std::string Player::get_name() const{
    return name_;
}

void Player::add_points(int pts){
    points_ = points_ + pts;
    if(points_ > 50){
        std::cout << name_ << " gets penalty points!" << std::endl;
        points_ = 25;
    }
}

int Player::get_points() const{
    return points_;
}

bool Player::has_won(){
    if(points_ == 50){
        return true;
    }else{
        return false;
    }
}
