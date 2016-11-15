/**
 
 Name : Sahar Kausar Hussain
 
 UF ID: 30887953
 
 Gator ID: sahar.kausar
 
 Discussion section # : 1087
 
 
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