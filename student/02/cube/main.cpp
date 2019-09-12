#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int nro = 0;
    cout << "Enter a number: ";
    cin >> nro;
    int p = 0;
    int r = 0;
    p = pow(nro, 3);
    r = cbrt(p);
    if(p < 0){
        cout << "Error! The cube of " << nro << " is not " << p << endl;
    } else if(r != nro){
        cout << "Error! The cube of " << nro << " is not " << p << endl;
    } else{
        cout << "The cube of " << nro << " is " << p << "." << endl;
    }
}
