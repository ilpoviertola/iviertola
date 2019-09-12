#include <iostream>

// Write here a function counting the mean value

int main()
{
    int nroAmount = 0;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    std::cin >> nroAmount;
    if(nroAmount > 0){
        int i = 1;
        double sum = 0;
        while(i <= nroAmount){
            int input = 0;
            std::cout << "Input " << i << ". number: ";
            std::cin >> input;
            sum = input + sum;
            ++i;
        }
        std::cout << "Mean value of the given numbers is " << sum / nroAmount << std::endl;
    }
    else{
        std::cout << "Cannot count mean value from " << nroAmount << " numbers" << std::endl;
    }
}
