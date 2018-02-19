#ifndef MYGEM_H_INCLUDED
#define MYGEM_H_INCLUDED
#include <math.h>
#include <iostream>
#include <iomanip>
#define MAX 99
using namespace std;
using type=long double;
class MyGEM{
public:
    //could be used to print a matrix nicely, for the use of debugging
    void print(type a[MAX][MAX],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++)cout<<left<<setw(14)<<a[i][j]<<"   ";
        cout<<endl;
    }

    }
    //Find the element with the largest absolute value in a matrix(or sub-matrix)
    //return the position of the value(row,col)
    int FindMax(type a[MAX][MAX],int start, int n, int &row, int &col){
        int Pmax=0;
        for(int i=start;i<n;i++){
            for(int j=start;j<n;j++){
                if(fabsf(a[i][j])>fabsf(Pmax)){
                Pmax=a[i][j];
                row=i;
                col=j;
                }
            }
        }
    return Pmax;
    }

    void SwitchRow(type a[MAX][MAX],int n,int start,int row){
        type temp;
        for(int i=start;i<=n;i++){
            temp=a[start][i];
            a[start][i]=a[row][i];
            a[row][i]=temp;
        }
        return;
    }

    void SwitchCol(type a[MAX][MAX],int n,int start,int col){
        type temp;
        for(int i=0;i<n;i++){
            temp=a[i][start];
            a[i][start]=a[i][col];
            a[i][col]=temp;
        }
        return;
    }

    //Key function in the GEM algorithm, transform A in to a upper-triangle matrix
    void Elimination(type a[MAX][MAX],int n,int indicator[MAX]){
        int row,col;
        for(int i=0;i<n-1;i++){
            int p=FindMax(a,i,n,row,col); //find the entry with largest absolute value in the sub-matrix
            if(row!=i)SwitchRow(a,n,i,row); //change it to the up right position
            if(col!=i){
                SwitchCol(a,n,i,col);
                int temp=indicator[i]; //keep a record of col swapping
                indicator[i]=indicator[col];
                indicator[col]=temp;
            }
            for(int j=i+1;j<n;j++){
                type c=-a[j][i]/a[i][i];
                for(int k=i;k<=n;k++){
                    a[j][k]+=c*a[i][k];
                }
            }
        }
    }
    //deduce every x value from the reformed A matrix
    void Recursion(type a[MAX][MAX],int n,int indicator[MAX],type ans[MAX]){
        type x[MAX];
        for(int i=n-1;i>=0;i--){
            x[i]=a[i][n];
            for(int j=n-1;j>i;j--){
                x[i]-=a[i][j]*x[j];
            }
            x[i]/=a[i][i];
        }
        for(int i=0;i<n;i++){
            ans[indicator[i]]=x[i];
        }
    }
    //a similar function used to deal with lower-triangle matrix
    void Recursion_Lower(type a[MAX][MAX],int n,int indicator[MAX],type ans[MAX]){
        type x[MAX];
        for(int i=0;i<n;i++){
            x[i]=a[i][n];
            for(int j=0;j<i;j++){
                x[i]-=a[i][j]*x[j];
            }
            x[i]/=a[i][i];
        }
        for(int i=0;i<n;i++){
            ans[indicator[i]]=x[i];
        }
    }

};

#endif // MYGEM_H_INCLUDED
