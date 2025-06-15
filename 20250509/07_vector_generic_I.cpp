#include <iostream>
#include <vector>

// std::vector is a template class from the Standard Library for dynamic arrays
// <int> specifies that it's a vector of integers
// allowing you to store a sequence of elements that can grow or shrink in size.
template <typename T>
void printVectorGeneric(T elements){

    // Access elements of the vector using index
    std::cout << "First element: " << elements[0] << std::endl;
    std::cout << "Second element: " << elements[1] << std::endl;

    // std::vector<int>::iterator is the data type *it
     std::cout << "Elements:";
    for (typename T::iterator it = elements.begin(); it != elements.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
}

// std::vector is a template class from the Standard Library for dynamic arrays
// <int> specifies that it's a vector of char


int main() {
    // Declare a vector of integers
	std::vector<int> numbers;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
	printVectorGeneric(numbers);
    
	std::vector<char> characters;
    characters.push_back('a');
    characters.push_back('b');
    characters.push_back('c');
    characters.push_back('d');
	printVectorGeneric(characters);

    //int i;
	//std::cin>>i;

    return 0;
}

