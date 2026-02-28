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



bool constraint(vector<double> x){
    if(param.orconstraint==1){
        for(int i=0;i<x.size();i++){
            if(x[i]<param.min_value[i]||param.max_value[i]<x[i]) return false;
        }
        return true;
    }


    else{
        for(int i=0;i<x.size();i++){
            if(x[i]<param.min_value[i]||param.max_value[i]<x[i]) return false;
        }
        return true;
    };
}

#endif