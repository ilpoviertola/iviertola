#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

int main()
{
    std::map<std::string, int> scoreboard;
    std::string inputFile;
    std::cout << "Input file: ";
    getline(std::cin, inputFile);

    std::ifstream fileObj(inputFile);

    if( fileObj){
        std::string row;
        while( getline(fileObj, row) ){
            std::string::size_type spot;
            std::string name;
            int score;

            spot = row.find(":");
            name = row.substr(0, spot);
            score = std::stoi( row.substr(spot+1) );

            if( scoreboard.find(name) != scoreboard.end()){
                scoreboard.at(name) += score;
            } else {
                scoreboard.insert( { name, score } );
            }

        }

        fileObj.close();

        for(auto name : scoreboard){
            std::cout << name.first << ": " << name.second << std::endl;
        }

        exit( EXIT_SUCCESS );

    } else {
        std::cout << "Error! The file " << inputFile << " cannot be opened." << std::endl;
        exit(EXIT_FAILURE);
    }
}
