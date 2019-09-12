#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int nbr = 0;
    std::cin >> nbr;

    int i = 1;
    while(i <= nbr)
    {
        if(i % 3 == 0)
        {if(i % 7 == 0){
            std::cout << "zip boing" << std::endl;}
            else{
           std::cout << "zip" << std::endl;}
        } else if(i % 7 == 0){
            if(i % 3 == 0){
                std::cout << "zip boing" << std::endl;
            }else{
            std::cout << "boing" << std::endl;}
        } else {
            std::cout << i << std::endl;
        }
        ++i;
        }

    }

