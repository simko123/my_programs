#include <iostream>

class Vector {
public:
    inline static unsigned count;
    
    Vector(unsigned d, double *values);
    Vector(const Vector &vec);
    Vector();
    ~Vector();

    friend std::ostream& operator<< (std::ostream &out, const Vector &vec);
    Vector operator+ (const Vector &vec);
    Vector operator- (const Vector &vec);
    Vector operator- ();
    Vector operator= (const Vector &vec);
    double operator* (const Vector &vec);

private:
    unsigned dim, number;
    double *val;
};

Vector::Vector(unsigned d, double *values) {
    dim = d;
    val = new double[d];
    for (int i = 0; i < d; ++i) val[i] = values[i];
    number = ++count;
}

Vector::Vector(const Vector &vec) {
    for (unsigned i = 0; i < vec.dim; ++i) val[i] = vec.val[i];
    dim = vec.dim;
    number = ++count;
}

Vector::~Vector() {
    delete[] val;
}

std::ostream& operator<< (std::ostream &out, const Vector &vec) {
    out << "Vector #" << vec.number << " (";
    for (unsigned i = 0; i < vec.dim - 1; ++i) out << vec.val[i] << ", ";
    out << vec.val[vec.dim - 1];
    out << ")";
    return out;
}

Vector Vector::operator+ (const Vector &vec) {
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

Vector Vector::operator- (const Vector &vec) {
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

double Vector::operator* (const Vector &vec) {
    if (dim != vec.dim) {
        throw std::exception();
    } else {
        double result = 0;
        for (unsigned i = 0; i < dim; ++i) result += val[i] * vec.val[i];
        return result;
    }
}

Vector Vector::operator= (const Vector &vec) {
    return Vector(vec);
}

int main() {
    double val1[3] = {1,2,3},
           val2[3] = {8,3,2.5},
           val3[2] = {10,10},
           val4[3] = {7,9,2};
    Vector v1(3, val1),
           v2(3, val2),
           v3(2, val3),
           v4(3, val4);
    
    std::cout << 
        v1 << " + " << v2 << " = " << v1 + v2 << std::endl << 
        v4 << " - " << v2 << " = " << v4 - v2 << std::endl <<
        v1 << " * " << v4 << " = " << v1 * v4 << std::endl <<
        "-" << v3 << " = " << -v3 << std::endl <<
        "Copying v3 ..." 
    << std::endl;
    
    Vector v5 = v3;
    std::cout << v3 << std::endl << v5 << std::endl;
        
    return 0;
}