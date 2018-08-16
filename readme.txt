userName: rachelive
name: racheli verechzon id:305710071
***There is a need to open this document in notepad++ *******
**Please note! Wherever we were asked to perform the exit action, the program will exit the cmd**

In this exercise, we have the class that represents a mathematical matrix.
// A sparse matrix. a mathematical matrix object which is implemented
// in a way that saves memory if the matrix is sparse. The implementation
// consists of /linked lists of elements which are not zero. 
 The matrix support Several basic services:
 1) constructor that initializes the matrix
 1) zero_Matrix method that initializes the matrix,each cell to a zero, 
    in case this is not a quadratic matrix ( means that rows!=columns)
 1) Generate_Matrix method that create the wanted matrix
 2) constructor that is destroying the matrix.
 3) getElement method allows to get the values of wanted cell in the matrix
 4) set	Element method allows you to insert a value for a particular cell in the matrix.
 5) + add method will connect values of two matrices and returns the result in a new matrix.
	this method wiil check that is possible to connect this two matrices;
 6) rowShift method Performs ciclastic displacement of the lines in the mutation.
 7) colShift method that replace between the matrix's cols and rows
 8) bool isA Checks whether the matrix satisfies the setting set to its matType value.Can be one of three values ,Arrowhead,Topliz,any
And returns respectively true or false.
 9) << print method that print the wonted matrix
 10) sizeInBytes Returns the amount of storage space used
 11) printColumnsIndexes  Prints all the columns of the matrix in the form of threaded lists of indexes of rows*
containing different organs from zero.
 12) printRowIndexes
 13) SMatrix& operator = (const SMatrix& other) The positioning operator places the other in the present
 14)SMatrix(const SMatrix& other);   - copy constructor
** the set and get method will check that when we want to insert  data or get data of particular cell the user enter valid cell, if not the system wil exit(1) 


how the user  should to compile the program?.
 we create 2 files:
1. SMatrix.h 2. SMatrix.cpp and (readme). 
tou should compile all the 1 and 2 files together.
after saving each file on Visual studio 1. to the "Header Files" section 2. "source file" section  .
you will find this section at "Explorer solution" window.
all file will pass compiling.


how the user  should to compile the program?.
 we create 2 files that contains a file for the statements "SMatrix.h", a file for the functions realization "SMatrix.cpp" and a  The files need to be copied to Visual Studio. 
after saving each file you should  press  "bulid"->"bulid solution" and then compile by pressing "debug"->"Start without Debugging".

After these steps will open you a cmd window



The files are divided to files with extension ".h" and files with extension ".cpp"

in files with extension ".h" we :import the needed liberys to use of method
								 create  wanted class
								 declarations to methods that implementation  in the file with extension ".cpp" with the same name.
								 
in files with extension ".cpp" we	: import the file. h with the same name and implementate all  method that relate to the file


You should have a main.cpp for test the program we that will check all the matrix method and entring the need data for iinitializes the matrix

needed inpot :
if you use me main you should enter value for each cell in the matrix (accroding to  the num of thr matrix cells

needed outpot :
printed matrix ( depend on  runing method of the metrix)


 
	

