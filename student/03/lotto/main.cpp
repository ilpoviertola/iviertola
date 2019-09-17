#include <iostream>

using namespace std;

unsigned long int factorial(int nro)
{
    if(nro > 0){
        return nro * factorial(nro - 1);
    } else {
        return 1;
    }
}

unsigned long int calculate(int drawnBalls, int totalBalls)
{
    unsigned long int p;
    p = factorial(totalBalls) / (factorial(totalBalls - drawnBalls) * factorial(drawnBalls));
    return p;
}

int main()
{
    cout << "Enter the total number of lottery balls: ";
    int totalBalls;
    cin >> totalBalls;

    cout << "Enter the number of drawn balls: ";
    int drawnBalls;
    cin >> drawnBalls;

    if(totalBalls > 0){
        if(totalBalls >= drawnBalls){
            cout << "The probability of guessing all " << drawnBalls << " balls correctly is 1/"
                 << calculate(drawnBalls, totalBalls) << endl;
        } else{
            cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        }
    } else{
        cout << "The number of balls must be a positive number." << endl;
    }
    return 0;
}
