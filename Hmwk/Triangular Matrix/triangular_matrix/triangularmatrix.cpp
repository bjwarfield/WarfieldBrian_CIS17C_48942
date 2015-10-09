#ifndef TRIANGULARMATRIX_H
#define TRIANGULARMATRIX_H

template <class T>
class TriangularMatrix
{
private:
    //class private members
    TriangularMatrix();
    int cols;
    int* d1Array;
    int** d2Array;


    //Function Prototypes
    int *filAray(int);
    int **filAray(int*,int);
    void prntAry(int *,int);
    void prntAry(int **,int *,int);


public:
    TriangularMatrix(int cols);

    //deconstructor
    ~TriangularMatrix();
};

#endif // TRIANGULARMATRIX_H

TriangularMatrix::TriangularMatrix(int cols)
{
    this->cols = cols;

    init();
}

void TriangularMatrix::init()
{
    d1Array = *fillArray(cols);
}

