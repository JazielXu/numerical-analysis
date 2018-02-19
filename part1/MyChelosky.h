#ifndef MYCHELOSKY_H_INCLUDED
#define MYCHELOSKY_H_INCLUDED
#include <iostream>
#include <iomanip>
#include <math.h>
#define MAX 99

using type = long double;
//used to generate the Hilbert matrix
type *generator(int n){
    type *rst = new type[n * n];
    for(int _x=0;_x<n;_x++){
        for(int _y=0; _y < n; ++_y){
            rst[_x * n + _y] = 1 / ((type)1 + _x + _y );
        }
    }
    return rst;
}
void convertor(type a[MAX][MAX],type *baba,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a[i][j]=*(baba++);
        }
    }
}



class MyChelosky{
public:
    void Cholesky(type a[MAX][MAX],int n,type h[MAX][MAX]){
        h[0][0]=sqrtl(a[0][0]);
        for(int t=1;t<n;t++)h[t][0]=a[t][0]/h[0][0];
        for(int j=1;j<n;j++){
            h[j][j]=a[j][j];

            for(int k=0;k<j;k++){
                h[j][j]-=h[j][k]*h[j][k];
            }

            h[j][j]=sqrtl(h[j][j]);
            for(int i=j+1;i<n;i++){
                h[i][j]=a[i][j];
                for(int k=0;k<j;k++){
                    h[i][j]-=h[i][k]*h[j][k];
                }
            h[i][j]/=h[j][j];
            }
        }
    }
        void add(type h[MAX][MAX],type b[MAX],int n){
        for(int i=0;i<n;i++)h[i][n]=b[i];
    }

//Solve the Hermintion Conjugate of a matrix h
    void Hermintion(type h[MAX][MAX],int n){
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                h[j][i]=h[i][j];
                h[i][j]=0;
            }
        }
    }
};


#endif // MYCHELOSKY_H_INCLUDED
