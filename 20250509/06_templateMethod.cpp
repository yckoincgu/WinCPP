#include <iostream>

// Template class with a templated method
template <typename T>
class MyClass
{
private:
    T data;
public:
    /* 	It takes a parameter of type T and
        initializes the member variable data with the value passed to the constructor.
    */
    MyClass(T d) : data(d) {} // assign d to data which is a member vaiable

    // Templated method to display data
    template <typename U>
    void display(U datatype)
    {
        std::cout << datatype << ": " << data << std::endl;
    }
};

int main()
{
    // Instantiate MyClass with int data type
    // intObj is an object variable
    MyClass<int> x(42); //  initializes the data member of intObj to 42
    x.display("Integer");

    // Instantiate MyClass with double data type
    MyClass<double> y(3.14);
    y.display("Double");

    return 0;
}
