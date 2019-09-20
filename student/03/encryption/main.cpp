#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int check(string key)
{
    string::size_type length;
    length = key.length();
    int const summa = 32764;

    if(length != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;}

    for(int i = 0;i < 26;i++){
        char letter;
        letter = key.at(i);
        if(islower(letter)k){
           continue;}
        else{
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;}}

    for(int i = 97;i <= 122; ++i){
        length = key.find((char)i);
        if(length == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return EXIT_FAILURE;}}
}

int main()
{
    cout << "Enter the encryption key: ";
    string key;
    getline(cin, key);
    check(key);
}
