// C++ program to create calculator using
// switch statement
#include <iostream>
using namespace std;

// Driver code
int main()
{
	char op;
	float num1, num2;

	cout<< "enter an arithematic operator" << endl;
	// It allows user to enter operator
	// i.e. +, -, *, /
	cin >> op;

	// It allow user to enter the operands
	cout<< "enter to intergers for operation" << endl;
	cin >> num1 >> num2;

	// Switch statement begins
	switch (op) {
	// If user enter +
	case '+':
		cout << num1 + num2;
		break;

	// If user enter -
	case '-':
		cout << num1 - num2;
		break;

	// If user enter *
	case '*':
		cout << num1 * num2;
		break;

	// If user enter /
	case '/':
		cout << num1 / num2;
		break;

	// If the operator is other than +, -, * or /,
	// error message will display
	default:
		cout << "Error! operator is not correct";
	}
	// switch statement ends

	return 0;
}

