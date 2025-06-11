#include <iostream>

class Matrix {
public:
    int** A;  // The 2D array with heap storage
    int n, m; // Dimensions: rows (n) and columns (m)

    Matrix(int rows, int columns) : n(rows), m(columns) {
        A = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            A[i] = new int[columns];
        }
        int value = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                A[i][j] = value++;
            }
        }
    }

    void printMatrixDimension() const {
        std::cout << "The matrix dimensions n=" << n << " m= " << m << std::endl;
    }

    void printMatrix() const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << A[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void deleteMatrix() {
        for (int i = 0; i < n; ++i) {
            delete[] A[i];
        }
        delete[] A;
    }

    ~Matrix() {
        deleteMatrix();
    }
};

int main() {
    Matrix a(2, 3);
    a.printMatrixDimension();
    a.printMatrix();

    
    // std::cout<< a.A[1][1]<< std::endl;

    // Matrix destructor will automatically clean up the allocated memory
    return 0;
    // return 0; This signals the end of the main function.
    // As main (and specifically the block where a was declared) goes out of scope, 
    // the destructor for a (~Matrix()) is automatically invoked.
}
