// C++ program to demonstrate constructors 
#include <bits/stdc++.h> 
using namespace std; 
class Person 
{ 
	public: 
	std::string name;
	int id; 
	
	//Default Constructor 
	Person() 
	{ 
		cout << "Default Constructor called" << endl; 
		id=-1; 
	} 
	
	//Parameterized Constructor 
	Person(std::string name, int id):name(name), id(id) 		// :name(name), id(id) mean this.name=name, this.id=id
	{ 
		cout <<"Parameterized Constructor called "<< endl; 

	} 
}; 

int main() { 
	
	// student will call Default Constructor 
	Person student_1; 
	cout <<"student_1 id is: "<< student_1.id << endl; 
	
	// student_2 will call Parameterized Constructor 
	Person* student_2=new Person(); 
	cout <<"student_2 name is: " <<student_2->name << endl;
	cout <<"student_2 id is: " <<student_2->id << endl; 
	
	
	return 0; 
} 

