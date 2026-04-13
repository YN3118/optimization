#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include"config.h"
#include<vector>
/*---égópÇ∑ÇÈä÷êî---*/

vector<double> ZDT4(vector<double> x){
    vector<double> result(2);
    result[0]=x[0];
    double g=0.0;
    double h=0.0;

    for(int i=1;i<x.size();i++){
        g+=pow(x[i],2)-10*cos(4*pi*x[i]);
    }
    g=g+1.0+10*(param.dimension-1);
    h=1.0-sqrt(x[0]/g);
    result[1]=g*h;
    return result;
}

vector<double> ZDT1(vector<double> x){
    vector<double> result(2);
    result[0]=x[0];
    
    double g=0.0;
    for(int i=1;i<x.size();i++){
        g+=x[i];
    }
    g=1.0+9.0*g/(x.size()-1);

    double h=1.0-sqrt(result[0]/g);
    result[1]=g*h;
    
    return result;
}

vector<double> ZDT2(vector<double> x){
    vector<double> result(2);
    result[0]=x[0];
    double g=0.0;
    for(int i=1;i<x.size();i++){
        g+=x[i];
    }
    g=1+(9*g/(x.size()-1));
    result[1]=g*(1-pow(x[0]/g,2));
    return result;
}

vector<double> ZDT3(vector<double> x){
    vector<double> result(2);
    result[0]=x[0];
    double g=0.0;
    for(int i=1;i<x.size();i++){
        g+=x[i];
    }
    g=1+(9*g/(x.size()-1));
    result[1]=g*(1-sqrt(x[0]/g))-((x[0]/g)*sin(10*pi*x[0]));
    return result;
}

vector<double> ZDT6(vector<double> x){
    vector<double> result(2);
    result[0]=1-exp(-4.0*x[0])*pow(sin(6.0*pi*x[0]),6);
    double g=0.0;
    for(int i=1;i<x.size();i++){
        g+=pow(x[i]/(x.size()-1),1.0/4.0);
    }
    g=1+9*g;
    result[1]=g+(1-(x[0]/g));
    return result;
}
vector<double> moga_fvalue(int i,vector<double> x){
    vector<double> a(2,-99.0);
    if(i==0) return ZDT4(x);
    if(i==1) return ZDT1(x);
    if(i==2) return ZDT2(x);
    if(i==3) return ZDT3(x);
    if(i==4) return ZDT6(x);
    return a;
}




#endif