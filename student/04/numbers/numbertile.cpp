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
    : hasBeenMoved_(false), value_(value), coords_(coords), board_(board)
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
int NumberTile::addValue(int value, char direction, bool hasBeenMoved)
{
    // Amount of succesful moves when a direction is called.
    int moves = 0;

    // Move can be performed if tile value the tile is moving on is the same
    // as the value in the moving tile or zero.
    if((value_ == value && hasBeenMoved == false) or (value_ == 0 && hasBeenMoved == false)){

        // When the tile is being moved over a blank tile, the move doesn't count.
        if(value_ == 0 or value == 0){
            hasBeenMoved_ = false;
        } else{
            hasBeenMoved_ = true;
        }

        // Adds value of the tile which was moved on an another, to the tile
        // the tile was moved on.
        value_ += value;

        moves += 1;

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
    return moves;
}

// Clear the "extra" zeros afger moving tile.
void NumberTile::clearZeros(int value, char direction)
{
    if(value_ == 0){

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

// Moves tiles around the board.
int NumberTile::moveTile(char direction, const int SIZE)
{
    //Amount of succesful moves of tiles
    int moves = 0;

    if(direction == 'a'){
        for( int y = 0 ; y < SIZE ; y++ ){
            for( int x = SIZE - 1 ; x > 0 ; x-- ){
                // Adds the value of a tile in the right hand side to a tile on the left.
                moves = moves + board_->at(y).at(x - 1)
                        .addValue(board_->at(y).at(x).getValue(), direction, board_->at(y).at(x).getHasBeenMoved());
            }
        }
    }

    if( direction == 'd'){
        for( int y = 0 ; y < SIZE ; y++ ){
            for( int x = 0 ; x < SIZE - 1; x++ ){
                // Adds the value of a tile in the left hand side to a tile on the right.
                moves = moves + board_->at(y).at(x + 1)
                        .addValue(board_->at(y).at(x).getValue(), direction, board_->at(y).at(x).getHasBeenMoved());
            }
        }
    }

    if(direction == 'w'){
        for( int x = 0 ; x < SIZE ; x++){
            for( int y = SIZE - 1 ; y > 0 ; y--){
                // Adds the value of a tile underneath the another tile.
                moves = moves + board_->at(y - 1).at(x)
                        .addValue(board_->at(y).at(x).getValue(), direction, board_->at(y).at(x).getHasBeenMoved());
            }
        }
    }

    if(direction == 's'){
        for( int x = 0; x < SIZE ; x++){
            for( int y = 0 ; y < SIZE - 1 ; y++){
                // Adds the value of a tile underneath the another.
                moves = moves + board_->at(y + 1).at(x)
                        .addValue(board_->at(y).at(x).getValue(), direction, board_->at(y).at(x).getHasBeenMoved());
            }
        }
    }


    return moves;
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

void NumberTile::resetHasBeenMoved()
{
    hasBeenMoved_ = false;
}

bool NumberTile::getHasBeenMoved()
{
    return hasBeenMoved_;
}

