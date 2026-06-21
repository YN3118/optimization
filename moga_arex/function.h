#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include<cstdio>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
#include<random>

#include"config.h"

using namespace std;


namespace Function{

    //二つのベクトルの差を計算
    inline vector<double> cal_dis(const vector<double> &a,const vector<double> &b,int n){
        vector<double> result_dis;
        for(int i=0;i<a.size();i++){
            result_dis.push_back(a[i]-b[i]);
            if(n==1&&result_dis[i]<0) result_dis[i]=fabs(result_dis[i]);
        }

        return result_dis;
    }
    //ベクトルの内積を計算
    inline double cal_mul(const vector<double> &a,const vector<double> &b){
        double result=0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*b[i];
        }
        return result;
    }
    //定数×ベクトル
    inline vector<double> cal_constmul(double a,const vector<double> &b){
        vector<double> result;
        for(int i=0;i<b.size();i++){
            result.push_back(a*b[i]);
        }
        return result;
    }
    //ベクトルのノルムを計算
    inline double cal_norm(const vector<double> &a){
        double result=0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*a[i];
        }
        return sqrt(result);
    }
    //ベクトルの和を計算
    inline vector<double> cal_sum(const vector<double> &a,const vector<double> &b){
        vector<double> result_sum;
        for(int i=0;i<a.size();i++){
            result_sum.push_back(a[i]+b[i]);
        }
        return result_sum;
    }
    //転置行列を計算
    inline vector<vector<double>> transpose(vector<vector<double>> a){
        vector<vector<double>> result(a[0].size(),vector<double>(a.size()));
        for(int i=0;i<a[0].size();i++){
            for(int j=0;j<a.size();j++){
                result[i][j]=a[j][i];
            }
        }
        return result;
    }
};

#endif
