#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    } 
}

bool same_values(std::vector< int >& ints)
{
    bool error;
    for(long unsigned int i = 0;i < ints.size() - 1;++i){
        if(ints.at(i) != ints.at(i+1)){
            error = true;
            break;
        }
    }
    if(error){return false;}else{return true;}
}

bool is_ordered_non_strict_ascending(std::vector< int >& ints)
{
    bool error;
    for(long unsigned int i = 0;i < ints.size() - 1;++i){
        if(ints.at(i) > ints.at(i+1)){
            error = true;
            break;
        }
    }
    if(error){return false;}else{return true;}
}

bool is_arithmetic_series(std::vector< int >& ints)
{
    bool error;
    for(long unsigned int i = 0;i < ints.size() - 2;++i){
        if(ints.at(i) - ints.at(i+1) != ints.at(i+1) - ints.at(i+2)){
            error = true;
            break;
        }
    }
    if(error){return false;}else{return true;}
}

bool is_geometric_series(std::vector< int >& ints)
{
    bool error;
    for(long unsigned int i = 0;i < ints.size() - 2;++i){
        if(ints.at(i) / ints.at(i+1) != ints.at(i+1) / ints.at(i+2)){
            error = true;
            break;
        }
    }
    if(error){return false;}else{return true;}
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
