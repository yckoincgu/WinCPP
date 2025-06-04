#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream  inputFile("X06512A.csv");
    std::string line;
    int i=1;
    while(std::getline(inputFile,line))
    {
    	std::cout<< "student " << i++ << ": "<< line << std::endl;
    }

   
	std::cin>>i;
 }
