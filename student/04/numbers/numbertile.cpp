/*  Source file for NumberTile class.
 *
 * Also contains an operator for pair addition.
 *
 * Method implementations should be added to the same level as the existing
 * ones.
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

//Returns the coordinates of a tile.
std::string NumberTile::getCoords()
{
    std::string coordinates = std::to_string(coords_.first) + " " + std::to_string(coords_.second);
    return coordinates;
}

//Adds value to the tile when tiles are being moved.
int NumberTile::addValue(int value, char direction)
{
    int moves = 0;

    if(value_ == value or value_ == 0 or value == 0){

        value_ += value;

        moves += 1;

        if(direction == 'a'){
            board_->at(coords_.first).at(coords_.second + 1).zeroValue();
        }

        else if(direction == 'd'){
            board_->at(coords_.first).at(coords_.second - 1).zeroValue();
        }

        else if(direction == 'w'){
            board_->at(coords_.first + 1).at(coords_.second).zeroValue();
        }

        else{
            board_->at(coords_.first - 1).at(coords_.second).zeroValue();
        }
    }

    return moves;
}

// Resets tile value.
void NumberTile::zeroValue()
{
    value_ = 0;
}

int NumberTile::moveTile(char direction, const int SIZE)
{
    //Amount of succesful moves of tiles
    int moves = 0;

    if(direction == 'a'){
        for( int y = 0 ; y < SIZE ; y++ ){
            //std::cout <<"y: "<< y << std::endl;
            for( int x = SIZE - 1 ; x > 0 ; x-- ){
                //std::cout << "x: " << x << std::endl;
                moves = moves + board_->at(y).at(x - 1).addValue(board_->at(y).at(x).getValue(), direction);
            }
        }
    }

    if( direction == 'd'){
        for( int y = 0 ; y < SIZE ; y++ ){
            //std::cout << "y: " << y << std::endl;
            for( int x = 0 ; x < SIZE - 1; x++ ){
                moves = moves + board_->at(y).at(x + 1).addValue(board_->at(y).at(x).getValue(), direction);
                //std::cout << "x: " << x << std::endl;
            }
        }
    }

    if(direction == 'w'){
        for( int x = 0 ; x < SIZE ; x++){
            //std::cout << "x: " << x << std::endl;
            for( int y = SIZE - 1 ; y > 0 ; y--){
                moves = moves + board_->at(y - 1).at(x).addValue(board_->at(y).at(x).getValue(), direction);
                //std::cout << "y: " << y << std::endl;
            }
        }
    }

    if(direction == 's'){
        for( int x = 0; x < SIZE ; x++){
            //std::cout << "x: " << x << std::endl;
            for( int y = 0 ; y < SIZE - 1 ; y++){
                moves = moves + board_->at(y + 1).at(x).addValue(board_->at(y).at(x).getValue(), direction);
                //std::cout << "y: " << y << std::endl;
            }
        }
    }

    return moves;
}



