#include "linear_equation.h"
type* Thomas(type *a, type *b, type *c, int n,type *d){
    type alpha[n],beta[n];
    alpha[0]=a[0];
    for(int i=1;i<n;i++){
        beta[i]=b[i]/alpha[i-1];
        alpha[i]=a[i]-beta[i]*c[i-1];
    }
    type *x=new type[n];
    type *y=new type[n];
    y[0]=d[0];
    for(int i=1;i<n;i++){
        y[i]=d[i]-beta[i]*y[i-1];
    }
    x[n-1]=y[n-1]/alpha[n-1];
    for(int i=n-2;i>=0;i--){
        x[i]=(y[i]-c[i]*x[i+1])/alpha[i];
    }
    return x;
}
