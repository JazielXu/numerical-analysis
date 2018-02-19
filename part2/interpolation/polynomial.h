#ifndef POLYNOMIAL
#define POLYNOMIAL
#include <vector>
using namespace std;
using type=long double;
class poly{
private:
public:
        int degree;
    vector<type> a;
    poly(int d=0,vector<type> a={0}){
        this->degree=d;
        this->a=a;
    }

    poly operator +(const poly& b);
    poly operator -(const poly& b);
    poly operator *(const poly& b);
    poly operator ^(type b);
    poly operator +(type b);
    type calculate(type x);

};

poly Lagrange(int degree, type *a, type *b);
poly Chebyshev(int degree, type *x, type *y);
poly *spline(int n, type *x, type *y);
#endif // POLYNOMIAL

