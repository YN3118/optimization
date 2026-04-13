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

  //ベクトルの差を計算
  //引数に1を入れると絶対値
    inline vector<double> cal_dis(const vector<double> &a,const vector<double> &b,int n){
        vector<double> result_dis;
        for(int i=0;i<a.size();i++){
            result_dis.push_back(a[i]-b[i]);
            if(n==1&&result_dis[i]<0) result_dis[i]=fabs(result_dis[i]);
        }

        return result_dis;
    }

    //ベクトルの積
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

    //ベクトルのノルム計算
    inline double cal_norm(const vector<double> &a){
        double result=0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*a[i];
        }
        return sqrt(result);
    }
    
    //ベクトルの和
    inline vector<double> cal_sum(const vector<double> &a,const vector<double> &b){
        vector<double> result_sum;
        for(int i=0;i<a.size();i++){
            result_sum.push_back(a[i]+b[i]);
        }
        return result_sum;
    }

    //doubleの乱数を一様分布に従って生成
    inline double generateRandomDouble(double a,double b) {
        random_device rd; 
        uniform_real_distribution<> dis(a,b);

        return dis(gen);
    }

    //intの乱数を生成
    inline int generateRandomInt(int a,int b) {
        random_device rd; 
        uniform_real_distribution<> dis(a,b);

        return dis(gen);
    }

    //doubleの乱数を平均mean，分散stddevの正規分布に従って生成
    inline double generateRandomNomal(double mean,double stddev){
        random_device rd;
        normal_distribution<> dis(mean, stddev);

        return dis(gen);
    }

    //sgn関数(正の場合は1，負の場合は-1を返す)
    inline int sgn(double a){
      if(a>=0) return 1;
      else return -1;
    }

};

#endif
