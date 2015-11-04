

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TriangularMatrix.h"

using namespace std;

//User Libraries

//Global Constants



/*
 * 
 */
int main(int argc, char** argv) {
    
    cout<<"Integer Matrix\n";
    TriangularMatrix<int> intMatrix(10);
    intMatrix.printRowLengths();
    intMatrix.prntMatrix();
    
    cout<<"Float Matrix\n";
    TriangularMatrix<float> floatMatrix(15);
    floatMatrix.printRowLengths();
    floatMatrix.prntMatrix();
    
    cout<<"Double Matrix\n";
    TriangularMatrix<double> doubleMatrix(5);
    doubleMatrix.printRowLengths();
    doubleMatrix.prntMatrix();
    
    
    
    return 0;
}
