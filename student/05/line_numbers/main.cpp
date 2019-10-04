#include <iostream>
#include <fstream>
#include <string>

int readWriteFile(std::string inputFile, std::string outputFile)
{
    std::ifstream fileObj(inputFile);

    if(fileObj){

        std::ofstream fileObjW(outputFile);

        int rowNmbr = 1;
        std::string row;

        while(getline(fileObj, row)){
            row.insert(0, std::to_string(rowNmbr)+" ");
            fileObjW << row << std::endl;
            rowNmbr += 1;
        }

        fileObj.close();
        fileObjW.close();

        exit( EXIT_SUCCESS );


    } else {

        std::cout << "Error! The file " << inputFile << " cannot be opened." << std::endl;
        exit( EXIT_FAILURE );

    }

}

int main()
{
    std::string inputFile;
    std::string outputFile;

    std::cout << "Input file: ";
    getline(std::cin, inputFile);
    std::cout << "Output file: ";
    getline(std::cin, outputFile);

    readWriteFile(inputFile, outputFile);

}
