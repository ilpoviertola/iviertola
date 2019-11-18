#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>


std::vector<std::string> split(std::string line, char separator)
{
    std::vector<std::string> parts;
    std::string::size_type spot;
    std::string splittedPart;

        while(line.length() > 0){
            spot = line.find(separator);
            if(spot == std::string::npos){
                parts.push_back(line);
                line.erase(0);
            }
            else{
                splittedPart = line.substr(0, spot);
                line.erase(0, spot +1);
                if(splittedPart.length() != 0){
                parts.push_back(splittedPart);}
            }
    }
    return parts;

}

int main()
{
    std::map< std::string, std::pair<int, std::string>> data;

    std::string inputFile;
    std::cout << "Input file: ";
    getline(std::cin, inputFile);
    int rowNmbr = 1;
    char separator = ' ';

    std::ifstream fileObj(inputFile);

    if(fileObj){
        std::string  row;
        while( getline(fileObj, row) ){
            std::vector< std::string > parts_no_empty  = split(row, separator);

            for( auto word : parts_no_empty){
                if(data.find(word) != data.end() && data.at(word).first < rowNmbr){

                    data.at(word).first += 1;
                    data.at(word).second += ", "+std::to_string(rowNmbr);

                } else {

                    data.insert( { word, std::make_pair(1, std::to_string(rowNmbr)) } );

                }
            }

            rowNmbr += 1;
            }

        fileObj.close();

        for(auto word : data){
            std::cout << word.first << " " << word.second.first << ": " << word.second.second << std::endl;
            }

        exit( EXIT_SUCCESS );

    } else {

        std::cout << "Error! The file " << inputFile << " cannot be opened." << std::endl;
        exit( EXIT_FAILURE );
    }

}
