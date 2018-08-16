/*Program name and exercise number: Ex4*/

/*
Date: 05/01/2018
Author: Racheli Verechzon
Id:305710071
*/


/*************************************************************************************************************************
In this program, we will implement a matrix with a similar interface to that of the previous matrix (exercise number 3), but is implemented in a different matrix. The realization of all the interface functions that were in the class plus some functions and updates will be shown below. The savings will be expressed when the matrix is sparse, meaning that it contains a relatively small number of organs that are different from zero. In order to save memory space, we will not use a two-dimensional array, but rather a data structure that preserves only the various objects from zero - hence the name is a thin matrix.
*************************************************************************************************************************/
#define RESET 0 //The constant will be used as a zero         
#include "SMatrix.h"
#include<iostream>
using namespace std;
MNode::MNode(int i, int j, double data)
{
	_data = data;
	_indexI = i;
	_indexJ = j;
	_nextRow = NULL;
	_nextCol = NULL;
}

//--------------------------------------------------------------------------------------------------------
/* construct a 'rows X cols' matrix with matType*/
SMatrix::SMatrix(int rows, int cols, string matType)
{
	if (rows > RESET && cols > RESET &&( matType == "any" || matType == "Toeplitz" || matType == "Arrowhead"))
	{
		_rowSize = (rows);
		_colSize = (cols);
		_matType = (matType);
		initialize(rows, cols, matType);
	}
	else
	{
		cout << "The values entered are incorrect" << endl;
		return;
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
/*******************************************************
For the Copy constructor                                       *
Gets SMatrix & other and copies its contents to This   *
*******************************************************/
void SMatrix::copy( SMatrix & other)
{
	initialize(other._rowSize,other._colSize,other._matType);
	for (int i = RESET; i < other._rowSize; i++)
	{
		MNode* rowsPtr = other._rowHead[i];
		while (rowsPtr != NULL)
		{
			this->setElement(i, rowsPtr->_indexJ, other.getElement(i, rowsPtr->_indexJ));
			rowsPtr = rowsPtr->_nextRow;
		}
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
/****************************************
Returns the amount of storage space used*
*****************************************/
void SMatrix::sizeInBytes()
{
	cout <<"The Size in bytes:";
	cout <<( sizeof(SMatrix) + (sizeof(MNode)*(_elemNum)) + (sizeof(MNode*))*(_rowSize+ _colSize));
}
//-------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------
/**************************rowShift******************************************************************************
Performs cyclic movement of the rows in the matrix                                                              *
The function receives a shiftSize value from the receiver and we will then decide how much the matrix will move *
*****************************************************************************************************************/
void SMatrix::rowShift(const int shiftSize)
{
	int row = _rowSize, col = _colSize;
	if ((this->_matType == "any" || (col == 2 && row == 2)))
	{
		int shiftSize_temp = shiftSize,elementN =_elemNum;
		double **temp = Generate_Matrix(row, col);
		double **temp3 = Generate_Matrix(row,col);
		double** thisMatrix = basic_Matrix(temp3,*this);
		initialize(row, col, _matType);
		while (shiftSize_temp < 0)
		{
			shiftSize_temp += row;
		}
		for (int i = RESET; i < col; ++i)
		{
			for (int j = RESET; j < row; ++j)
			{
				double element = thisMatrix[j][i];
				temp[(j + shiftSize_temp) % (row)][i] = element;
			}
		}
		for (int i = RESET; i < _rowSize; i++)
		{
			for (int j = RESET; j < _colSize; j++)
			{
				if (temp[i][j] != RESET)
				{
					MNode *curNode = new MNode(i, j,temp[i][j]);
					insertNode(curNode,*this);
				}
			}
		}
		_elemNum = elementN;
		clearBasicMatrix(temp);
		clearBasicMatrix(thisMatrix);
	}
	else
		cout << "";
}
//----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
/******************************colShift*************************************************************************
Performs cyclic movement of the columns in the matrix                                                          *
The function receives a shiftSize value from the receiver and we will then decide how much the matrix will move*
****************************************************************************************************************/
void SMatrix::colShift(const int shiftSize)
{
	int row = _rowSize, col = _colSize;
	if ((this->_matType == "any"))
	{
		int shiftSize_temp = shiftSize, elementN = _elemNum;
		double **temp = Generate_Matrix(row, col);
		double **temp3 = Generate_Matrix(row, col);
		double** thisMatrix = basic_Matrix(temp3, *this);
		initialize(row, col, _matType);
		while (shiftSize_temp < RESET)
		{
			shiftSize_temp += col;
		}
		for (int i = RESET; i < row; ++i)
		{
			for (int j = RESET; j < col; ++j)
			{
				double element = thisMatrix[i][j];
				temp[i][(j + shiftSize_temp) % (col)] = element;
			}
		}
		for (int i = RESET; i < _rowSize; i++)
		{
			for (int j = 0; j < _colSize; j++)
			{
				if (temp[i][j] != RESET)
				{
					MNode *curNode = new MNode(i, j, temp[i][j]);
					insertNode(curNode, *this);
				}
			}
		}
		_elemNum = elementN;
		clearBasicMatrix(temp);
		clearBasicMatrix(thisMatrix);
	}
	else
		cout << "";
}
//-----------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------
/****************************add*****************************************************************************************
The function accepts  reference to matrice and makes a connection between the current and the other matrix and the result* retains the result matrix                                                                                             *
*************************************************************************************************************************/
SMatrix SMatrix::operator+(SMatrix & other)
{
	if ((this->_rowSize != other._rowSize) || this->_colSize != other._colSize)
	{
		cout << "NA The size of the matrices other and this is different and therefore the action was not performed_1" << endl;
		exit(1);
	}
	else if ((other._matType) !=this->_matType)
	{
		cout << "NA The Type  of the matrices is different and therefore the action was not performed_Arrowhead" << endl;
		exit(1);
	}
	double calculate = RESET;
	double **temp1 = Generate_Matrix(_rowSize, _colSize);
	double **temp2 = Generate_Matrix(_rowSize, _colSize);
	double **resultMatrix = Generate_Matrix(_rowSize, _colSize);
	double** thisMatrix = basic_Matrix(temp1,*this);
	double** otherMatrix = basic_Matrix(temp2,other);
	
	SMatrix result = SMatrix(_rowSize, _colSize, _matType);

	for (int i = RESET; i < _rowSize; i++)
	{
		for (int j = RESET; j < _colSize; j++)
		{
			calculate = otherMatrix[i][j] + thisMatrix[i][j];
			resultMatrix[i][j] = calculate;
		}
	}
	initialize(_rowSize,_colSize,_matType);
	for (int i = RESET; i < _rowSize; i++)
	{
		for (int j = RESET; j < _colSize; j++)
		{
			result.setElement(i, j, resultMatrix[i][j]);
		}
	}
	clearBasicMatrix(resultMatrix);
	clearBasicMatrix(thisMatrix);
	clearBasicMatrix(otherMatrix);
	return result;
}
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
/*****************************getElement*******************************************************************************
Returns the value of the element  of matrix (i, j) in case the idanx exceeds the matrix size, we print "exit" and exit* with NA for the screen                                                                                              *
***********************************************************************************************************************/
double SMatrix::getElement(int i, int j)
{
	if ((i < this->_rowSize) && (j < this->_colSize) && i>=0 && j>=0) 
	{
		if (IsExist(i,j))
		{
			MNode *ptr = _rowHead[i];


			while (ptr && ptr->_indexJ != j)
				ptr = ptr->_nextRow;

			if (ptr->_indexJ == j)
				return ptr->_data;
		}
		return RESET;
	}
	else
	{
		cout <<endl<< "NA";
		exit(1);
	}
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
/****************
Copy constructor*
*****************/
SMatrix::SMatrix(SMatrix & other)
{
	copy(other);
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
/*********************************setElement*****************************************************************************
Gets index of row i and value j, index of column. The function inserts the assignment value data into the element (of the matrix i, j)
*************************************************************************************************************************/
void SMatrix::setElement(int i, int j, double data)
{
	if (i < RESET || j < RESET || i >= _rowSize || j >= _colSize)
	{
		cout << "index error,Operation not executed The program will continue as usual" << endl;
		return;
	}
	bool found = IsExist(i, j);
	if (data == RESET && found == true) {
		if(actionPerformed2(i,j))
		removeElement(i, j);
	}
	if (data == RESET && found == false) {
		return;
	}
	if (data != RESET && found == true) {
		if (actionPerformed3(i, j))
		updateValue(i, j, data);
	}
	if (data != RESET && found == false) {
		if (actionPerformed3(i, j))
		{
			MNode *curNode = new MNode(i, j, data);
			insertNode(curNode,*this);
			_elemNum++;
		}
	}
}
//-----------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------
/***********************~Matrix*************************************
Deals with the elimination and orderly release of the matrix memory*
********************************************************************/
SMatrix::~SMatrix()
{
	clear();
}
//-----------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------
/*******************************isA****************************************************************
matType of Matrix Can be one of the three values mentioned. If the matrix  true in the constructor*
 This means that the function satisfies the conditions of the type on which it is registered      *
 **************************************************************************************************/
//------------------------------------------------------------------------------------------------------
bool SMatrix::isA(string matType)
{
	if (matType == "Arrowhead")
	{
		for (int i = RESET; i < this->_rowSize; i++)
		{
			MNode* rowsPtr = _rowHead[i];
			while(rowsPtr!=NULL)
			{
				if ((rowsPtr->_indexJ == RESET || rowsPtr->_indexI == RESET) || (rowsPtr->_indexJ == rowsPtr->_indexI))
				{
					//cout << "(" << i << "," << j << ")" << endl;
				}
				else
				{
					if (rowsPtr->_data != RESET)
					{
					//	cout << "false" << endl;
						return false;
					}
				}
				rowsPtr = rowsPtr->_nextRow;
			}
		}
		//cout << "true" << endl;
		return true;
	}
	else if (matType == "any")
	{
		//cout << "true" << endl;
		return true;
	}
	else if (matType == "Toeplitz")
	{
		return baseToepliz();
	}
	else
	{
		//cout << "false__" << endl;
		return false;
	}
}
//--------------------------------------------------------------------------------



//--------------------------------------------------------------------------------
/***************************************************************************************
- Prints all the columns of the matrix in the form of threaded lists of indexes of rows*
containing different organs from zero.                                                 *
****************************************************************************************/
void SMatrix::printColumnsIndexes()
{
	MNode* p;
	for (int i = RESET; i < _colSize; i++)
	{
		p = p = _colHead[i];
		cout << endl << i << ": ";

		while (p != NULL)
		{
			cout << "(" << p->_indexI << "," << p->_data << ")->";
			p = p->_nextCol;
		}
	}
	cout << endl;
}
void SMatrix::printRowsIndexes()
{
	MNode* p;
	for (int i = RESET; i < _rowSize; i++)
	{
		p = _rowHead[i];
		cout << endl << i << ": ";

		while (p != NULL)
		{
			cout << "(" << p->_indexJ << "," << p->_data << ")->";
			p = p->_nextRow;
		}
	}
	cout << endl;
}
//--------------------------------------------------------------------------------
/***********************************************************************************
A private method for the printing function that deals with endpoints to zero values*
************************************************************************************/
void printZero(int num, int cur, int end)
{
	for (int i = RESET; i < num; i++)
	{
		if (cur < end)
		{
			cout << "0,";
			cur++;
		}
		else
			cout << "0";
	}

}
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------

SMatrix & SMatrix::operator=(SMatrix & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
/********************************print**********************************************************************************
Prints the matrix in the following format: The matrix will be printed  Line by line - Each line in the matrix will start* with a new row on the screen. When between the two members of the same line the character will appear only and without* any space.                                                                                                            *
*************************************************************************************************************************/
ostream& operator<<(ostream& os, const SMatrix& mat)
{
	int curIndex = RESET, lastIndex, beginningIndex;
	for (int i = RESET; i < mat._rowSize; i++)
	{
		lastIndex = -1;
		MNode* p = mat._rowHead[i];
		if (p == NULL)
			printZero(mat._colSize - lastIndex - 1, RESET, mat._colSize - 1);
		else if (p->_indexJ == mat._colSize - 1)
		{
			printZero(p->_indexJ, RESET, p->_indexJ);
			cout << p->_data;
		}
		else
		{
			beginningIndex = RESET;
			while (p!=NULL)
			{
				curIndex = p->_indexJ;

				printZero(curIndex - lastIndex - 1, beginningIndex, curIndex);
				if (curIndex < mat._colSize - 1)
					cout << p->_data << ",";
				else
					cout << p->_data;

				beginningIndex = p->_indexJ;
				lastIndex = p->_indexJ;
				p = p->_nextRow;
			}
			beginningIndex++;
			printZero(mat._colSize - beginningIndex, beginningIndex, mat._colSize - 1);
		}
		cout << endl;
	}
	return os;
}

//--------------------------------------------------------------------------------
/*For the Constructo*/
void SMatrix::initialize(int rows, int cols, string matType)
{
	_matType = matType;
	_rowSize = rows;
	_colSize = cols;
	_elemNum = RESET;
	_colHead = new MNode*[cols];
	if (!_colHead)
	{
		cout << "allocation error"<<endl;
		exit(1);
	}
	_rowHead = new MNode*[rows];
	if (!_rowHead)
	{
		cout << "allocation error" << endl;
		exit(1);
	}
	for (int i = RESET; i < rows; i++)
	{
		_rowHead[i] = NULL;
	}
	for (int i = RESET; i < cols; i++)
	{
		_colHead[i] = NULL;
	}
}
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
/*For the Destructo*/
void SMatrix::clear()
{
	if (_elemNum != RESET)
	{
		for (int i = RESET; i < this->_rowSize; i++)
		{
			MNode *p = this->_rowHead[i], *p2;
			while (p != NULL)
			{
				p2 = p;
				p = p->_nextRow;
				delete p2;
			}
		}
	}
	delete[] this->_colHead;
	delete[] this->_rowHead;
}


/**********************************for SetElement Method***********************************/
void SMatrix::removeElement(int i, int j)
{
	MNode* prev = NULL;
	MNode* colPtr = _colHead[j];
	MNode* rowPtr = _rowHead[i];

	if (_colHead[j]->_indexI == i)
		_colHead[j] = _colHead[j]->_nextCol;

	else
	{
		while (colPtr && colPtr->_indexI != i)
		{
			prev = colPtr;
			colPtr = colPtr->_nextCol;
		}
		prev->_nextCol = colPtr->_nextCol;
	}
	if (_rowHead[i]->_indexJ == j)
		_rowHead[i] = _rowHead[i]->_nextRow;

	else
	{
		while (rowPtr && rowPtr->_indexJ != j)
		{
			prev = rowPtr;
			rowPtr = rowPtr->_nextRow;
		}
		prev->_nextRow = rowPtr->_nextRow;
	}

	delete rowPtr;
}
void SMatrix::insertNode(MNode *n,SMatrix &m)
{
	MNode* p = m._rowHead[n->_indexI];
	if (p != NULL)
	{
		if (n->_indexJ < p->_indexJ)
		{
			n->_nextRow = p;
			m._rowHead[n->_indexI] = n;

		}
		else
		{
			while (p->_nextRow && p->_nextRow->_indexJ < n->_indexJ)
				p = p->_nextRow;

			n->_nextRow = p->_nextRow;
			p->_nextRow = n;
		}
	}
	else                            // row is empty
		m._rowHead[n->_indexI] = n;

	p = m._colHead[n->_indexJ];       // the j column
	if (p != NULL)
	{
		if (n->_indexI < p->_indexI)
		{
			n->_nextCol = p;
			m._colHead[n->_indexJ] = n;
		}
		else
		{
			while (p->_nextCol && p->_nextCol->_indexI < n->_indexI)
				p = p->_nextCol;


			n->_nextCol = p->_nextCol;
			p->_nextCol = n;
		}
	}
	else                            // column is empty
		m._colHead[n->_indexJ] = n;
}
//------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
/*Boolean method that checks whether an element exists or not*/
bool SMatrix::IsExist(int i, int j)
{
	MNode *ptr = _rowHead[i];

	if (ptr == NULL)
		return false;

	while (ptr && ptr->_indexJ < j)
		ptr = ptr->_nextRow;

	if (ptr && ptr->_indexJ == j)
		return true;

	return false;
}
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
/*A private method that updates the value of an element*/
void SMatrix::updateValue(int i, int j, double data)
{
	MNode *p = _rowHead[i];//_rowHead[i]
	while (p->_indexJ != j)
		p = p->_nextRow;
	p->_data = data;
}


//------------------------------------------------------------------------------------------------
/*Check whether the element has passed the conditions*/
bool SMatrix::isToepliz(double **temp)
{
	for (int i = RESET; i < _rowSize - 1; i++)
	{
		for (int j = RESET; j < _colSize - 1; j++)
		{
			if (temp[i][j] != temp[i + 1][j + 1])
			{
				{
					//cout << "false__";
					return false;
				}
			}
		}
	}
	//cout << "true";
	return true;
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
A private method for the setElement functionchecks whether the matrix is a toplitz and an arrow and then decides whether to return truth or falsehood******************************************************************************************/
bool SMatrix::actionPerformed3(int i, int j)
{
	if (this->_matType == "any")
		return true;
	else if ((this->_matType) == "Toeplitz")
	{
		if ((i == RESET && j == (this->_colSize) - 1) || (j == RESET && i == (this->_rowSize) - 1))
		{
			return true;
		}
	}
	else if (this->_matType == "Arrowhead")
	{
		if (i == RESET || j == RESET || i == j)
			return true;
	}
	cout << "NA The Type  of the matrices is different and therefore the action was not performed"<<endl;
	return false;
}


//------------------------------------------------------------------------------------------------
/*The same as the previous method only has different conditions*/
bool SMatrix::actionPerformed2(int i, int j)
{
	if (this->_matType == "any" || this->_matType == "Arrowhead")
		return true;
	else if ((this->_matType) == "Toeplitz")
	{
		if ((i == RESET && j == (this->_colSize) - 1) || (j == RESET && i == (this->_rowSize) - 1))
		{
			return true;
		}
	}
	cout << "NA The Type  of the matrices is different and therefore the action was not performed_Topepltz"<<endl;
	return false;
}
//------------------------------------------------------------------------------------------------
/*fot the baseMatrix method*/
bool SMatrix::baseToepliz()
{
	bool top = false;
	double **temp = Generate_Matrix(_rowSize, _colSize);
	double** matrix =basic_Matrix(temp,*this);
	top = isToepliz(matrix);
	clearBasicMatrix(matrix);
	return top;
}
//------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
/*from Ex3 ___baseMatrix*/
/*Deals with the elimination and orderly release of the base matrix memory*/
void SMatrix::clearBasicMatrix(double** &temp)
{
	for (int i = RESET; i < _rowSize; i++)
	{
		delete[] temp[i];
	}
	delete[] temp;
}
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
/*from Ex3 ___baseMatrix*/
/*Generate Matrix base */
double ** SMatrix::Generate_Matrix(int rows, int cols)
{
	{
		if (rows > RESET && cols > RESET)
		{
			double **temp = new double*[rows];
			for (int i = RESET; i < rows; i++)
			{
				temp[i] = new double[cols];
			}
			for (int i = RESET; i <_rowSize; i++)
			{
				for (int j = RESET; j < _colSize; j++)
				{
					temp[i][j] = RESET;
				}
			}
			return temp;
		}
		else {
			cout << "NA Exceeding the boundaries of the matrix and therefore the action was not carried out"<<endl;
			exit(1);
		}
	}
}


double ** SMatrix::basic_Matrix(double ** temp,SMatrix &m)
{
	for (int i = RESET; i < m._rowSize; i++)
	{
		MNode* rowsPtr = m._rowHead[i];
		while (rowsPtr != NULL)
		{
			temp[i][rowsPtr->_indexJ] = rowsPtr->_data;
			rowsPtr = rowsPtr->_nextRow;
		}
	}
	return temp;
}
//------------------------------------------------------------------------------------------------



