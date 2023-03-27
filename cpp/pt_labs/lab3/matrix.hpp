#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "vector.hpp"

class Matrix {
    
public:

    inline static uint count;

    Matrix(uint squareSize, double** arr);
    Matrix(uint rows, uint columns, double** arr);
    Matrix(const Matrix& m);
   ~Matrix();

    void print();

    Matrix operator+ (const Matrix& m);
    Matrix operator- (const Matrix& m);
    Matrix operator- ();
    Matrix operator* (const Matrix& m);
    Vector operator* (const Vector& v);
    Matrix operator* (double num);
    Matrix operator= (const Matrix& m);

private:

    uint    rows;
    uint columns;
    uint  number;
    double** val;

    double rowProd(uint i);
    double colProd(uint j);

};

#endif