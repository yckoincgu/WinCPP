#include <iostream>
#include <string>
#include <sstream>


int getWordsNumber(std::string& line, char delimiter){
	int i=1;
	std::stringstream x(line);
	std::string words;
	while(std::getline(x, words, delimiter)) i++;
	
	return i;
} 

void showPointerArray(std::string line, char delimiter){
	
	int n=getWordsNumber(line, delimiter);
	
	std::stringstream y(line);
	std::string words;
	int i=0;
	
	std::string** aPointerToPointers = new std::string*[n];	//  a dynamic allocation of an array of pointers to std::string objects
	
	while(std::getline(y, words, delimiter)){
		aPointerToPointers[i++]=new std::string(words);	// give a pointer by new
		std::cout << words << std::endl;
	} 
};

int main()
{
    std::string line="I am a student";
    int i=1;
	char delimiter=' ';
    showPointerArray(line, delimiter);

	//std::cin>>i;
    
 }
