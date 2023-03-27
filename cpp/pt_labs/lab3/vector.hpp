#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class Vector {
public:
    inline static unsigned count;
    
    Vector(unsigned dim, double *values);
    Vector(const Vector &vec);
    Vector(){};
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

#endif