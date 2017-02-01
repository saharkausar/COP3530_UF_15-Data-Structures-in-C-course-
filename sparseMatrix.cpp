/*
 Created by Sahar Kausar (Fall 2015 COP3530 - Data Structures with C++)
 Please do not copy or redistribute without permission.
 
 Assignment: Sparse Matrix
 */

/**
 What the program does:
 
 Sparse matrices are matrices populated primarily with zeros. When storing and manipulating sparse matrices on a computer, it is beneficial and often necessary to use specialized algorithms and data structures that take advantage of the sparse structure of the matrix. The sparseMatrix data structure described as follows. Tbe sparseMatrix consists of an array of chains. Each chain holds the non-zero elements of the corresponding row in the matrix. These non-zero elements can be of type boolean or integer. All of the elements of the sparseMatrix must be of the same type,  i.e. a sparseMatrix cannot contain both integers and booleans.  Thus, the sparseMatrix class is templated.
 
 For the sparseMatrix data structure, the following is implemented: a constructor, destructor, print, read, and mask methods.
 -	The read function receives input from standard input (stdin) and creates a sparse matrix by assigning values to the internal structures of the matrix.
 -	The print function prints out the elements of the matrix, in the format shown in the example below.
 -	The sparseMatrix method mask(b,c), has an implicit third operand. The operand is this (the object invoking the method). The  mask(b,c) method stores the result of masking this and b into the sparseMatrix c.
 -	Masking a matrix is defined as follows:
 c(i,j) = a(i,j) if b(i,j) is true, and
 c(i,j) =0 otherwise,
 where b is a boolean sparse matrix, and a and b are integer sparse matrices.
 -	Explicitly instantiated two matrices with type int, and one matrix with type boolean. The main matrix and result matrix will contain integers.  The mask matrix will contain booleans.
 -	All matrices will have the same dimensions.
 
 -	Note: As you read in matrix b, you will read integer values from the input, but store boolean values into b. As you read in matrix a, you will read (and store) integer values.
 
 Example Run:
 
 OUTPUT>> Reading Matrix A
 OUTPUT>> Enter number of rows, columns
 USER INPUT>> 3 4
 OUTPUT>> Enter number of terms in row 1
 USER INPUT>> 1
 OUTPUT>> Enter element's column, and value of each term in row 1
 USER INPUT>> 1 111
 OUTPUT>> Enter number of terms in row 2
 USER INPUT>> 2
 OUTPUT>> Enter element's column, and value of each term in row 2
 USER INPUT>> 2 222 3 233
 OUTPUT>> Enter number of terms in row 3
 USER INPUT>> 0
 
 OUTPUT>> Matrix A:
 OUTPUT>> rows = 3 columns = 4
 OUTPUT>> row 1[ col:1 val= 111]
 OUTPUT>> row 2[ col:2 val= 222, col:3 val= 233]
 OUTPUT>> row 3[]
 
 OUTPUT>> Reading Matrix B
 OUTPUT>> Enter number of rows, columns
 USER INPUT>> 3 4
 OUTPUT>> Enter number of terms in row 1
 USER INPUT>> 1
 OUTPUT>> Enter element's column, and value of each term in row 1
 USER INPUT>> 1 1
 OUTPUT>> Enter number of terms in row 2
 USER INPUT>> 1
 OUTPUT>> Enter element's column, and value of each term in row 2
 USER INPUT>> 3 1
 OUTPUT>> Enter number of terms in row 3
 USER INPUT>> 0
 
 OUTPUT>> Matrix B, the boolean mask matrix:
 OUTPUT>> rows = 3 columns = 4
 OUTPUT>> row 1[ col:1 val= 1]
 OUTPUT>> row 2[ col:3 val= 1]
 OUTPUT>> row 3[]
 
 OUTPUT>> Matrix C, result:
 OUTPUT>> rows = 3 columns = 4
 OUTPUT>> row 1[ col:1 val= 111]
 OUTPUT>> row 2[ col:3 val= 233]
 OUTPUT>> row 3[]

 
 **/

/**
 How to Compile and Execute:
 
 Download the file to your desired root folder on your computer. Open the terminal or executable IDE program to compile and run the file. Enter the following in the quotes (make sure to omit the quotes): "g++ -o (desiredNameOfFile) sparseMatrix.cpp"
 
 For example, you may enter the following: "g++ -o sparseMatrix sparseMatrix.cpp"
 
 The program will then compile. Run the program by typing "./(desiredNameOfFile)"
 
 In the above example, you may have entered: "./sparseMatrix"
 
 The program will then run and the user may follow the prompt. Enjoy!
 
 **/

#include <iostream>
#include <string>

using namespace std;

template<class T>
class sparseMatrix {
	private:
		int row;
		int column;
		//Matrix of type T (will be int or bool)
	public:
        T ** Matrix;
		sparseMatrix(); //Constructor to create empty sparseMatrix
		~sparseMatrix(); //Destructor to delete sparseMatrix		
		void read(); //Read values into Matrix from stdin
		void print(); //Print out matrix to console
		void mask(sparseMatrix<bool>&, sparseMatrix<int>&); //Use the this operand to mask the matrix calling the method with the boolean matrix (i) and store the result (matrix j)
};

//Constructor to create empty sparseMatrix
template<class T>
sparseMatrix<T>::sparseMatrix() {
	
}

template<class T>
void sparseMatrix<T>::read() {
	
	string input;
	int numStart = 0;
	int numEnd = 0;

	int terms;
	int columnNumber;
	int value;	

	cout << "Enter number of rows, columns" << endl;
	cin >> row >> column;
	//cout << "Rows: " <<  row <<  "Columns: " << col << endl;

	//Matrix now points to an array of rows
	Matrix = new T*[row];

	//Create array with all 0 values
	for (int i = 0; i < row; i++) {
		//Initialize each row
		Matrix[i] = new T[column];

		for (int j = 0; j < column; j++)
		{
			Matrix[i][j] = 0;
		}
	}

	//Fill array with values
	for (int k = 0; k < row; k++)
	{
		cout << "Enter number of terms in row " << k + 1 << endl;
		cin >> terms;

		if (terms > 0)
		{
            
            cout << "Enter element's column, and value of each term in row " << k + 1 << "\n";
			for (int l = 0; l < terms; l++) {
				//cin.ignore(); //Ignore the newline character from cin >> terms;
				//getline(cin, input);
				//cout << input << " " << input.length() << endl;

				//for (int l = 0; l < input.length() << l++)
				//{

					cin >> columnNumber >> value;

					Matrix[k][columnNumber - 1] = value;
				//}
			}
		}
	}
}

template<class T>
void sparseMatrix<T>::print() {

	cout << "rows = " << row << " columns = " << column << endl;

	//Test printing the Matrix
	//for (int i = 0; i < row; i++) {
	//	for (int j = 0; j < column; j++)
	//	{
	//		cout << Matrix[i][j] << " ";
	//	}
	//	cout << "\n";
	//}

	for (int i = 0; i < row; i++) {
		
		cout << "row " << i + 1 << "[ ";

		for (int j = 0; j < column; j++)
		{			
			if (Matrix[i][j] != 0)
			{
				cout << " col:" << j + 1 << " val= " << Matrix[i][j] << ",";
			}
		}

		cout << "\b" << " ]\n"; //Move back one character and overwrite comma with closing bracket		
	}
}

template<class T>
void sparseMatrix<T>::mask(sparseMatrix<bool>& b, sparseMatrix<int>& c) {
 /**
    cout << " rows = " << row << " columns = " << column << endl;
    
    for (int i = 0; i < row; i++) {
        cout<< "sdf";
        cout << "row " << i + 1 << "[ ";
        
        for (int j = 0; j < column; j++)
        {
               // if there is a value in b
            if (b.Matrix[i][j] == true)
            {
                c.Matrix[i][j] = Matrix[i][j];
            }
            else{
                c.Matrix[i][j]=0;
  **/
}

//Destructor to delete sparse Matrix
template<class T>
sparseMatrix<T>::~sparseMatrix() {

	for (int i = 0; i < row; i++)
	{
		//Delete Matrix row by row
		delete[] Matrix[i];
	}
}

int main() {
	sparseMatrix<int> *a = new sparseMatrix<int>(); //Main Matrix
	sparseMatrix<bool> *b = new sparseMatrix<bool>(); //Mask Matrix
	sparseMatrix<int> *c = new sparseMatrix<int>(); //Result Matrix

	cout << "Reading Matrix A" << endl;
	a->read();	

	cout << endl;
	cout << "Matrix A:" << endl;
	a->print();
	
	cout << endl;
	cout << "Reading Matrix B" << endl;
	b->read();
	
	cout << endl;
	cout << "Matrix B, the boolean mask matrix:" << endl;
	b->print();
	
	//Masking

	a->mask(*b, *c);

	cout << "Matrix C, result:" << endl;
	//c->print();

	//cin.get();
	//cin.get();
	return 0;
}