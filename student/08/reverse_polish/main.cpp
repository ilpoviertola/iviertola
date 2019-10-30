#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include <cctype>

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int divi(int a, int b) {
    return a / b;
}

typedef int (*funptr)(int, int);

funptr operations[] = { add, sub, mul, divi };

bool error_check( int nums, int operands )
{
    if( nums <= operands ){
        std::cout << "Error: Too few operands\n";
        return false;
    }
    else if( nums > operands + 1){
        std::cout << "Error: Too few operators\n";
        return false;
    }
    else{
        return true;
    }

}

int main()
{
    std::cout << "Input an expression in reverse Polish notation (end with #):\n";

    while( true ){
        int array[80] = {0};
        int operands = 0;
        int nums = 0;
        bool cont = true;
        std::string input = "";
        std::cout << "EXPR> ";
        getline( std::cin, input );

        if( !isdigit(input.at(0)) ){
            std::cout << "Error: Expression must start with a number\n";
            break;
        }

        for( char command : input ){

            if( isdigit(command) ){
                std::rotate( std::begin(array), std::end(array) - 1, std::end(array) );
                array[0] = command - '0';
                ++nums;
            }
            else if( command == '+' ){
                array[0] = (operations[0])(array[0], array[1]);
                array[1] = 0;

                for( int i = 1 ; i < 80 ; ++i ){
                    if( i != 79 ){
                        array[i] = array[i + 1];
                    } else { array[79] =  0; }
                }
                ++operands;
            }
            else if( command == '-' ){
                array[0] = (operations[1])(array[0], array[1]);
                array[1] = 0;

                for( int i = 1 ; i < 80 ; ++i ){
                    if( i != 79 ){
                        array[i] = array[i + 1];
                    } else { array[79] =  0; }
                }
                ++operands;
            }
            else if( command == '*' ){
                array[0] = (operations[2])(array[0], array[1]);
                array[1] = 0;

                for( int i = 1 ; i < 80 ; ++i ){
                    if( i != 79 ){
                        array[i] = array[i + 1];
                    } else { array[79] =  0; }
                }
                ++operands;
            }
            else if( command == '/' ){
                if( array[1] == 0 ){
                    std::cout << "Error: Division by zero\n";
                    cont = false;
                    break;
                }
                array[0] = (operations[3])(array[0], array[1]);
                array[1] = 0;

                for( int i = 1 ; i < 80 ; ++i ){
                    if( i != 79 ){
                        array[i] = array[i + 1];
                    } else { array[79] =  0; }
                }
                ++operands;
            }
            else if( command == '#' ){
                break;
            }
            else if( command == ' ' ){
                continue;
            }
            else {
                std::cout << "Error: Unknown character\n";
                break;
            }
        }
        if( cont ){
            if( error_check(nums, operands) ){
                std::cout << "Correct: " << array[0] << " is the result\n";
            }
            else{
                break;
            }
        } else { break; }
    }
}
