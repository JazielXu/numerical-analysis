#include "polynomial.h"
#include "matrix.h"

#include <math.h>
#include <iostream>
#include <iomanip>
#define PI 3.14159265358979323846264338
using namespace std;

poly poly::operator +(const poly &b)
{
    int d=(degree>b.degree?degree:b.degree);
    vector<mytype>answer(degree>b.degree?a:b.a);
        auto it=answer.begin();
        for(auto x:(degree>b.degree?b.a:a)){
            *it+=x;
            it++;
    }
    poly p(d,answer);
    return p;
}

poly poly::operator -(const poly &b)
{
    int d=(degree>b.degree?degree:b.degree);
    vector<mytype>answer(degree>b.degree?a:b.a);
        auto it=answer.begin();
        for(auto x:(degree>b.degree?b.a:a)){
            *it-=x;
            it++;
    }
    poly p(d,answer);
    return p;
}


poly poly::operator *(const poly &b)
{
    int d=degree+b.degree;
    vector<mytype>answer={0};
    answer.resize(d+1,0);
    for(int i=0;i<=degree;i++){
        for(int j=0;j<=b.degree;j++){
            answer[i+j]+=a[i]*b.a[j];
        }
    }
    poly p(d,answer);
    return p;
}

poly poly::operator ^(mytype b)
{
    vector<mytype>answer(a);
    auto it=answer.begin();
    while(it!=answer.end()){
        (*it)*=b;
        ++it;
    }
    poly p(degree,answer);
    return p;
}

poly poly::operator +(mytype b)
{
    vector<mytype>answer(a);
    auto it=answer.begin();
    *(it)+=b;
    poly p(degree,answer);
    return p;
}

mytype poly::calculate(mytype x)
{
    mytype answer=0;
    for(int i=0;i<=degree;i++){
        answer+=pow(x,i)*a[i];
    }
    return answer;
}



poly term(mytype m, mytype dm)
{
    vector<mytype> v={pow(m/dm,2),-2*m/pow(dm,2),1/pow(dm,2)};
    return poly(2,v);
}
