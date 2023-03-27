#include <iostream>

#include "matrix.hpp"
#include "vector.hpp"

Matrix::Matrix(uint squareSize, double** arr) {

    this->number = ++count;
    this->rows = squareSize;
    this->columns = squareSize;

    this->val = new double* [squareSize];
    for (uint i = 0; i < squareSize; ++i) this->val[i] = new double [squareSize];
    
    for (uint i = 0; i < squareSize; ++i) {
        for (uint j = 0; j < squareSize; ++j) {
            this->val[i][j] = arr[i][j];
        }
    }

    std::cout << "Matrix #" << this->number << " has been generated." << std::endl;
}

Matrix::Matrix(uint rows, uint columns, double** arr) {

    this->number = ++count;
    this->rows = rows;
    this->columns = columns;

    this->val = new double* [rows];
    for (uint i = 0; i < rows; ++i) this->val[i] = new double [columns];

    for (uint i = 0; i < rows; ++i) {
        for (uint j = 0; j < columns; ++j) {
            this->val[i][j] = arr[i][j];
        }
    }

    std::cout << "Matrix #" << this->number << " has been generated." << std::endl;
}

Matrix::Matrix(const Matrix& m) {

    this->number = ++count;
    this->rows = m.rows;
    this->columns = m.columns;

    this->val = new double* [rows];
    for (uint i = 0; i < rows; ++i) this->val[i] = new double [columns];

    for (uint i = 0; i < m.rows; ++i) {
        for (uint j = 0; j < m.columns; ++j) {
            this->val[i][j] = m.val[i][j];
        }
    }

    std::cout << "Matrix #" << this->number << " has been generated." << std::endl;
}

Matrix::~Matrix() {
    for (uint i = 0; i < rows; ++i) delete [] this->val[i];   
    delete [] this->val; 
    std::cout << "Matrix #" << this->number << " has been deleted." << std::endl;
}

Matrix Matrix::operator+ (const Matrix& m) {
    if (this->rows != m.rows || this->columns != m.columns) {
        throw std::exception();
    } else {
        double** result = new double* [m.rows];
        for (uint i = 0; i < rows; ++i) result[i] = new double [m.columns];
        for (uint i = 0; i < rows; ++i) {
            for (uint j = 0; j < columns; ++j) {
                result[i][j] = this->val[i][j] +
                                   m.val[i][j];
            }
        }
        return Matrix(m.rows, m.columns, result);
    }
}

Matrix Matrix::operator- (const Matrix& m) {
    if (this->rows != m.rows || this->columns != m.columns) {
        throw std::exception();
    } else {
        double** result = new double* [m.rows];
        for (uint i = 0; i < rows; ++i) {
            result[i] = new double [m.columns];
        }
        for (uint i = 0; i < rows; ++i) {
            for (uint j = 0; j < columns; ++j) {
                result[i][j] = this->val[i][j] -
                                   m.val[i][j];
            }
        }
        return Matrix(m.rows, m.columns, result);
    }
}

Matrix Matrix::operator- () {
    Matrix m(*this);
    for (uint i = 0; i < m.rows; ++i) {
        for (uint j = 0; j < m.columns; ++j) {
            m.val[i][j] = -(m.val[i][j]);
        }
    }
    return m;
}


double Matrix::rowProd(uint i) {
    double sum = 0;
    for (uint j = 0; j < this->columns; ++j) {
        sum += this->val[i][j];
    }
}

Matrix Matrix::operator* (const Matrix& m) {
    if (this->columns != m.rows) {
        throw std::exception();
    } else {

        double** result = new double* [this->rows];
        for (uint i = 0; i < this->rows; ++i) {
            result[i] = new double [m.columns];
        }

        for (uint i = 0; i < this->rows; ++i) {
            for (uint j = 0; j < m.columns; ++j) {
                result[i][j] = 0; // !
            }
        }
    }
}

// m*v

Matrix Matrix::operator* (double n) {
    Matrix m(*this);
    for (uint i = 0; i < m.rows; ++i) {
        for (uint j = 0; j < m.columns; ++j) {
            m.val[i][j] *= n;
        }
    }
    return m;
}