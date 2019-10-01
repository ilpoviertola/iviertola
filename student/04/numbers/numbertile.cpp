/*  Source file for NumberTile class.
 *
 * Also contains an operator for pair addition.
 *
 * Method implementations should be added to the same level as the existing
 * ones.
 *
 * Program author ( Fill with your own info )
 * Name: Ilpo Viertola
 * Student number: 272634
 * UserID: viertoli ( Necessary due to gitlab folder naming. )
 * E-Mail: ilpo.viertola@tuni.fi
 *
 *
 * */
#include "numbertile.hh"
#include <iomanip>
#include <iostream>

// Pair addition operator. Allows to do result_pair = pair_1 + pair_2
std::pair<int, int>operator +(std::pair<int, int> lhs, std::pair<int, int> rhs){
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

// Modify the second line if you don't wish to use pairs.
NumberTile::NumberTile(int value,
                       std::pair<int, int> coords,
                       std::vector<std::vector<NumberTile> > *board)
    : value_(value), coords_(coords), board_(board)
{
    // Students should write their own implementation here, if necessary.


}

// Students should not touch this method.
void NumberTile::print(int width)
{
    // std::setw() sets the width of next printable to given amount, usually
    // by adding spaces in front.
    std::cout << "|" << std::setw(width - 1) << value_;
}

//Sets new value to an empty tile.
bool NumberTile::setValue(int value)
{
    if(value_ == 0){
        value_ += value;

        return true;
    }
    else{
        return false;
    }
}

//Return the value of a tile.
int NumberTile::getValue()
{
    return value_;
}

//Adds value to the tile when tiles are being moved.
void NumberTile::addValue(int value, char direction)
{

    // Move can be performed if tile value which the tile is moving on is the
    // same as the value in the moving tile or zero.
    if(value_ == value or value_ == 0 or value == 0){


        // Adds value of the tile which was moved on an another, to the tile
        // the tile was moved on.
        value_ += value;

        if(direction == 'a'){
            // Zeros the value of the tile on the right hand side.
            board_->at(coords_.first).at(coords_.second + 1).zeroValue();
        }

        else if(direction == 'd'){
            // Zeros the value of the tile on the left hand side.
            board_->at(coords_.first).at(coords_.second - 1).zeroValue();
        }

        else if(direction == 'w'){
            // Zeros the value of the tile underneath.
            board_->at(coords_.first + 1).at(coords_.second).zeroValue();
        }

        else{
            // Zeros the value of the upper tile.
            board_->at(coords_.first - 1).at(coords_.second).zeroValue();
        }
    }
}

// Clear the "extra" zeros afger moving tile.
void NumberTile::clearZeros(int value, char direction)
{
    if(value_ == 0 or value == 0){

        // Adds value of the tile which was moved on an another, to the tile
        // the tile was moved on.
        value_ += value;

        if(direction == 'a'){
            // Zeros the value of the tile on the right hand side.
            board_->at(coords_.first).at(coords_.second + 1).zeroValue();
        }

        else if(direction == 'd'){
            // Zeros the value of the tile on the left hand side.
            board_->at(coords_.first).at(coords_.second - 1).zeroValue();
        }

        else if(direction == 'w'){
            // Zeros the value of the tile underneath.
            board_->at(coords_.first + 1).at(coords_.second).zeroValue();
        }

        else{
            // Zeros the value of the upper tile.
            board_->at(coords_.first - 1).at(coords_.second).zeroValue();
        }
    }
}

// Resets tile value to zero.
void NumberTile::zeroValue()
{
    value_ = 0;
}

//Checks if user has won the game.
bool NumberTile::hasWon(int goal)
{
    if(value_ >= goal){
        return true;
    }
    else {
        return false;
    }
}


