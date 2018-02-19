#include "polynomial.h"
#include "linear_equation.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#define PI 3.14159265358979323846264338
using namespace std;

poly poly::operator +(const poly &b)
{
    int d=(degree>b.degree?degree:b.degree);
    vector<type>answer(degree>b.degree?a:b.a);
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
    vector<type>answer(degree>b.degree?a:b.a);
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
    vector<type>answer={0};
    answer.resize(d+1,0);
    for(int i=0;i<=degree;i++){
        for(int j=0;j<=b.degree;j++){
            answer[i+j]+=a[i]*b.a[j];
        }
    }
    poly p(d,answer);
    return p;
}

poly poly::operator ^(type b)
{
    vector<type>answer(a);
    auto it=answer.begin();
    while(it!=answer.end()){
        (*it)*=b;
        ++it;
    }
    poly p(degree,answer);
    return p;
}

poly poly::operator +(type b)
{
    vector<type>answer(a);
    auto it=answer.begin();
    *(it)+=b;
    poly p(degree,answer);
    return p;
}

type poly::calculate(type x)
{
    type answer=0;
    for(int i=0;i<=degree;i++){
        answer+=pow(x,i)*a[i];
    }
    return answer;
}

poly Lagrange(int degree, type *x, type *y)
{
    vector<type>answer={0};
    poly ans(0,answer);
    for(int i=0;i<=degree;i++){
        vector<type>one={y[i]};
        poly temp(0,one);
        for(int _=0;_<=degree;_++){
            if(_!=i){
                int now_d=1;
                vector<type>now_a={-x[_]/(x[i]-x[_]),1.0/(x[i]-x[_])};
                poly now(now_d,now_a);
                temp=temp*now;
            }
        }
        ans=ans+temp;
    }

    return ans;
}



poly Chebyshev(int degree, type *x, type *y)
{
    poly Che[degree];
    type c[degree];
    vector<type>zero={1};
    vector<type>one={0,1};
    vector<type>twox={0,2};
    poly two_x(1,twox);
    Che[0].degree=0;
    Che[0].a=zero;
    Che[1].degree=1;
    Che[1].a=one;
    for(int i=2;i<degree;i++){
        Che[i]=two_x*Che[i-1]-Che[i-2];
    }

    //now we have T_ks,time to calculate c_ks from x and y.
    for(int i=0;i<degree;i++){
        //calculating C[i]
        type answer=0;
        for(int j=0;j<degree;j++){
            answer+=y[j]*cos(PI*i*(j+0.5)/degree);
        }
        c[i]=2*answer/degree;
    }
    //now we can get the resulting poly
    vector<type>c0={-0.5*c[0]};
    poly result(0,c0);
    for(int i=0;i<degree;i++){
        result=result+(Che[i]^c[i]);
    }
    return result;
}



poly *spline(int n, type *x, type *y)
{
    type h[n+1];
    for(int i=1;i<=n;i++){
        h[i]=x[i]-x[i-1];
    }
    type a[n+1],b[n+1],c[n+1],d[n+1];
    a[0]=1;a[n]=1;
    b[n]=0;c[0]=0;
    d[0]=0;d[n]=0;
    for(int i=1;i<n;i++){
        b[i]=h[i]/6;
        c[i]=h[i+1]/6;
        a[i]=(h[i]+h[i+1])/3;
        d[i]=(y[i+1]-y[i])/h[i+1]-(y[i]-y[i-1])/h[i];
    }
    type *M=Thomas(a,b,c,n+1,d);
    type A[n],B[n];
    for(int i=0;i<n;i++){
        B[i]=y[i]-M[i]*h[i+1]*h[i+1]/6;
        A[i]=(y[i+1]-y[i])/h[i+1]-h[i+1]*(M[i+1]-M[i])/6;
    }
    poly *S=new poly[n];
    for(int i=0;i<n;i++){
        vector<type> one_a={x[i+1],-1};
        poly one(1,one_a);
        vector<type> two_a={-x[i],1};
        poly two(1,two_a);
        S[i]=(one*one*one^(M[i]/(6*h[i+1])))+(two*two*two^(M[i+1]/(6*h[i+1])))+(two^A[i])+B[i];
        for(auto x:S[i].a)cout<<setiosflags(ios::fixed)<<setprecision(4)<<x<<" ";
        cout<<endl;
    }
    return S;
}
