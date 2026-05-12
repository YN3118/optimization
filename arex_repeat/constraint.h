//���������ݒ�
#ifndef _CONSTRAINT_H_
#define _CONSTRAINT_H_

#include<cstdio>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
#include"function.h"
#include"parameter.h"


//制約条件

//定義域(min,max)を越えないように
//設計変数の和が0になるように設定(10の-9乗で近似)

bool constraint(vector<double> x){
    if(param.orconstraint==1){
        double sum=0.0;
        for(int i=0;i<x.size();i++){
            if(x[i]<param.min_value||param.max_value<x[i]) return false;
            sum+=x[i]; 
        }
        //Rosenbrockの場合は制約を変更(最適解[1,1,...,1]であるため)
        if(param.f_num==0||param.f_num==5){
            if(abs(sum)<param.dimension-1.0e-9||param.dimension+1.0e-9<abs(sum)) return false;
        }
        else{
            if(abs(sum)>1.0e-9) return false;
        }
        return true;
    }

    //定義域超えないように
    else{
        for(int i=0;i<x.size();i++){
            if(x[i]<param.min_value||param.max_value<x[i]) return false;
        }
        return true;
    };
}

#endif