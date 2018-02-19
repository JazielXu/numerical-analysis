#include <iostream>
#include "matrix.h"
#include <complex>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "dataloader.h"
#include "ode.h"
using namespace std;
int main(int argc, char *argv[])
{
    /*
//this is for question Ex4-2--------------------------------------------------------
int N=50;

    matrix A(N);
    matrix B(N,"GetB");
    matrix I(N*N,N*N,"identity");
    matrix D_inv(N,"GetD-1");
    matrix E(N,"GetE");
    matrix L=E*(mytype)0.25;
    matrix Bw=I-L*1.1;


//    matrix temp=I-(D_inv^A);
    mytype rhoJ=cos(PI/(N+1));
    //mytype omega=2/(1+sqrt(1-rhoJ*rhoJ));
    mytype omega=1;
cout<<"omega= "<<omega<<endl;

    matrix u(N*N,1,(mytype)0);
    mytype h=1.0/(N+1);
    mytype e[N*N];
    mytype norm=1,temp;
    int z;
    for(z=0;;++z){
        if(norm<=0.0001*h*h)
            break;
        for(int i=0;i<N*N;++i){
            if(z!=0)u.ele[i]=e[i];
            e[i]=0;
        }
        norm=0;
        //u=((I-(D_inv^A))^u)+(D_inv^B);
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                e[i*N+j]=(1-omega)*u.ele[i*N+j];
                if(j!=0)
                    e[i*N+j]+=0.25*e[i*N+j-1]*omega;
                if(j!=N-1)
                    e[i*N+j]+=0.25*u.ele[i*N+j+1]*omega;
                if(i!=0)
                    e[i*N+j]+=0.25*e[i*N+j-N]*omega;
                if(i!=N-1)
                    e[i*N+j]+=0.25*u.ele[i*N+j+N]*omega;
                e[i*N+j]+=0.5*PI*PI*h*h*sin(PI*(i+1)*h)*sin(PI*(j+1)*h);
                temp=4*e[i*N+j]-4*u.ele[i*N+j];
                norm=max(norm,temp);
            }
        }

        //matrix temp=(I-(D_inv^A));
        //u=temp^u;
        //u=u+(D_inv^B);
    }
    cout<<"iterate "<<z<<" times! And we reach norm="<<norm/h/h<<endl;
    cout<<"Here is the comparesion between the exact result versus the calculated ones"<<endl;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cout<<sin(PI*(i+1)*h)*sin(PI*(j+1)*h)<<" "<<u.ele[i*N+j]<<endl;
        }
        cout<<endl;
    }
*/
    /*
    //this is for Ex3-question 1:--------------------------------------------------
    matrix ran(6,6);
    ran.QS_h("givens");
    //ran.QS_h("householder");
    ran.print();
    */
/*
    //this is for Ex3-question 2:-------------------------------------------------

    matrix a(10,10,
             "string");
    cout<<"A="<<endl;
    a.print();

    cout<<"lambda = "<<a.getEigenvalue();
    cout<<endl;


    */

/*
     //this is for Ex3-question 3--------------------------------------------------
     load();
*/
    return 0;
}

