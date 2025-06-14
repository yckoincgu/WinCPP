#include <iostream>
// 
/*
runtime polymorphism 
1. It allows for code changes at running time.
   specifically (achieved through virtual functions 
   and base class pointers/references)
   enables the dynamic dispatch of function calls. 
2. virtual table
3. Polymorphism and plugin have tightly relationship and scenario
*/
class Operation {
public:
    virtual int perform(int a, int b) const = 0;
    virtual ~Operation() {}
};

class MultiplyOperation : public Operation {
public:
    int perform(int a, int b) const override {
        return a * b;
    }
};

class AddOperation : public Operation {
public:
    int perform(int a, int b) const override {
        return a + b;
    }
};

int main() {
    Operation* op_ptr = nullptr; // Initialize to nullptr

    // Scenario 1: Decision at runtime based on user input or some logic
    int choice;
    std::cout << "To operate arithematic function for 10 and 5"<< std::endl;
    std::cout<< "Enter 1 for Multiplication, 2 for Addition: "<< std::endl;
    std::cin >> choice;

    if (choice == 1) {
        op_ptr = new MultiplyOperation();
    } else if (choice == 2) {
        op_ptr = new AddOperation();
    } else {
        std::cout << "Invalid choice. Exiting.\n";
        return 1;
    }

    // At this point, we don't know at compile time whether op_ptr points to
    // a MultiplyOperation or an AddOperation.
    // The decision of WHICH perform() to call is made NOW, at runtime.
    std::cout << "Result: " << op_ptr->perform(10, 5) << std::endl;

    delete op_ptr; // Polymorphic cleanup

    return 0;
}