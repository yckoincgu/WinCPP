// 01_inheritance.cpp
#include <iostream>
#include <string> // Required for std::string

// Base Class: Person
class Person {
public:
    // Data Members
    std::string name; // Every person has a name

    // Constructor for Person
    Person(const std::string& nameArg) : name(nameArg) {
        std::cout << "Person constructor called for: " << name << std::endl;
    }

    // Member Function
    void printName() const { // Added const correctness
        std::cout << "Name: " << name << std::endl;
    }

    // Virtual destructor for proper polymorphic cleanup (good practice in base classes)
    virtual ~Person() {
        std::cout << "Person Virtual destructor called for: " << name << std::endl;
    }
};

// Derived Class: Student
// Student inherits publicly from Person
class Student : public Person {
public:
    // Data Members specific to Student
    std::string id;
    std::string departmentId;

    // Constructor for Student
    // It must call the base class (Person) constructor
    Student(const std::string& name, const std::string& studentId, const std::string& deptId)
        : Person(name), // Call base class Person's constructor to initialize 'name'
          id(studentId),
          departmentId(deptId)
    {
        std::cout << "Student constructor called for: " << name << std::endl;
    }

    // Member Function specific to Student
    void printStudentInfo() const { // Added const correctness
        // Inherited members can be accessed directly or via base class method
        printName(); // Call inherited method to print name
        std::cout << "Student ID: " << id << std::endl;
        std::cout << "Department ID: " << departmentId << std::endl;
    }

    // Override base class destructor (good practice with virtual base destructor)
    ~Student() override {
        std::cout << "Student destructor called for: " << name << std::endl;
    }
};

int main() {
    // Create a Person object
    std::cout << "--- Creating a Person ---\n";
    Person p1("Alice Smith");
    p1.printName();
    std::cout << "\n";

    // Create a Student object
    // This calls the Person constructor first, then the Student constructor
    std::cout << "--- Creating a Student ---\n";
    Student s1("Bob Johnson", "S12345", "CS");
    s1.printStudentInfo(); // Calls Student-specific print function
    s1.printName();        // Can also call the inherited printName function
    std::cout << "\n";

    // Demonstrating polymorphism with a base class pointer
    std::cout << "--- Demonstrating Polymorphism ---\n";
    Person* p_ptr = &s1; // A Person pointer can point to a Student object
    p_ptr->printName();  // Calls Person's printName (or Student's if printName were virtual)
                         // Here, it calls Person::printName because printName is not virtual.
                         // If printName in Person was virtual and overridden in Student,
                         // it would call Student's version.

    // If we dynamically allocate, virtual destructors become critical
    std::cout << "\n--- Dynamic Allocation and Deallocation ---\n";
    Person* dynamicPerson = new Person("Charlie Brown");
    Person* dynamicStudent = new Student("Dana Scully", "XFiles", "FBI");

    dynamicPerson->printName();
    // dynamicStudent->printStudentInfo(); // ERROR: Person* doesn't know about Student-specific methods

    std::cout << "\nDeleting dynamically allocated objects:\n";
    delete dynamicPerson; // Calls Person destructor
    delete dynamicStudent; // Calls Student destructor, then Person destructor (due to virtual ~Person)

    std::cout << "\n--- Program End ---\n";
    return 0;
}