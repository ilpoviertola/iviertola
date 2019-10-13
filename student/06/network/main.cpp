#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print(std::map<std::string, std::vector<std::string>> network_copy, const std::string id, const int level)
{

    for( std::string name : network_copy.at(id) ){

        std::string output = "";

        for(int i = 0 ; i < level ; ++i){
            output += "..";
        }

        output += name;

        std::cout << output << std::endl;

        if( network_copy.find(name) != network_copy.end()){
            int new_level = level + 1;
            print(network_copy, name, new_level);
        }

    }
}

int count(std::map<std::string, std::vector<std::string>> network_copy, std::string id, std::vector<std::string> found)
{
    int counter = 0;

    for( std::string name : network_copy.at(id) ){
        ++counter;
        if( network_copy.find(name) != network_copy.end() ){
            found.push_back(name);
        }
    }

    for( std::string name : found ){
        found.erase(found.begin());
        return counter + count(network_copy, name, found);
    }

    return counter;
}

int depth(std::map<std::string, std::vector<std::string>> network_copy, std::string id, int deep)
{
    for( std::string name : network_copy.at(id) ){
        if( network_copy.find(name) != network_copy.end() ){
            ++deep;
            return depth(network_copy, name, deep);
        }
    }
    return deep;
}

int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string, std::vector<std::string>> network;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            if( network.find(id1) == network.end() ){
                std::vector<std::string> names;
                network.insert( { id1 , names } );
                network.at(id1).push_back(id2);
            } else {
                std::vector<std::string>::iterator it = std::find(network.at(id1).begin(), network.at(id1).end(), id2);
                if( it == network.at(id1).end() ){
                    network.at(id1).push_back(id2);
                }
            }


        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::map<std::string, std::vector<std::string>> network_copy(network);
            std::cout << id << std::endl;
            if(network.find(id) != network.end()){
                print(network_copy, id, 1);}

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            if(network.find(id) != network.end()){
                std::map<std::string, std::vector<std::string>> network_copy(network);
                std::vector<std::string> found;
                std::cout << count(network_copy, id, found) << std::endl;
            }
            else {
                std::cout << 0 << std::endl;
            }

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            if( network.find(id) != network.end() ){
                std::map<std::string, std::vector<std::string>> network_copy(network);
                std::cout << depth(network_copy, id, 2) << std::endl;
            }
            else {
                std::cout << 1 << std::endl;
            }

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
