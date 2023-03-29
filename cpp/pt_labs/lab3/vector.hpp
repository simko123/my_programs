#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class Vector {
public:
    inline static unsigned count;
    
    Vector(unsigned dim, double *values);
    Vector(const Vector &vec);
   ~Vector();

    friend std::ostream& operator<< (std::ostream &out, const Vector &vec); 
    Vector operator+ (const Vector &vec);
    Vector operator- (const Vector &vec);
    Vector operator- ();
    Vector& operator= (const Vector &vec);
    double operator* (const Vector &vec);

    unsigned getDim() const { return this->dim; }
    double at(unsigned i) const { return this->val[i]; }

private:
    unsigned dim, number;
    double *val;
};

#endif