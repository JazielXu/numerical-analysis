#include <iostream>
#include "MyGEM.h"
#include "MyChelosky.h"
using namespace std;


int main()
{
    //generate the Hilbert matrix
    int n; //n denote the dimension of the matrix

    while(cin>>n){
    if(n=='q')break;
    type Hilbert[MAX][MAX];
    type *baba = generator(n);
    convertor(Hilbert,baba,n);




    int indicator[MAX]={0,1,2,3,4,5,6,7,8,9,10,11}; //the original state of indicator
    type ans[MAX];
    int i,j;

    MyGEM g;//using GEM class
    MyChelosky ch; //using Chelosky
    type h[MAX][MAX];
    type b[MAX]={1,1,1,1,1,1,1,1,1,1,1}; //b is defined
//using Cholesky
    ch.add(Hilbert,b,n);//expand the matrix(append b to the last col)
    ch.Cholesky(Hilbert,n,h);//find h
    ch.add(h,b,n);//append h with b again

    g.Recursion_Lower(h,n,indicator,ans);
    ch.Hermintion(h,n);
    ch.add(h,ans,n);

    g.Recursion(h,n,indicator,ans);
    for(int i=0;i<n;i++)cout<<ans[i]<<" ";
    cout<<endl;

//using GEM
    ch.add(Hilbert,b,n);
    g.Elimination(Hilbert,n,indicator);
    g.Recursion(Hilbert,n,indicator,ans);
    for(int i=0;i<n;i++)cout<<ans[i]<<" ";
    cout<<endl;

    }
    return 0;
}
