// C++ program to implement 
// the above approach 
#include <bits/stdc++.h> 
using namespace std; 

// Iterative function to 
// reverse digits of num 
int reverseDigits(int num) 
{ 
	int new_num = 0; 
	while (num > 0) { 
		new_num = new_num * 10 + num % 10; 
		num = num / 10; 
	} 
	return new_num; 
} 

// Driver code 
int main() 
{ 
	int num = 123; 
	cout << "Reverse of num is " << reverseDigits(num); 

	//getchar(); 

	return 0; 
}

