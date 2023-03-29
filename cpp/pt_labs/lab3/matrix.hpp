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
    Matrix operator* (double n);
    Matrix& operator= (const Matrix& m);

private:

    unsigned    rows;
    unsigned columns;
    unsigned  number;
    double**     val;

    Vector vectorRow(unsigned i) const;
    Vector vectorCol(unsigned j) const;

};

#endif