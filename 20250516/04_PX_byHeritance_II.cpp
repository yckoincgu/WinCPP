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
        std::cout<<std::endl;
	}
	
	void deleteMatrix(){
	    for (int i = 0; i < rows; ++i) delete[] A[i]; // Release memory and Ball destruBtor 
		delete[] A; // Release memory and Ball destruBtor		
	} 
    virtual ~Matrix() {
        std::cout << "Person Virtual destructor called for: " << std::endl;
    }	
};


template<typename T>            // This template is necessary due to parent
class AxB: public Matrix<T>{    // public Matrix<T> inherited from parent
	public:
	//int rows,columns;
	AxB(Matrix<T>& a, Matrix<T>& b) : Matrix<T>(a.rows, b.columns)  // parent constructor
    {        
		a.printMatrixDimension();   // passing by reference
		a.printMatrix();
		b.printMatrixDimension();
		b.printMatrix();

        this->rows=a.rows; this->columns=b.columns;     // inherited from parent by using "this" to make deferring
			
		for(int i=0; i<this->rows; i++){
			for(int j=0; j<this->columns; j++){
				this->A[i][j]=0;                // Before instantiation, template data type is unknown; 
                                                // At instantiation, it is known by deferring parent A
				for(int k=0; k<a.columns; k++)
					this->A[i][j] +=a.A[i][k]*b.A[k][j];
			}
		}

        std::cout<<"The result of A x B is "<<std::endl;
		this->printMatrix();
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
