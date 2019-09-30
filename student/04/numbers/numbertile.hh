/* Class: Numbertile
 *
 * Acts as a single tile in the board.
 *
 * Students can modify both parts of the class and add their own variables
 * and methods. Implementations for the methods should be in the source file.
 *
 * */
#ifndef NUMBERTILE_HH
#define NUMBERTILE_HH
#include <utility>
#include <vector>
#include <string>
#include <iostream>

class NumberTile
{
public:
    // Public part contains variables and methods that can be used outside the
    // class itself.

    /* About pairs: the elements in a pair can be accessed with pair.first
    * and pair.second. If you do not wish to use pairs, you can modify the
    * given code to work without. Just replace the pair-parameter here & in the
    * source file with "int y, int x" and then modify the main.cpp in the
    * indicated spot.
    * */
    // Constructor that takes in a value, a location and the board the tile is on.
    NumberTile(int value, std::pair<int, int> coords,  std::vector<std::vector<NumberTile>> *board);

    // Prints the tile in the desired width.
    void print( int width );

    // Tries to set a new value to the tile. Returns true if successful, false
    // if the tile already contains some value.
    bool setValue(int value);

    // Moves the tile to user given direction, if possible. Counts succesful moves.
    int moveTile(char direction, const int SIZE);

    // Returns value of a tile.
    int getValue();

    //Adds value of another tile to another.
    int addValue(int value, char direction, bool hasBeenMoved);

    // Resets tile value to zero.
    void zeroValue();

    // Checks is the tile value is more or exactly the goal value.
    bool hasWon(int goal);

    // Clears extra zeros after a tile is succesfully moved.
    void clearZeros(int value, char direction);

    void resetHasBeenMoved();

    bool getHasBeenMoved();

private:
    // Private part contains variables and methods that shouldn't be usable
    // outside the class.

    bool hasBeenMoved_;

    // Value of the tile.
    int value_;

    // Coordinaters of a tile.
    std::pair<int, int> coords_;

    // Pointer to the board where the tile is.
    std::vector<std::vector<NumberTile>>* board_;
};

#endif // NUMBERTILE_HH
