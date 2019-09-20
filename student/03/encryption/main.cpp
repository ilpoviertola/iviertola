#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void check(string key)
{
    string::size_type length;
    length = key.length();

    if(length != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        exit(EXIT_FAILURE);}

    for(int i = 0;i < 26;i++){
        char letter;
        letter = key.at(i);
        if(islower(letter)){
           continue;}
        else{
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            exit(EXIT_FAILURE);}}

    for(int i = 97;i <= 122; ++i){
        length = key.find((char)i);
        if(length == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            exit(EXIT_FAILURE);}}
}

void encrypt(string key, string& text){
    string::size_type length;
    length = text.length();
    string copy = text;



    for(long unsigned int p = 0;p < length; ++p){
        for(int i = 0; i < 26; ++i){
            char keyLetter = key[i];
            char original = 97 + i;
            string keyString;
            string originalString;
            keyString.assign(1, keyLetter);
            originalString.assign(1, original);
            if(original == text[p]){
                copy.replace(p, 1, keyString);}

        }
    }
    cout << "Encrypted text: " << copy << endl;
}


int main()
{
    cout << "Enter the encryption key: ";
    string key;
    getline(cin, key);
    check(key);

    cout << "Enter the text to be encrypted: ";
    string text;
    getline(cin, text);
    encrypt(key, text);

}
