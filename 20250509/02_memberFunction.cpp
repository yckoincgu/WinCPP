// C++ program to demonstrate function 
// declaration outside class 

#include <iostream>  
using namespace std; 

class Person 
{ 
	public: 
	string name; 
	int id; 
	
	// printname is NOT defined inside class definition 
	void printname(); 
	
	// printid is defined INSIDE class definition 
	void printid() 
	{ 
		cout <<"student id is: "<<id; 
	} 
}; 

// Definition of printname using scope resolution operator :: 
void Person::printname() 
{ 
	cout <<"student name is: "<<name; 
} 


int main() { 
	
	Person student; 
	student.name = "xyz"; 
	student.id=15; 
	
	// call printname() 
	student.printname(); 
	cout << endl; 
	
	// call printid() 
	student.printid(); 
	return 0; 
} 

