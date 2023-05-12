#include <iostream>
#include <cmath>

class Vector {
public:
    inline static unsigned count;
    
    Vector(double x, double y);
    Vector(double x, double y, double z);
    Vector(const Vector &vec);
    Vector(){};
    ~Vector(){};

    double scalarProd(const Vector& vec);
    double angleTo(const Vector& vec); // todo
    double mod();

    friend std::ostream& operator<< (std::ostream& out, const Vector& vec); 
    Vector operator+ (const Vector &vec);
    Vector operator- (const Vector &vec);
    Vector operator- ();
    Vector operator= (const Vector &vec);
    Vector operator* (const Vector &vec);

private:
    unsigned number;
    char dim;
    double x, y, z;
};

Vector::Vector(double x, double y) {
    this->dim = 2;
    this->x = x;
    this->y = y;
    this->number = ++count;
}

Vector::Vector(double x, double y, double z) {
    this->dim = 3;
    this->x = x;
    this->y = y;
    this->z = z;
    this->number = ++count;
}

Vector::Vector(const Vector& vec) {
    this->dim = vec.dim;
    this->x = vec.x;
    this->y = vec.y;
    if (vec.dim == 3) this->z = vec.z;
    this->number = ++count;
}

double Vector::scalarProd(const Vector& vec) {
    if (this->dim != vec.dim) {
        throw std::exception();
    } else {
        if (vec.dim == 2) {
            return this->x * vec.x + this->y * vec.y;
        } else if (vec.dim == 3) {
            return this->x * vec.x + this->y * vec.y + this->z * vec.z;
        }
    }
}

double Vector::mod() {
    return sqrt(x*x + y*y + z*z);
}

std::ostream& operator<< (std::ostream& out, const Vector& vec) {
    out << "Vector #" << vec.number << " (" <<
    vec.x << ", " << vec.y;
    if (vec.dim == 3) out << ", " << vec.z;
    out << ")";
    return out;
}

Vector Vector::operator+ (const Vector& vec) {
    if (this->dim != vec.dim) {
        throw std::exception();
    } else {
        double x = this->x + vec.x,
               y = this->y + vec.y;
        if (vec.dim == 3) {
            double z = this->z + vec.z;
            return Vector(x, y, z);
        } else {
            return Vector(x, y);
        }
    }
}

Vector Vector::operator- (const Vector& vec) {
    if (this->dim != vec.dim) {
        throw std::exception();
    } else {
        double x = this->x - vec.x,
               y = this->y - vec.y;
        if (vec.dim == 3) {
            double z = this->z - vec.z;
            return Vector(x, y, z);
        } else {
            return Vector(x, y);
        }
    }
}

Vector Vector::operator- () {
    if (this->dim == 2) {
        return Vector(-this->x, -this->y);
    } else if (this->dim == 3) {
        return Vector(-this->x, -this->y, -this->z);
    }
}

Vector Vector::operator* (const Vector& vec) {
    double i, j, k;
    i =   this->y * vec.z - vec.y * this->z;
    j = -(this->x * vec.z - vec.x * this->z);
    k =   this->x * vec.y - vec.x * this->y;
    return Vector(i, j, k);
}

Vector Vector::operator= (const Vector& vec) {
    return Vector(vec);
}

int main() {
    Vector v1(1, 2, 3),
           v2(8, 3, 2.5),
           v3(10, 10),
           v4(7, 9, 2);
    
    std::cout << 
        v1 << " + " << v2 << " = " << v1 + v2 << std::endl << 
        v4 << " - " << v2 << " = " << v4 - v2 << std::endl <<
        v1 << " * " << v4 << " = " << v1.scalarProd(v4) << std::endl <<
        "-" << v3 << " = " << -v3 << std::endl <<
        "Copying v3 ..." 
    << std::endl;
    
    Vector v5 = v3;
    std::cout << v3 << std::endl << v5 << std::endl;
        
    return 0;
}