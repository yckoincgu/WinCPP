#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


using namespace std;

template <typename T>
class Matrix {
protected:
    T dynamicMatrix;
    int rows, columns;
    string errorInformation;
    
public:
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

    Matrix(int rows, int cols) : rows(rows), columns(cols) {
        dynamicMatrix = new int*[rows];
        for(int i = 0; i < rows; i++) {
            dynamicMatrix[i] = new int[columns];
            for(int j = 0; j < columns; j++) {
                dynamicMatrix[i][j] = 0;
            }
        }
    }

    // Add public accessor methods
    int getRows() const { return rows; }
    int getColumns() const { return columns; }
    T getMatrixData() const { return dynamicMatrix; }

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
    
    virtual ~Matrix() {
        for(int i = 0; i < rows; ++i) delete[] dynamicMatrix[i];
        delete[] dynamicMatrix;        
    }    
};

template<typename T>
class AxB : public Matrix<T> {
public:
    AxB(const Matrix<T>& a, const Matrix<T>& b) : 
        Matrix<T>(a.getRows(), b.getColumns()) {
            
        a.printMatrixDimension();
        a.printMatrix();
        b.printMatrixDimension();
        b.printMatrix();
            
        T A = a.getMatrixData();
        T B = b.getMatrixData();
        
        for(int i = 0; i < a.getRows(); i++) {
            for(int j = 0; j < b.getColumns(); j++) {
                this->dynamicMatrix[i][j] = 0;
                for(int k = 0; k < a.getColumns(); k++) {
                    this->dynamicMatrix[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    virtual ~AxB() {
        cout << "AxB destructor called" << endl;
    }
};

int main() {
    ifstream inputAfile("MatrixA.csv");
    ifstream inputBfile("MatrixB.csv");
    
    if(inputAfile.is_open() && inputBfile.is_open()) {
        Matrix<int**> a(inputAfile);
        Matrix<int**> b(inputBfile);
        
        AxB<int**> axb(a, b);
        axb.printMatrixDimension();
        axb.printMatrix();
        
        inputAfile.close();
        inputBfile.close();
    }
    return 0;
}