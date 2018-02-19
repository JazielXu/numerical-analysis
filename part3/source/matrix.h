#ifndef MATRIX_H
#define MATRIX_H
#include <stdlib.h>
#include <string>
#include <math.h>
//#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286209
const long double PI=atan(1)*4;
using namespace std;
using mytype = double;
class matrix{
public:
    int row;
    int col;
    mytype *ele;
    matrix(){
        row = 1;
        col = 1;
        ele = 0;
    }

    matrix(int n,int m){
        row = n;
        col = m;
        ele = new mytype[m*n];
        for(int i=0;i<m*n;i++){
            srand(i);
            int temp=rand()%2;
            if(temp==0)temp=-1;
            ele[i] = temp*rand()%100/(double)101;
        }
    }
    matrix(int n,int m,mytype k){
        row =n;
        col = m;
        ele = new mytype[m*n];
        for(int i=0;i<m*n;i++){
            ele[i] = k;
        }
    }
    matrix(int n,int m, string s){
        if(n!=m){return;}
        if(s == "identity"){
            row =n;
            col =n;
            ele = new mytype[n*n];
            for(int i=0;i<n;i++){
                for(int j=0;j<n;++j){
                    if(i==j)ele[i*n+j]=1.0;
                    else ele[i*n+j]=0.0;
                }
            }
        }
        else if(s=="string"){
            row =n;
            col =n;
            ele = new mytype[n*n];
            for(int i=0;i<n;i++){
                for(int j=0;j<n;++j){
                    if(i==j)ele[i*n+j]=2;
                    else if(abs(i-j)==1) ele[i*n+j]=-1;
                    else ele[i*n+j]=0;
                }
            }
            ele[n-1]=ele[n*(n-1)]=-1;
        }
    }
    matrix(int N){
        row=col=N*N;
        ele = new mytype[N*N*N*N];
        for(int i=0;i<N*N;++i){
            for(int j=0;j<N*N;++j){
                if(i==j)ele[i*N*N+j]=4.0;
                else if(i-j==1){
                    if(i%N!=0)
                        ele[i*N*N+j]=-1.0;
                }
                else if(j-i==1){
                    if(i%N!=(N-1))
                        ele[i*N*N+j]=-1.0;
                }
                else if(i-j==N||j-i==N){
                    ele[i*N*N+j]=-1.0;
                }
                else ele[i*N*N+j]=0;
            }
        }
    }
    matrix(int N ,string s){
        if(s=="GetE"){
            row=col=N*N;
            ele = new mytype[N*N*N*N];
            for(int i=0;i<N*N;++i){
                for(int j=0;j<N*N;++j){
                    if(i-j==1){
                        if(i%N!=0)
                            ele[i*N*N+j]=1.0;
                    }

                    else if(i-j==N){
                        ele[i*N*N+j]=1.0;
                    }
                    else ele[i*N*N+j]=0;
                }
            }
        }
        if(s=="GetD-1"){
            row=col=N*N;
            ele = new mytype[N*N*N*N];
            for(int i=0;i<N*N;++i){
                for(int j=0;j<N*N;++j){
                    if(i==j)ele[i*N*N+j]=1.0/4;
                    else ele[i*N*N+j]=0;
                }
            }
        }
        else if(s=="GetB"){
            row=N*N;
            col=1;
            mytype h=1.0/(N+1);
            ele = new mytype[N*N];
            for(int i=0;i<N;++i){
                for(int j=0;j<N;++j){
                    ele[i*N+j]=h*h*2*PI*PI*sin(PI*(j+1)*h)*sin(PI*(i+1)*h);
                }
            }
        }
    }

    matrix(int n, int m, mytype *e){
        row = n;
        col = m;
        ele = new mytype[m*n];
        for(int i=0;i<m*n;i++){
            ele[i] = e[i];
        }
    }

    void print();
    matrix take_out_col(int c, int u);
    bool is_vec();
    mytype sqare();
    matrix *householer(); //take a vector and return the "u" vector
    matrix *QS_h(string s);
    bool update(matrix u);
    matrix getQ(matrix *u);
    matrix operator +(const matrix &b);
    matrix operator -(const matrix &b);
    mytype operator *(const matrix &b);
    matrix operator ^(const matrix &b);
    matrix operator *(mytype k);
    matrix tras_row_to_col();
    mytype getEigenvalue();
    mytype getNorm();
    matrix getG(int n, int i, int j, mytype a, mytype b);
};

#endif // MATRIX_H

