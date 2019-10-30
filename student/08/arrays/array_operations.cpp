#include "array_operations.hh"
#include <iostream>
#include <algorithm>

int greatest_v1(int* itemptr, int size){
    int greatest = 0;
    int round = 0;

    for(int* position = itemptr; position < itemptr + size; ++position){
        if( round != 0){
            if( *position > greatest){
                greatest = *position;
            }
            else {
                continue;
            }
        } else { greatest = *position;}

        ++round;
    }
    return greatest;
}

int greatest_v2(int* itemptr, int *endptr){
    int greatest = 0;
    int round = 0;

    for( int *position = itemptr ; position != endptr ; ++position ){
        if( round != 0){
            if( *position > greatest){
                greatest = *position;
            }
            else {
                continue;
            }
        } else { greatest = *position;}

        ++round;
    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr){

    std::copy(itemptr, endptr, targetptr);

}

void reverse(int *leftptr, int *rightptr){

    std::reverse(leftptr, rightptr);
}
