#include<iostream>
using namespace std;

// A node of a sparse matrix.  
class MNode {
	//friend class SMatrix;
public:

	double _data;
	int _indexI, _indexJ; // the place of the node in the matrix  
	MNode* _nextRow, *_nextCol;// clarification: _nextRow is a pointer to the next columns in the row
	MNode(int i, int j, double data);


};


// A sparse matrix. a mathematical matrix object which is implemented
// in a way that saves memory if the matrix is sparse. The implementation
// consists of /linked lists of elements which are not zero. 
class SMatrix {
	//friend class MNode;

private:
	MNode** _rowHead, **_colHead; // _rowHead : array of head-pointers for the rows lists. 
	int _rowSize, _colSize; // _rowSize - number of rows
	int _elemNum; // number of entries not containing zero 
	string _matType;

	
	bool IsExist(int, int);

	void updateValue(int, int, double);

	void insertNode(MNode*,SMatrix &m);

	void initialize(int, int,string);

	void copy( SMatrix& other);

	bool isToepliz(double **temp);

	double **basic_Matrix(double**,SMatrix &m);

	void removeElement(int, int);

	void clearBasicMatrix(double** &temp);

	bool baseToepliz();

	bool actionPerformed2(int, int);

	bool actionPerformed3(int, int);

	double **Generate_Matrix(int rows, int cols);
public:
	
	// SMatrix size in bytes
	void sizeInBytes();
	
	void rowShift(const int shiftSize);

	void colShift(const int shiftSize);
	
	// operator + for SMatrix
	SMatrix operator +(SMatrix& other);

	double getElement(int i, int j);

	SMatrix(SMatrix &other);

	// construct a 'rows X cols' matrix. 
	SMatrix(int rows, int cols, string matType);

	// set the (i,j) element to be 'data' 
	void setElement(int i, int j, double data);

	// destroy this matrix. 
	~SMatrix();

	bool isA(string matType);
	
	// print columns as linked lists
	void printColumnsIndexes();

	// print rows as linked lists
	void printRowsIndexes();

	friend ostream& operator<<(ostream& os, const SMatrix& mat);

	void clear();

	// operator = for SMatrix
	SMatrix& operator=(SMatrix &other);

};
