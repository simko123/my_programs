#include <iostream>
#include "vector.hpp"

Vector::Vector(unsigned d, double *values) {
    this->dim = d;
    this->val = new double[d];
    for (int i = 0; i < d; ++i) val[i] = values[i];
    this->number = ++count;
}

Vector::Vector(const Vector& vec) {
    this->dim = vec.dim;
    this->number = ++count;
    this->val = new double[vec.dim];
    for (unsigned i = 0; i < vec.dim; ++i) {
        this->val[i] = vec.at(i);
    }
}

Vector::~Vector() {
    delete[] val;
}

std::ostream& operator<< (std::ostream& out, const Vector &vec) {
    out << "Vector #" << vec.number << " (";
    for (unsigned i = 0; i < vec.dim - 1; ++i) out << vec.val[i] << ", ";
    out << vec.val[vec.dim - 1];
    out << ")";
    return out;
}

Vector Vector::operator+ (const Vector& vec) {
    if (dim != vec.dim) {
        throw std::exception();
    } else {
        double newVal[vec.dim]; 
        for (unsigned i = 0; i < vec.dim; ++i) {
            newVal[i] = val[i] + vec.val[i];
        }
        return Vector(dim, newVal);
    }
}

Vector Vector::operator- (const Vector& vec) {
    if (dim != vec.dim) {
        throw std::exception();
    } else {
        double newVal[vec.dim]; 
        for (unsigned i = 0; i < vec.dim; ++i) newVal[i] = val[i] - vec.val[i];
        return Vector(dim, newVal);
    }
}

Vector Vector::operator- () {
    double newVal[dim];
    for (unsigned i = 0; i < dim; ++i) newVal[i] = -val[i];
    return Vector(dim, newVal);
}

double Vector::operator* (const Vector& vec) {
    if (dim != vec.dim) {
        throw std::exception();
    } else {
        double result = 0;
        for (unsigned i = 0; i < dim; ++i) result += val[i] * vec.val[i];
        return result;
    }
}

Vector& Vector::operator= (const Vector& vec) {
    this->dim = vec.dim;
    this->number = ++count;
    for (unsigned i = 0; i < this->dim; ++i) {
        this->val[i] = vec.val[i];
    }
    return *this;
}