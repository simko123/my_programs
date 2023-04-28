#include <iostream>

#include "matrix.hpp"
#include "vector.hpp"

<<<<<<< HEAD
unsigned Matrix::count = 0;

=======
>>>>>>> 7c088fcc5ecc3009bfac17245fac4ba7ed54bfd2
Matrix::Matrix(unsigned squareSize, double** arr) {

    this->number = ++count;
    this->rows = squareSize;
    this->columns = squareSize;

    this->val = new double* [squareSize];
    for (unsigned i = 0; i < squareSize; ++i) this->val[i] = new double [squareSize];
    
    for (unsigned i = 0; i < squareSize; ++i) {
        for (unsigned j = 0; j < squareSize; ++j) {
            this->val[i][j] = arr[i][j];
        }
    }
}

Matrix::Matrix(unsigned rows, unsigned columns, double** arr) {

    this->number = ++count;
    this->rows = rows;
    this->columns = columns;

    this->val = new double* [rows];
    for (unsigned i = 0; i < rows; ++i) this->val[i] = new double [columns];

    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < columns; ++j) {
            this->val[i][j] = arr[i][j];
        }
    }
}

Matrix::Matrix(const Matrix& m) {

    this->number = ++count;
    this->rows = m.rows;
    this->columns = m.columns;

    this->val = new double* [m.rows];
    for (unsigned i = 0; i < m.rows; ++i) this->val[i] = new double [m.columns];

    for (unsigned i = 0; i < m.rows; ++i) {
        for (unsigned j = 0; j < m.columns; ++j) {
            this->val[i][j] = m.val[i][j];
        }
    }
}

Matrix& Matrix::operator= (const Matrix& m) {
<<<<<<< HEAD
    std::cout << "RAVNOOOOOO\n";
=======
>>>>>>> 7c088fcc5ecc3009bfac17245fac4ba7ed54bfd2
    this->rows = m.rows;
    this->columns = m.columns;
    this->number = ++count;
    for (unsigned i = 0; i < this->rows; ++i) {
        for (unsigned j = 0; j < this->rows; ++j) {
            this->val[i][j] = m.val[i][j];
        }
    }
    return *this;
}

Matrix::~Matrix() {
    std::cout << "IMDYING\n";
    for (unsigned i = 0; i < rows; ++i) delete [] this->val[i];
    delete [] this->val;
}

Matrix Matrix::operator+ (const Matrix& m) {
    if (this->rows != m.rows || this->columns != m.columns) {
        throw std::exception();
    } else {
        double** result = new double* [m.rows];
        for (unsigned i = 0; i < rows; ++i) result[i] = new double [m.columns];
        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j = 0; j < columns; ++j) {
                result[i][j] = this->val[i][j] +
                                   m.val[i][j];
            }
        }
        Matrix matrix(m.rows, m.columns, result);
        for (unsigned i = 0; i < this->rows; ++i) {
            delete [] result[i];
        }
        delete [] result;
        return matrix;
    }
}

Matrix Matrix::operator- (const Matrix& m) {
    if (this->rows != m.rows || this->columns != m.columns) {
        throw std::exception();
    } else {
        double** result = new double* [m.rows];
        for (unsigned i = 0; i < m.rows; ++i) {
            result[i] = new double [m.columns];
        }
        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j = 0; j < columns; ++j) {
                result[i][j] = this->val[i][j] -
                                   m.val[i][j];
            }
        }
        Matrix matrix(m.rows, m.columns, result);
        for (unsigned i = 0; i < m.rows; ++i) {
            delete [] result[i];
        }
        delete [] result;
        return matrix;
    }
}

Matrix Matrix::operator- () {
    Matrix m(*this);
    for (unsigned i = 0; i < m.rows; ++i) {
        for (unsigned j = 0; j < m.columns; ++j) {
            m.val[i][j] = -(m.val[i][j]);
        }
    }
    return m;
}


Vector Matrix::vectorRow(unsigned i) const {
    return Vector(this->columns, this->val[i]);
}

Vector Matrix::vectorCol(unsigned j) const {
    double* column = new double[this->rows];
    for (unsigned i = 0; i < this->rows; ++i) {
        column[i] = this->val[i][j];
    }
    Vector v(this->rows, column);
    delete [] column;
    return v;
}

Matrix Matrix::operator* (const Matrix& m) {
    if (this->columns != m.rows) {
        throw std::exception();
    } else {

        double** result = new double* [this->rows];
        for (unsigned i = 0; i < this->rows; ++i) {
            result[i] = new double [m.columns];
        }

        for (unsigned i = 0; i < this->rows; ++i) {
            for (unsigned j = 0; j < m.columns; ++j) {
                result[i][j] = this->vectorRow(i) * m.vectorCol(j);
            }
        }
        Matrix matrix(this->rows, m.columns, result);
        for (unsigned i = 0; i < this->rows; ++i) {
            delete [] result[i];
        }
        delete [] result;
        return matrix;
    }
}

Vector Matrix::operator* (const Vector& v) {
    if (this->rows != v.getDim()) {
        throw std::exception();
    } else {
        double* result = new double[this->rows];
        for (unsigned i = 0; i < this->rows; ++i) {
            result[i] = 0;
            for (unsigned j = 0; j < this->columns; ++j) {
                result[i] += this->val[i][j] * v.at(j);
            }
        }
        Vector vec(this->rows, result);
        delete[] result;
        return vec;
    }

}

Matrix Matrix::operator* (double n) {
    Matrix m(*this);
    for (unsigned i = 0; i < m.rows; ++i) {
        for (unsigned j = 0; j < m.columns; ++j) {
            m.val[i][j] *= n;
        }
    }
    return m;
}

void Matrix::print() {
    std::cout << "Matrix #" << this->number << std::endl;
    for (unsigned i = 0; i < this->rows; ++i) {
        for (unsigned j = 0; j < this->columns; ++j) {
            std::cout << this->val[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}