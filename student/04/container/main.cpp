#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


void read_integers(std::vector< int >& ints, int count)

{

    int new_integer = 0;

    for(int i = 0; i < count; ++i)

    {

        std::cin >> new_integer;

        ints.push_back(new_integer);

        // TODO: Implement your solution here

    }

}



// TODO: Implement your solution here

bool same_values(std::vector< int >& ints){

    int counter = 0;

    for (long unsigned int i =1; i < ints.size(); ++i){

        if (ints.at(i) == ints.at(i-1)){

            ++counter;

        }

    }

    if ( counter != 0){

        return true;

    } else{return false;}

}

bool is_ordered_non_strict_ascending(std::vector< int >& ints){

    if (std::is_sorted(ints.begin(), ints.end())){

        return true;

    }

    else {return false;}

}



bool is_arithmetic_series (std::vector< int >& ints){

    long unsigned int sum = 0;

    for ( int vector_elem : ints){

        sum += vector_elem;

    }

    if (sum == ((ints.size()*(ints.at(0)+ints.at(ints.size()-1)))/2)){

        return true;}

    else {return false;}

}



bool is_geometric_series (std::vector< int >& ints){

    int q = ints.at(1)/ints.at(0);

    int counter = 0;

    for ( unsigned long int i = 1; i < ints.size(); ++i){

        if (ints.at(i) != ints.front() * pow(q, i)){

            ++counter;

        }

    }

    if (counter != 0){

        return false;

    } else{return true;}

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
