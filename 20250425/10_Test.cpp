#include <iostream> // For std::cout
// #include <bits/stdc++.h> // Avoid using this non-standard header in production code
using namespace std; 

// Helper recursive function that takes an accumulator 'reversed_num'
int reverseDigitsRecursiveHelper(int num, int reversed_num) {
    // Base case: If the original number becomes 0, we've processed all digits
    if (num == 0) {
        return reversed_num;
    }

    // Recursive step:
    // 1. Get the last digit of num (num % 10)
    // 2. Add it to reversed_num (after shifting reversed_num left by one decimal place)
    // 3. Remove the last digit from num (num / 10)
    return reverseDigitsRecursiveHelper(num / 10, reversed_num * 10 + num % 10);
}

// Public wrapper function to start the recursion with a clean state
int reverseDigits(int num) {
    // Handle negative numbers if desired (e.g., reverse -123 to -321)
    // For simplicity, this example assumes positive numbers as per original code.
    // If num is 0, the helper function will immediately return 0.
    return reverseDigitsRecursiveHelper(num, 0);
}

// Driver code 
int main() { 
    int num1 = 123; 
    cout << "Reverse of " << num1 << " is " << reverseDigits(num1) << endl; 

    int num2 = 98765;
    cout << "Reverse of " << num2 << " is " << reverseDigits(num2) << endl;

    int num3 = 100; // Test with trailing zeros
    cout << "Reverse of " << num3 << " is " << reverseDigits(num3) << endl;

    int num4 = 0; // Test with zero
    cout << "Reverse of " << num4 << " is " << reverseDigits(num4) << endl;
    
    return 0; 
}