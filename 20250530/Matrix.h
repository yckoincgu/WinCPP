#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template <typename T>
class Matrix {
public:
    T **matrix;     // Pointer to a 2D array (matrix)
    int rows, columns;  // Rows = n, Columns = m

    // Constructor to initialize the matrix with dimensions n x m
    Matrix(int n, int m) : rows(n), columns(m) {
        matrix = new T*[n];
        for (int i = 0; i < n; ++i) {
            matrix[i] = new T[m];
        }
        int k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = k++;
            }
        }
    }

    // Destructor to delete dynamically allocated memory
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Print matrix dimensions
    void printMatrixDimension() {
        std::cout << "Matrix dimensions: n = " << rows << ", m = " << columns << std::endl;
    }

    // Print matrix elements
    void printMatrix() {
        std::cout << "Matrix elements:" << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Template class AxB that multiplies two Matrix objects
template<typename T>
class AxB {
public:
    T **C;    // Resultant matrix
    int rows, columns, p;    // Dimensions of the matrices involved

    // Constructor that multiplies two Matrix objects a and b
    AxB(Matrix<T>& a, Matrix<T>& b) : rows(a.rows), columns(a.columns), p(b.columns) {
        // Check if matrices a and b can be multiplied
        if (a.columns != b.rows) {
            std::cout<< "Matrices cannot be multiplied: dimensions mismatch";
        }

        // Allocate memory for matrix C
        C = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            C[i] = new T[p];
        }

        // Perform matrix multiplication and store result in C
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < p; ++j) {
                C[i][j] = 0;
                for (int k = 0; k < a.columns; ++k) {
                    C[i][j] += a.matrix[i][k] * b.matrix[k][j];
                }
            }
        }
    }

    // Destructor to delete dynamically allocated memory
    ~AxB() {
        for (int i = 0; i < rows; ++i) {
            delete[] C[i];
        }
        delete[] C;
    }
};

#endif // MATRIX_H