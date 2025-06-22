#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
class Matrix {
public:
    T dynamicMatrix;
    int rows, columns;
    string errorInformation;
    
    Matrix(std::ifstream& inputFile) {
        string line, word;
        rows = 0, columns = 0;
        bool firstLoop = true;
        
        while(getline(inputFile, line)) {
            int j = 0;
            istringstream iss(line); 
            while(getline(iss, word, ',')) if(!word.empty()) j++; 
            if(!firstLoop && columns != j) { errorInformation = "Invalid column count"; }
            if(firstLoop) { columns = j; firstLoop = false; }             
            rows++;
        }    

        dynamicMatrix = new int*[rows]; 
        for(int i = 0; i < rows; i++) dynamicMatrix[i] = new int[columns];

        inputFile.clear();
        inputFile.seekg(0, ios::beg);

        for(int i = 0; i < rows; i++) {
            getline(inputFile, line);
            istringstream iss(line); 
            for(int j = 0; j < columns; j++) {
                getline(iss, word, ',');
                if(!word.empty()) dynamicMatrix[i][j] = stoi(word);
            }
        }             
    }

    // Constructor for creating empty matrix
    Matrix(int rows, int cols) : rows(rows), columns(cols) {
        dynamicMatrix = new int*[rows];
        for(int i = 0; i < rows; i++) {
            dynamicMatrix[i] = new int[columns];
            for(int j = 0; j < columns; j++) {
                dynamicMatrix[i][j] = 0;
            }
        }
    }

    void printMatrixDimension() const {
        cout << "Matrix dimensions: " << rows << "x" << columns << endl;
    }
    
    void printMatrix() const {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) 
                cout << dynamicMatrix[i][j] << " ";    
            cout << endl;            
        }    
    }
    
    void deleteMatrix() {
        for(int i = 0; i < rows; ++i) delete[] dynamicMatrix[i];
        delete[] dynamicMatrix;        
    } 
    
    virtual ~Matrix() {
        deleteMatrix();
    }    
};

template<typename T>
class AxB {
private:
    Matrix<T> result;
    
public:
    AxB(Matrix<T>& a, Matrix<T>& b) : result(a.rows, b.columns) {
        a.printMatrixDimension();
        a.printMatrix();
        b.printMatrixDimension();
        b.printMatrix();
            
        T A = a.dynamicMatrix, B = b.dynamicMatrix;
        for(int i = 0; i < a.rows; i++) {
            for(int j = 0; j < b.columns; j++) {
                result.dynamicMatrix[i][j] = 0;
                for(int k = 0; k < a.columns; k++) {
                    result.dynamicMatrix[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    const Matrix<T>& getResult() const {
        return result;
    }

    void printResult() const {
        result.printMatrixDimension();
        result.printMatrix();
    }
};

int main() {
    ifstream inputAfile("MatrixA.csv");
    ifstream inputBfile("MatrixB.csv");
    
    if(inputAfile.is_open() && inputBfile.is_open()) {
        Matrix<int**> a(inputAfile);
        Matrix<int**> b(inputBfile);
        
        AxB<int**> axb(a, b);
        axb.printResult();
        
        inputAfile.close();
        inputBfile.close();
    }
    return 0;
}