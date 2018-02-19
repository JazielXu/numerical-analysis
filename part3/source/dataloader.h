#ifndef DATALOADER_H
#define DATALOADER_H

#include <complex>
#include <stdio.h>
#include <string.h>
#include <iomanip>

#include "matrix.h"
#include "polynomial.h"
using namespace std;
mytype rho(mytype *in,int a,int b){
    mytype ab=0,aa=0,bb=0,c_a_bar=0,c_b_bar;
    for(int i=0;i<1000;++i){
        srand(i);
        int temp=rand()%200;
        c_a_bar += in[temp*64+a];
        c_b_bar += in[temp*64+b];
    }
    c_a_bar /= 1000;c_b_bar /= 1000;
    for(int i=0;i<1000;++i){
        srand(i);
        int temp=rand()%200;
        aa += (in[temp*64+a]-c_a_bar)*(in[temp*64+a]-c_a_bar);
        ab += (in[temp*64+a]-c_a_bar)*(in[temp*64+b]-c_b_bar);
        bb += (in[temp*64+b]-c_b_bar)*(in[temp*64+b]-c_b_bar);
    }
    return ab/sqrt(aa*bb);
}

void load(){
    freopen("C.txt","r",stdin);
    int item;
    mytype real[64*200],complex,c_bar[33],c_delta[33],m[32];
    memset(c_bar,0,sizeof(c_bar));
    memset(c_delta,0,sizeof(c_delta));
    int times,sec;
    scanf("%d %d",&times,&sec); //times=200,sec=64
    for(int i=0;i<times;++i){
        for(int j=0;j<sec;++j){
            scanf("%d %lf %lf",&item,&real[j+sec*i],&complex);
        }
    }
    for(int i=0;i<times;++i){
        for(int j=1;j<32;++j){
            real[j+sec*i]=0.5*(real[j+sec*i]+real[sec*i+64-j]);
        }
    }
    for(int i=0;i<=sec/2;++i){
        for(int j=0;j<times;++j){
            c_bar[i]+=real[i+j*sec];
        }
        c_bar[i] /= times;
        for(int j=0;j<times;++j){
            c_delta[i]+=pow(real[i+j*sec]-c_bar[i],2);
        }
        c_delta[i] /= (times*(times-1));
        c_delta[i] = sqrt(c_delta[i]);
        //cout<<i<<" "<<c_bar[i]<<endl;
    }



    for(int i=0;i<32;++i){
        m[i]=log(c_bar[i]/c_bar[i+1]);
        //m[i]=acosh((c_bar[i+1]+c_bar[i-1])/2/c_bar[i]);
    }
    for(int i=0;i<33;++i)
        c_bar[i]=0;
    mytype m_count[32];
    for(int i=0;i<32;++i)
        m_count[i]=0;

    //doing jackknife: out is the kicked out block
    for(int out=0;out<times;++out){
        for(int i=0;i<=sec/2;++i){
            for(int j=0;j<times;++j){
                if(j!=out)c_bar[i]+=real[i+j*sec];
            }
            c_bar[i] /= (times-1);
            if(i!=0&&i!=sec/2){
                mytype mp=/*acosh((c_bar[i+1]+c_bar[i-1])/2/c_bar[i]);*/log(c_bar[i-1]/c_bar[i]);
                m_count[i-1]+=pow(mp-m[i-1],2);
                //if(i==15)cout<<out<<" "<<pow(log(c_bar[0]/c_bar[1])-m[0],2)<<" "<<m_count[i-1]<<" "<<m[i-1]<<endl;
            }
        }
    }


    for(int i=0;i<32;++i){
        m_count[i]=sqrt((times-1)*m_count[i]/times);
        cout<<setprecision(2)<<m_count[i]<<" & ";
        if(i==8||i==17||i==26)cout<<endl;
    }

    vector<mytype> a={0,0,0};
    poly chi2(2,a);
    mytype m_result;
    mytype min=999;
    mytype m_ans;
    int start,end;
    for(int i=0;i<32-4;++i){
        for(int j=i+3;j<32;++j){
            chi2.a=a;
            for(int k=i;k<=j;++k)
                chi2=chi2+term(m[k],m_count[k]);
            m_result=-chi2.a[1]/(2*chi2.a[2]);
            //cout<<chi2.calculate(m_result)/(j-i)<<endl;
            if(chi2.calculate(m_result)/(j-i) < min){
                start=i;end=j;
                min=chi2.calculate(m_result)/(j-i);
                m_ans=m_result;
            }
        }
    }
    cout<<"fit result m= "<<m_ans<<end<<endl;
    cout<<"the minimum chi-squre value = "<<min<<" And the coresponded interval is [" <<start<<", "<<end<<"]"<<endl;
    mytype error=0;
    for(int i=start;i<=end;++i){
        error += 1/(m_count[i]*m_count[i]);
    }
    cout<<"delta_m="<<sqrt(1/error)<<endl;
}


#endif // DATALOADER_H
