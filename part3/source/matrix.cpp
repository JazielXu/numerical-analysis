#include "matrix.h"
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
void matrix::print()
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(ele[i*col+j]>0.00001||ele[i*col+j]<-0.00001)
                cout<<setprecision(4)<<ele[i*col+j]<<"     ";
            else cout<<"0     ";
        }
        cout<<endl;
    }
}

matrix matrix::take_out_col(int c,int u)//only take out ele starting from row index u,
{
    mytype a[row-u];
    int cnt=0;
    for(int i=u;i<row;i++){
        a[cnt++]=ele[i*col+c];
    }
    return matrix(row-u,1,a);
}

bool matrix::is_vec()
{
    return col==1?true:false;
}

mytype matrix::sqare()
{
    if(!this->is_vec()){
        cout<<"squre() function only calculate norm square of a row-vector"<<endl;
        return -1;
    }
    mytype answer = 0;
    for(int i=0;i<row;i++){
        answer += ele[i]*ele[i];
    }
    return answer;
}

matrix* matrix::householer()
{
    if(!this->is_vec()){
        cout<<"this function only calculate reflection of a column vector"<<endl;
        return this;
    }
    mytype y=pow(this->sqare(),0.5);
    mytype denominator=pow(2*y*(y-ele[0]),0.5);
    mytype vec[row];
    for(int i=0;i<row;i++){
        vec[i]=ele[i]/denominator;
    }
    vec[0] -= y/denominator;
    matrix *ret=new matrix(row,1,vec);
    return ret;
}

matrix *matrix::QS_h(string s)
{
    if(s=="householder"){
        //using reflectors(householer method)to do QS decompose
        matrix *u=new matrix[row-1];
        for(int i=0;i<row-1;i++){
            u[i]=this->take_out_col(i,i);
            u[i]=*(u[i].householer());
            //u[i].print();
            //have to update the next column using u
            this->update(u[i]);
            this->getQ(u);
        }
    }
    else if(s=="givens"){
        //using rotators(givens method)to do QS decompose
        for(int i=0;i<col-1;++i){
            for(int j=i+1;j<row;++j){
                matrix G=getG(row,i,j,ele[i*row+i],ele[j*row+i]);
                *this=(G^(*this));
                //this->print();
            }
        }
    }
}

bool matrix::update(matrix u)
{
    if(u.row>this->row){cout<<"update encountering invalid input"<<endl;return false;}
    int operate;
    for(int i=u.row;i>0;--i){
        operate=this->row-i;
        take_out_col(operate,row-u.row).print();
        mytype cu=take_out_col(operate,row-u.row)*u;
        int cnt=0;
        for(int j=row-u.row;j<row;++j){
            this->ele[operate+col*j]-=2*cu*u.ele[cnt++];
        }
    }

}

matrix matrix::getQ(matrix *u)
{
    mytype k=0;
    matrix Q(row,col,"identity");
    Q=Q-((u[0]^(u[0].tras_row_to_col()))*2);
}

matrix matrix::operator +(const matrix &b)
{
    if(row!=b.row || col != b.col){cout<<"can't add!"<<endl;return *this;}
    mytype ret[row*col];
    for(int i=0;i<row*col;++i)
        ret[i]=ele[i]+b.ele[i];
    return matrix(row,col,ret);
}

matrix matrix::operator -(const matrix &b)
{
    if(row!=b.row || col != b.col){cout<<"can't minus!"<<endl;return *this;}
    mytype ret[row*col];
    for(int i=0;i<row*col;++i)
        ret[i]=ele[i]-b.ele[i];
    return matrix(row,col,ret);
}

mytype matrix::operator *(const matrix &b)
{
    if(b.col!=1 || col!=1 || b.row != row){cout<<"can't do dot product"<<endl;return -1;}
    mytype answer=0;
    for(int i=0;i<row;++i){
        answer += ele[i]*b.ele[i];
    }
    return answer;
}

matrix matrix::operator ^(const matrix &b)
{
    if(col!=b.row){cout<<"matrix mul formating error!"<<endl;return *this;}
    mytype ret_ele[row*b.col];
    for(int i=0;i<row;++i){
        for(int j=0;j<b.col;++j){
            ret_ele[i*b.col+j]=0;
            for(int k=0;k<col;++k){
                ret_ele[i*b.col+j]+=ele[i*col+k]*b.ele[j+k*b.col];
                //cout<<"("<<i<<","<<j<<")+="<<ele[i*col+k]<<"*"<<b.ele[j+k*b.col]<<endl;
            }
        }
    }
    matrix answer(row,b.col,ret_ele);
    return answer;
}

matrix matrix::operator *(mytype k)
{
    for(int i=0;i<row*col;++i)
        ele[i] *=k;
    return matrix(row,col,ele);
}

matrix matrix::tras_row_to_col()
{
    if(col!=1){cout<<"can't convert col!=1"<<endl;return *this;}
    return matrix(col,row,ele);
}

mytype matrix::getEigenvalue()
{
    matrix q=matrix(row,1,(mytype)0);
    q.ele[row-1]=1;
    matrix z(row,1);
    mytype nu;
    for(int k=0;k<40;++k){
        z=(*this)^q;
        q=z*(1/(z.getNorm()));
        nu=q*(*this^q);
    }
    cout<<"q="<<endl;
    q.print();
    cout<<endl;
    return nu;
}

mytype matrix::getNorm()
{
    if(col!=1){cout<<"col="<<col<<", can't calculate norm"<<endl;return 0;}
    mytype ans=0;
    for(int i=0;i<row;++i){
        ans+=ele[i]*ele[i];
    }
    return sqrt(ans);
}

matrix matrix::getG(int n, int i, int j, mytype a, mytype b)
{
    mytype ele[n*n];
    for(int z=0;z<n;++z){
        for(int k=0;k<n;++k){
            if(z==k)ele[z*n+k]=1;
            else ele[z*n+k]=0;
        }
    }
    mytype a_=sqrt(a*a+b*b);
    mytype cos=(a*a_)/(a*a+b*b);
    mytype sin=sqrt(1-cos*cos);
    if(b<0)sin=-sin;
    ele[i*n+i]=cos;ele[i*n+j]=sin;ele[j*n+i]=-sin;ele[j*n+j]=cos;
    matrix G=matrix(n,n,ele);
    //G.print();
    return G;

}
