#include <iostream>
#include "polynomial.h"
#include "linear_equation.h"
#include "integrate.h"
#include <vector>
#include <math.h>
#define PI 3.14159265358979323846264338
#include <fstream>
#include <iomanip>
using namespace std;

type Runge(type x){
    return 1.0/(25*pow(x,2)+1);
}
void Lagranging(){


    type x[21];
    type y[21];
    for(int i=0;i<21;i++){
        x[i]=-1+0.1*i;
        y[i]=Runge(x[i]);
    }

    poly c=Lagrange(20,x,y);
    ofstream file;
    file.open("lagrange.txt");
    cout<<"opening"<<endl;
    for(int i=0;i<41;i++){
        file<<-1+0.05*i<<" "<<c.calculate(-1+0.05*i)<<endl;
        //cout<<Runge(-1+0.05*i)<<" "<<c.calculate(-1+0.05*i)<<endl;
    }
    file.close();
}

void Chebysheving(){
    type x[21];
    type y[21];
    for(int i=0;i<20;i++){
        x[i]=cos(PI*(i+0.5)/20);
        y[i]=Runge(x[i]);
    }
    poly a=Chebyshev(20,x,y);
    ofstream file;
    file.open("chebyshev.txt");
    for(int i=0;i<21;i++){
    file<<cos(PI*(i+0.5)/20)<<" "<<a.calculate(cos(PI*(i+0.5)/20))<<endl;
    file<<cos(PI*(i+1.5)/20)/2+cos(PI*(i+0.5)/20)/2<<" "<<a.calculate(cos(PI*(i+1.5)/20)/2+cos(PI*(i+0.5)/20)/2)<<endl;

    }
    file.close();
}
void splining(){
    type x[21];
    type y[21];
    for(int i=0;i<21;i++){
        x[i]=-1+0.1*i;
        y[i]=Runge(x[i]);
    }
    poly *s=spline(20,x,y);
    ofstream file;
    file.open("spline.txt");
    for(int i=0;i<41;i++){
        file<<-1+0.05*i<<" "<<s[i/2].calculate(-1+i*0.05)<<endl;
    }
}
void Cardioid(){
    type t[9],x[9],y[9];
    ofstream file;
    file.open("card.txt");
    for(int i=0;i<9;i++){
        t[i]=PI*i/4;
        x[i]=(1-cos(t[i]))*cos(t[i]);
        y[i]=(1-cos(t[i]))*sin(t[i]);
    }
        poly *sx=spline(8,t,x);
        cout<<"********************"<<endl;
        poly *sy=spline(8,t,y);

        for(int i=0;i<8;i++){
            for(int j=0;j<101;j++){
                file<<sx[i].calculate(t[i]+j*(t[i+1]-t[i])/100)<<" "<<sy[i].calculate(t[i]+j*(t[i+1]-t[i])/100)<<endl;
            }
        }
    file.close();
}
void Card(){
    ofstream file;
    file.open("ca.txt");
    type t,x,y;
    for(int i=0;i<801;i++){
        t=PI*i/400;
        x=(1-cos(t))*cos(t);
        y=(1-cos(t))*sin(t);
        file<<x<<" "<<y<<endl;
    }
    file.close();
}

bool check(type mid, type q2, int n)
{
    type f = zeta(q2,n);
    if(f > 0.0) return 1;
    return 0;
}


int point[32]={1,6,12,8,6,24,24,0,12,30,24,24,8,24,48,0,6,48,36,24,24,48,24,0,24,30,72,32,0,72,48};


type first_term(type q2,int n){
    type answer=0;
    for(int i=0;i<=n;i++){
         answer+=point[i]*exp(q2-i)/(i-q2);

/*
        for(int j=-n;j<=n;j++){
            for(int k=-n;k<=n;k++){
                int r2=i*i+j*j+k*k;
                if(r2<=n){
                    if(r2==0)cout<<r2<<" ";
                    answer+=exp(q2-r2)/(r2-q2);
                }
            }
        }
*/
    }
    return answer/sqrt(4*PI);
}

type fac(type x){
    if(x==1)return 1;
    else return x*fac(x-1);
}

type third_term(type q2){
    type answer=0;
    for(int i=0;i<50;i++){
        answer+=2*pow(q2,i+1)/((2*i+1)*fac(i+1));
    }
    return answer*PI/2;
}

type zeta(type q2, int n){

    type a=first_term(q2,n);
    type b=third_term(q2);
    type d=simpson(0,1,999999,q2,n);
    type answer=a+b-PI+d;
    return answer;
}

int main(int argc, char *argv[])
{
    /*
    for(int i=1;i<30;i++){
    cout<<setprecision(7)<<i<<" "<<
    zeta(0.4,i)<<endl;

    }*/


    //Lagranging();
    //Chebysheving();
    //Cardioid();
    vector<double>a={1,2,3};
    poly as(2,a);
    poly b=as*as;
    for(auto x:b.a)cout<<x<<" ";

return 0;


}

