

#ifndef TRIANGULARMATRIX_H
#define	TRIANGULARMATRIX_H

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template<class T>
class TriangularMatrix {
public:

    TriangularMatrix(int nCols);
    virtual ~TriangularMatrix();

    //Function Prototypes
    void printRowLengths();
    void prntMatrix();
private:
    int numRows;
    int* RowLens;
    T **matrix;
    int *initRows(int rows);
    T **filAray(int* rowLength, int nRows);


};

#endif	/* TRIANGULARMATRIX_H */

/**
 * constructor
 * @param nRows
 */
template<class T>
TriangularMatrix<T>::TriangularMatrix(int nRows) :
numRows(nRows) {
    srand(static_cast<unsigned int> (time(0)));
    RowLens = initRows(numRows);
    matrix = filAray(RowLens, numRows);

}

/**
 * Generates an array of row sizes in incrementing values given the rows
 * parameter 
 * @param number of rows to generate
 * @return array of row sizes in incrementing values
 */
template<class T>
int* TriangularMatrix<T>::initRows(int rows) {
    int *array = new int[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = i + 1;
    }

    return array;
}

/**
 * 
 * @param rowLength
 * @param nRows
 * @return 
 */
template<class T>
T ** TriangularMatrix<T>::filAray(int* rowLength, int nRows) {
    T ** array = new T*[nRows];

    //allocate memory
    for (int i = 0; i < nRows; i++) {//for each row
        array[i] = new T[rowLength[i]]; //allocate row length
    }

    //fill the array
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < rowLength[row]; col++) {
            array[row][col] = static_cast<T> (
                    static_cast<float> (rand()) /
                    (static_cast<float> (RAND_MAX / (100)))
                    ); //random float from 0 - 100 then cast to template
        }//end col loop 
    }//end row loop

    return array;
}

/**
 * print the row lengths of the matrix
 */
template<class T>
void TriangularMatrix<T>::printRowLengths() {
    cout << endl;
    for (int i = 0; i < numRows; i++) {
        cout << RowLens[i] << " ";
    }
}

/**
 * print the values of the triangular matrix
 */
template<class T>
void TriangularMatrix<T>::prntMatrix() {
    cout<<endl;
    for(int row = 0; row < numRows; row++){
        for(int col = 0; col < RowLens[row]; col++){
            cout<<matrix[row][col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

/**
 * destructor class
 */
template<class T>
TriangularMatrix<T>::~TriangularMatrix(){
    delete RowLens;
    for (int i = 0; i < numRows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

}