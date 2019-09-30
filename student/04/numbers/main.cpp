/* Numbers ( or 2048, but that's an invalid name ) : Template code
 *
 * Desc:
 *  This program generates a game of 2048, a tile combining game
 * where the goal is to get from 2's to 2048. The board is SIZE x SIZE,
 * ( original was 4x4 ) and every round the player chooses a direction
 * to which the tiles should fall. If they collide with a wall or a different
 * value, they will move as close as they can get. If they collide with
 * a tile with same value, they will combine and double the value. The
 * tile will continue to move until a wall or other tile comes along, but a
 * single tile can only be combined once per "turn".
 *  Game will end when the goal value asked (orig 2048) is reached or new
 * tile can't be added to the board.
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
 *
 * Notes about the program and it's implementation:
 * */

#include "numbertile.hh"
#include <iostream>
#include <vector>
#include <random>
#include <string>

const int SIZE = 4;
const int NEW_VALUE = 2;
const int PRINT_WIDTH = 5;
const int DEFAULT_GOAL = 2048;
const std::vector<char> INPUTS = {'a', 's', 'd', 'w', 'q'};


// Adds a single new value to board using rEng and distr for random positioning.
void newValue(std::vector<std::vector<NumberTile>> &board,
               std::default_random_engine &rEng,
               std::uniform_int_distribution<int> &distr){
    // Tries to assign NEW_VAl to randomly selected tile. Continues trying until
    // newVal() returns true.
    while(!board.at(distr(rEng)).at(distr(rEng)).setValue(NEW_VALUE));
}

// Initializes the board to size SIZE x SIZE and adds SIZE tiles with NEW_VALUE
// to it through new_value() func after initializing the random engine with
// a seed value.
void initBoard(std::vector<std::vector<NumberTile>> &board,
                std::default_random_engine &rEng,
                std::uniform_int_distribution<int> &distr){

    // Initialize the board with SIZE x SIZE empty numbertiles.
    for ( auto y = 0; y < SIZE; y++ ){
        board.push_back({});
        for ( auto x = 0; x < SIZE; x++ ){
            // If you don't want to use pairs, replace "std::make_pair(y, x)"
            // with "y, x".
            board.at(y).push_back(NumberTile(0, std::make_pair(y, x), &board));
        }

    }

    // Ask user for the seed value and initialize rEng.
    std::cout << "Give a seed value or an empty line: ";
    std::string seed = "";
    getline(std::cin, seed);

    if(seed == "") {
        // If the user did not give a seed value, use computer time as the seed
        // value.
        rEng.seed(time(NULL));
    } else {
        // If the user gave a seed value, use it.
        rEng.seed(stoi(seed));
    }

    // Add some tiles to the board.
    for ( int i = 0 ; i < SIZE ; ++i ){
        newValue(board, rEng, distr);
    }
}

// Prints the board.
void print(std::vector<std::vector<NumberTile>> &board){
    // The y isn't actually the y coordinate or some int, but an iterator that
    // is like a vector of NumberTiles.
    for ( auto y : board ){
        // Prints a row of dashes.
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        // And then print all cells in the desired width.
        for ( auto x : y ){
            x.print(PRINT_WIDTH);
        }
        // And a line after each row.
        std::cout << "|" << std::endl;
    }
    // Print a last row of dashes so that the board looks complete.
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}


// Checks if the user given input is rigth and acceptable. Continues asking
// until right input is given.
char userInput(){

    bool correctInput = false;

    while(!correctInput){
        char userInput;
        std::cout << "Dir> ";
        std::cin >> userInput;
        // Checks that the user has given legit input
        for( auto x : INPUTS){
            if(x == userInput){
                correctInput = true;
                return userInput;
                break;
            }
        }
        std::cout << "Error: unknown command." << std::endl;
    }
    return 0;
}

//Asks user for the goal wanted to set.
int askGoal(){
    int goal;
    std::cout << "Give a goal value or an empty line: ";
    std::string goalStr = "";
    getline(std::cin, goalStr);
    // If user gives empty line, DEFAULT_GOAL is used as a goal
    if(goalStr == ""){
        goal = DEFAULT_GOAL;
    } else{
        goal = stoi(goalStr);
    }
    return goal;
}

//Checks every tile on board if there's any wins.
bool hasWon(std::vector<std::vector<NumberTile>> &board, int goal){
    for( auto y : board ){
        for( auto x : y){
            if(x.hasWon(goal)){
                return true;
            }
        }
    }

    return 0;
}

// CLear zeros after succesful move.
void clearZeros(std::vector<std::vector<NumberTile>> &board, char direction)
{
    // Clears zeros after a succesful move to left.
    if(direction == 'a'){
        for( int y = 0 ; y < SIZE ; y++ ){
            for( int x = SIZE - 1 ; x > 0 ; x-- ){
                // Adds the value of a tile in the right hand side to a tile on
                // the left if left tile's value is 0.
                board.at(y).at(x - 1).clearZeros(board.at(y).at(x).getValue(),
                                                 direction);
            }
        }
    }
    // Clears zeros after a succesful move to right.
    if( direction == 'd'){
        for( int y = 0 ; y < SIZE ; y++ ){
            for( int x = 0 ; x < SIZE - 1; x++ ){
                // Adds the value of a tile in the left hand side to a tile on
                // the right if right tile's value is 0.
                board.at(y).at(x + 1).clearZeros(board.at(y).at(x).getValue(),
                                                 direction);
            }
        }
    }
    // Clear zeros after a succesful move upwards.
    if(direction == 'w'){
        for( int x = 0 ; x < SIZE ; x++){
            for( int y = SIZE - 1 ; y > 0 ; y--){
                // Adds the value of a tile underneath the another tile if the
                // tile's value on the bottom is zero.
                board.at(y - 1).at(x).clearZeros(board.at(y).at(x).getValue(),
                                                 direction);
            }
        }
    }
    // Clear zeros after a succesful move downwards.
    if(direction == 's'){
        for( int x = 0; x < SIZE ; x++){
            for( int y = 0 ; y < SIZE - 1 ; y++){
                // Adds the value of a tile underneath the another if the
                // tile's value on the top is 0.
                board.at(y + 1).at(x).clearZeros(board.at(y).at(x).getValue(),
                                                 direction);
            }
        }
    }
}

int moveTile(std::vector<std::vector<NumberTile>> &board, char direction)
{
    int moves = 0;

    if( direction == 'a' ){
        // Clears zeroes so tile's with value are next to each other before
        // adding them together.
        for( int i = 0 ; i < SIZE ; ++i){
        clearZeros(board, direction);
        }
        for( int y = 0 ; y < SIZE ; ++y ){
            for( int x = 0 ; x < SIZE - 1 ; ++x){
                // Adds the value of a tile in the right hand side
                // to a tile on the left.
                moves = moves + board.at(y).at(x).addValue(
                            board.at(y).at(x + 1).getValue(), direction);
            }
        }
    }

    if( direction == 'd' ){
        // Clears zeroes so tile's with value are next to each other before
        // adding them together.
        for( int i = 0 ; i < SIZE ; ++i){
        clearZeros(board, direction);
        }
        for( int y = 0 ; y < SIZE ; ++y){
            for( int x = SIZE - 1 ; x > 0 ; --x){
                 // Adds the value of a tile in the left hand side
                // to a tile on the right.
                moves = moves + board.at(y).at(x).addValue(
                            board.at(y).at(x - 1).getValue(), direction);
            }
        }
    }

    if( direction == 'w'){
        // Clears zeroes so tile's with value are next to each other before
        // adding them together.
        for( int i = 0 ; i < SIZE ; ++i){
        clearZeros(board, direction);
        }
        for( int x = 0 ; x < SIZE ; ++x ){
            for( int y = 0 ; y < SIZE - 1 ; ++y ){
                // Adds the value of a tile underneath the another tile.
                moves = moves + board.at(y).at(x).addValue(
                            board.at(y + 1).at(x).getValue(), direction);
            }
        }
    }

    if(direction == 's'){
        // Clears zeroes so tile's with value are next to each other before
        // adding them together.
        for( int i = 0 ; i < SIZE ; ++i){
        clearZeros(board, direction);
        }
        for( int x = 0 ; x < SIZE; ++x ){
            for( int y = SIZE - 1 ; y > 0 ; --y){
                // Adds the value of a tile underneath the another.
                moves = moves + board.at(y).at(x).addValue(
                            board.at(y - 1).at(x).getValue(), direction);
            }
        }
    }
    return 0;
}

// Checks if there's any blank tiles left.
bool spaceOnBoard(std::vector<std::vector<NumberTile>> &board){

    int spotsOnBoard = 0;

    for( auto y : board ){
        for( auto x : y ){
            if(x.getValue() == 0){
                ++spotsOnBoard;
            }
        }
    }
    return spotsOnBoard;
}

int main()
{
    // Declare the board and randomengine.
    std::vector<std::vector<NumberTile>> board;
    std::default_random_engine randomEng;
    // And initialize the disrt to give numbers from the correct
    std::uniform_int_distribution<int> distr(0, SIZE - 1);

    initBoard(board, randomEng, distr);
    int goal = askGoal();
    print(board);

    //Loop goes on and on until the goal is reached or user gives 'q' as input.
    while(!hasWon(board, goal)){
        //Input (direction) is being asked from the user.
        char direction = userInput();
        if(direction == 'q'){
            break;}
        //Move tiles to wanted direction. Success stands for accomplished moves.
        moveTile(board, direction);
        clearZeros(board, direction);
        // If the user hasn't won the game, a new tile is added to the board.
        if(!hasWon(board, goal)){
            //Adds new value to a empty tile after checking for space on the board.
            if(spaceOnBoard(board)){
                newValue(board, randomEng, distr);
            }
            //If new tile can't be added player has lost the game.
            else {
                std::cout << "Can't add new tile, you lost!" << std::endl;
                break;}
        }
        print(board);
    }

    std::cout << "You reached the goal value of " << goal << "!" << std::endl;
}

