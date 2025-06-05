// C++ program to demonstrate accessing of data members 
#include <iostream> 
using namespace std; 

class Student { 
public: // Access specifier 
	// Data Members 
	string name; 	// class member
	// Member Functions() 
	void printname() { cout << "The student name is:" << name << endl; } 
}; 
int main() 
{ 
	Student student_1, student_2; 		// Declare an object named student 
	student_1.name = "John"; 	// accessing data member
	student_1.printname(); 	// accessing member function 

	student_2.name = "Mary"; 	// accessing data member
	student_2.printname(); 	// accessing member function


	// int i;
	//std::cin>>i;
	
	return 0; 
}

