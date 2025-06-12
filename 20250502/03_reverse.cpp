// C++ program to implement 
// the above approach 
#include <bits/stdc++.h> 
using namespace std; 

// Iterative function to 
// reverse digits of num 
int reverseDigits(int num) 
{ 
	int x = 0; 
	while (num > 0) { 
		x = x * 10 + num % 10; 
		num = num / 10; 
	} 
	return x; 
} 

// Driver code 
int main() 
{ 
	int num = 123; 
	cout << "Reverse of num is " << reverseDigits(num); 

	//getchar(); 

	return 0; 
}

