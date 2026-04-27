#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include"config.h"
#include"parameter.h"
/*---�g�p����֐�---*/

//Rosenbrock�֐�
double Rosenbrock(vector<double> x){
        double sum=0.0;
        for(int i=1;i<x.size();i++){
            sum+=100*(x[0]-pow(x[i],2))*(x[0]-pow(x[i],2))+(x[i]-1)*(x[i]-1);
        }
        return sum;
    }

//Rastrigin�֐�
double Rastrigin(vector<double> x){
        double sum=0.0;
        int count=0;
        for(int i=0;i<x.size();i++){
            sum=sum+pow(x[i],2)-10*cos(2*pi*x[i]);
            count++;
        }
        return 10*count+sum;
    }

//Sphere�֐�
double Sphere(vector<double> x){
    double sum=0.0;
    for(int i=0;i<x.size();i++){
        sum+=x[i]*x[i];
    }
    return sum;
}

//�A�b�N���[�֐�
double Ackley(vector<double> x){
    double sum1=0.0;
    double sum2=0.0;
    for(int i=0;i<x.size();i++){
        sum1+=pow(x[i],2);
        sum2+=cos(2*pi*x[i]);
    }
    sum1=sqrt(sum1/x.size());
    sum2=sum2/x.size();

    return 20-(20*exp(-0.2*sum1))+exp(1)-exp(sum2);
}

//Schwefel�֐�
double Schwefel(vector<double> x){
    double sum=0.0;
    for(int i=0;i<x.size();i++){
        sum+=x[i]*sin(sqrt(fabs(x[i])));
    }
    return 418.9828873*x.size()+sum;
}

//Rosenborck�֐�(chain�^)
double Rosenbrock_chain(vector<double> x){
    double sum=0.0;
    for(int i=0;i<x.size()-1;i++){
        sum+=100*(x[i+1]-pow(x[i],2))*(x[i+1]-pow(x[i],2))+(x[i]-1)*(x[i]-1);
    }
    return sum;
}

//Ellipsoid�֐�
double Ellipsoid(vector<double> x){
    double sum=0.0;
    for(int i=0;i<x.size();i++){
        sum+=((pow(1000,i/param.dimension-1))*x[i])*((pow(1000,i/param.dimension-1))*x[i]);
    }
    return sum;
}

//Bohaxhevsky�֐�
double Bohaxhevsky(vector<double> x){
    double sum=0.0;
    for(int i=0;i<x.size()-1;i++){
        sum+=x[i]*x[i]+2*x[i+1]*x[i+1]-0.3*cos(3*pi*x[i])-0.4*cos(4*pi*x[i+1])+0.7;
    }
    return sum;
}

//Griewank�֐�
double Griewank(vector<double> x){
    double sum1=0.0;
    double sum2=1.0;
    for(int i=0;i<x.size();i++){
        sum1+=pow(x[i],2);
        sum2=sum2*cos(x[i]/(i+1));
    }
    return 1+(sum1/4000)-sum2;
}

//new_Rastrigin
double new_Rastrigin(vector<double> x){

    double sum=0.0;
    int count=0;
    for(int i=0;i<x.size();i++){
        sum=sum+(pow(x[i]-param.rast_shift[i],2))-10*cos(2*pi*(x[i]-param.rast_shift[i]));
        count++;
    }
    return 10*count+sum;
}

double f_value(int i,vector<double> x){
    if(i==0) return Rosenbrock(x);
    if(i==1) return Rastrigin(x);
    if(i==2) return Sphere(x);
    if(i==3) return Ackley(x);
    if(i==4) return Schwefel(x);
    if(i==5) return Rosenbrock_chain(x);
    if(i==6) return Ellipsoid(x);
    if(i==7) return Bohaxhevsky(x);
    if(i==8) return Griewank(x);
    if(i==9) return new_Rastrigin(x); 
    return -99.0;
}


#endif