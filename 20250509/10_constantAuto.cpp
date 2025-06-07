#include <iostream>
#include <sstream>
#include <vector>
#include <string>

// Function to split a string by a given delimiter
std::vector<std::string> buildVector(const std::string& s, char delimiter) {
    // s is a constant reference to a std::string object.
    // It does not create a copy of the string passed to the function.
    // It allows s to be used directly as if it were the original string object.
    // The const keyword guarantees that the function cannot modify the original string.
    // This reference must always refer to a valid object; it cannot be null.
    std::vector<std::string> dynamicWords;
    std::string word;
    std::istringstream ss(s);
    
    // Extract tokens separated by the delimiter
    while (std::getline(ss, word, delimiter)) {
        dynamicWords.push_back(word);
    }
    return dynamicWords;
}

int main() {
    std::string input = "Hello,World,Split,Example";
    char delimiter = ',';

    // Split the input string
    std::vector<std::string> wordsInVector = buildVector(input, delimiter);
    

    // Print each token using a range-based for loop
    int index = 0;
    for (const auto& word : wordsInVector) {
        // auto->Lets the compiler deduce the type of word from the elements in wordsInVector. 
        //       In this case, wordsInVector holds std::string objects, so auto will deduce to std::string.
        // const-> Indicates that word will be a constant reference. 
        //         This means you cannot modify the elements of wordsInVector 
        //         through word inside the loop
        // &->Indicates that word will be a reference. 
        //    This is highly recommended for performance when iterating over containers of objects (like std::string), 
        //    it avoids making a copy of each element in every iteration
        std::cout << "Word " << index++ << ": " << word << std::endl;
    }

    // Wait for user input before closing
    //std::cin.get();

    return 0;
}

