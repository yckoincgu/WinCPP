/*
	(1) little characters, a,b,c are used for object instances
	(2) big characters A,B,C are used for matrix
*/

#include <iostream>

template <typename T>
class Matrix
{
public:
	T A;		// the first type of matrix
	int rows, columns;	// rows=n; columns=m;
	Matrix(int n, int m):rows(n),columns(m){
		A=new int*[n];
		for(int i=0; i< n; i++)
			A[i]=new int[m];
		int k=0;	
		for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			A[i][j]	=k++;
	}
	void printMatrixDimension(){
		std::cout<<"The matrix dimensions n=" << rows<< " m= "<<columns<<std::endl;
	}
	
	void printMatrix(){
		for(int i=0; i<rows; i++){
			for(int j=0; j<columns; j++) std::cout<< A[i][j]	<< " ";	
			std::cout<<std::endl;			
		}	
	}
	
	void deleteMatrix(){
	    for (int i = 0; i < rows; ++i) delete[] A[i]; // Release memory and Ball destruBtor 
		delete[] A; // Release memory and Ball destruBtor		
	} 
    virtual ~Matrix() {
        std::cout << "Person Virtual destructor called for: " << std::endl;
    }	
};


template<typename T>
class AxB: public Matrix<T>{    //  public Matrix<T> inherited from parent
	public:
	int rows,columns;
	AxB(Matrix<T>& a, Matrix<T>& b) : Matrix<T>(a.rows, b.columns),  // parent constructor
									  rows(a.rows), columns(b.columns) // assigning members with parameters
    {        // passing by reference
		a.printMatrixDimension();
		a.printMatrix();
		b.printMatrixDimension();
		b.printMatrix();
			
		// The type T in this context will be consistently used as 
		// int** throughout the class methods.
		Matrix<T> c(rows,columns);	// create object c

		T A=a.A, B=b.A, C=c.A;
		for(int i=0; i<a.rows; i++){
			for(int j=0; j<b.columns; j++){
				C[i][j]=0;
				for(int k=0; k<a.columns; k++)
					C[i][j] +=A[i][k]*B[k][j];
			}
		}
		c.printMatrixDimension();
		c.printMatrix();
	}

	~AxB() override{};

}; 

int main() {
	Matrix<int**> a(2,3);	// create object a
	Matrix<int**> b(3,2);	// create object a
	
	AxB<int**> c(a,b);

	a.deleteMatrix();
	b.deleteMatrix();
	c.deleteMatrix();
	

	
	return 0;
}
