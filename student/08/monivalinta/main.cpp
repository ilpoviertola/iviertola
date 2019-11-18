#include <iostream>

using namespace std;

int main()
{
        int x;
        int* ptr = &x;
        x = 5;
        cout << ptr << endl;
        cout << *ptr << endl;
        cout << x << endl;
        cout << &x << endl;
}
