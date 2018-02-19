#ifndef ODE_H
#define ODE_H
#define type long double
struct vec{
    type x;
    type y;
    vec(type a,type b){
        x=a;
        y=b;
    }
    void update(type h,type par){
        type ky1=h*(x-1)*y;
        type kx1=h*par*(1-y)*x;
        type ky2=h*(x+0.5*kx1-1)*(y+0.5*ky1);
        type kx2=h*par*(1-y-0.5*ky1)*(x+0.5*kx1);
        type ky3=h*(x+0.5*kx2-1)*(y+0.5*ky2);
        type kx3=h*par*(1-y-0.5*ky2)*(x+0.5*kx2);
        type ky4=h*(x+kx3-1)*(y+ky3);
        type kx4=h*par*(1-y-ky3)*(x+kx3);
        x = x+ kx1/6+kx2/3+kx3/3+kx4/6;
        y = y+ ky1/6+ky2/3+ky3/3+ky4/6;
    }
};

#endif // ODE_H
