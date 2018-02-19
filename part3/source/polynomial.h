#ifndef POLYNOMIAL
#define POLYNOMIAL
#include <vector>
#include "matrix.h"
using namespace std;
class poly{
private:
public:
        int degree;
    vector<mytype> a;
    poly(int d=0,vector<mytype> a={0}){
        this->degree=d;
        this->a=a;
    }

    poly operator +(const poly& b);
    poly operator -(const poly& b);
    poly operator *(const poly& b);
    poly operator ^(mytype b);
    poly operator +(mytype b);
    mytype calculate(mytype x);

};
poly term(mytype m, mytype dm);

#endif // POLYNOMIAL

