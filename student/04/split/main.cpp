#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

std::vector<std::string> split(std::string line, char separator, bool no_empty=false)
{
    std::vector<std::string> parts;
    std::string::size_type spot;
    std::string splittedPart;
    if(no_empty){
        while(line.length() > 0){
            spot = line.find(separator);
            if(spot == std::string::npos){
                parts.push_back(line);
                line.erase(0);
            }
            else{
                splittedPart = line.substr(0, spot);
                //std::cout << splittedPart << std::endl;
                line.erase(0, spot +1);
                //std::cout << line << std::endl;
                if(splittedPart.length() != 0){
                parts.push_back(splittedPart);}
            }
    }}
    else{
        while(line.length() > 0){
            spot = line.find(separator);
            if(spot == std::string::npos){
                parts.push_back(line);
                line.erase(0);
            }
            else{
                splittedPart = line.substr(0, spot);
                //std::cout << splittedPart << std::endl;
                line.erase(0, spot +1);
                //std::cout << line << std::endl;
                parts.push_back(splittedPart);
            }
    }
    }
    return parts;

}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
