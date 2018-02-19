#include "integrate.h"
#include <math.h>
#include <iostream>
#define PI 3.14159265358979323846264338
using namespace std;
type four(type x, type q2, int r2){
    if(x==0)return 0;
    type answer=sqrt(PI/4)*pow(x,-1.5)*exp(x*q2-PI*PI*r2/x);
    return answer;
}

int points[32]={0,6,12,8,6,24,24,0,12,30,24,24,8,24,48,0,6,48,36,24,24,48,24,0,24,30,72,32,0,72,48};


type simpson(type begin, type end, int N,type q2,int n)
{
    type result=0;
    for(int i=0;i<=2*N;i++){
        type y=0;
        for(int j=0;j<=n;j++){
            y+=points[j]*four(begin+i*(end-begin)/(2*N),q2,j);
        }
        /*
        for(int _=-n;_<=n;_++){
            for(int j=-n;j<=n;j++){
                for(int k=-n;k<=n;k++){
                    int r2=_*_+j*j+k*k;
                    if((r2<=n)&&(r2!=0)){
                        y+=four(begin+i*(end-begin)/(2*N),q2,r2);
                    }
                }
            }
        }*/
        if(i%2==0){
            result+=y;
        }
        else{
            result+=(2*y);
        }
    }
    result=result*(end-begin)/(3*N);
    return result;
}
