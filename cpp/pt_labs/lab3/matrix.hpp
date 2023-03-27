#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "vector.hpp"

class Matrix {
    
public:

    inline static unsigned count;

    Matrix(unsigned squareSize, double** arr);
    Matrix(unsigned rows, unsigned columns, double** arr);
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

    unsigned    rows;
    unsigned columns;
    unsigned  number;
    double**     val;

    double rowProd(unsigned i);
    double colProd(unsigned j);

};

#endif