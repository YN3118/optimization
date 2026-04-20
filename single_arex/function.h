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

    //二つのベクトルの中点計算
    inline vector<double> cal_centor(vector<double> a,vector<double> b){
        vector<double> result_centor;
        for(int i=0;i<a.size();i++){
            result_centor.push_back((a[i]+b[i])/2);
        }
        return result_centor;
    }

    //二つのベクトルの差を計算
    //関数の引数に1を入れると絶対値計算モード
    inline vector<double> cal_dis(vector<double> a,vector<double> b,int n){
        vector<double> result_dis;
        for(int i=0;i<a.size();i++){
            result_dis.push_back(a[i]-b[i]);
            if(n==1&&result_dis[i]<0) result_dis[i]=fabs(result_dis[i]);
        }

        return result_dis;
    }

    //二つのベクトルの積を計算
    //一つ目の引数の右から二つ目のベクトルをかける
    //今回は(dim_num×1)×(1×dim_num)だから定数を返す
    inline double cal_mul(vector<double> a,vector<double> b){
        double result=0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*b[i];
        }
        return result;
    }

    //定数×ベクトル
    inline vector<double> cal_constmul(double a,vector<double> b){
        vector<double> result;
        for(int i=0;i<b.size();i++){
            result.push_back(a*b[i]);
        }
        return result;
    }

    //ベクトルのノルムを計算
    inline double cal_norm(vector<double> a){
        double result=0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*a[i];
        }
        return sqrt(result);
    }
    
    //二つのベクトルの和を計算
    inline vector<double> cal_sum(vector<double> a,vector<double> b){
        vector<double> result_sum;
        for(int i=0;i<a.size();i++){
            result_sum.push_back(a[i]+b[i]);
        }
        return result_sum;
    }

    //ベクトルの和（二次元対応）
    inline vector<double> cal_sumex(vector<vector<double>> b){
        vector<double> result;
        for(int i=0;i<b[0].size();i++){
            double sum=0.0;
            for(int j=0;j<b.size();j++){
                sum+=b[j][i];
            }
            result.push_back(sum);
        }
        return result;
    }

    //ベクトルの内積計算
    inline double cal_naiseki(vector<double> a,vector<double> b){
        double result=0.0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*b[i];
        }
        return result;
    }

    //doubleの乱数を生成
    inline double generateRandomDouble(double a,double b) {
        random_device rd; // ハードウェア乱数生成器
        //mt19937 gen(rd()); // メルセンヌ・ツイスタ
        //mt19937 gen(seed);
        uniform_real_distribution<> dis(a,b); // 一様分布

        return dis(gen);
    }

    //intの乱数を生成
    inline int generateRandomInt(int a,int b) {
        random_device rd; // ハードウェア乱数生成器
        //mt19937 gen(rd()); // メルセンヌ・ツイスタ
        //mt19937 gen(seed);
        uniform_real_distribution<> dis(a,b); // 一様分布

        return dis(gen);
    }

    //平均mean 標準偏差stddevの正規乱数を生成
    inline double generateRandomNomal(double mean,double stddev){
        random_device rd;
        //mt19937 gen(rd());
        //mt19937 gen(seed);
        normal_distribution<> dis(mean, stddev);//正規分布

        return dis(gen);
    }

    //一様分布の乱数を生成
    inline double generateRandomDist(double a,double b){
        random_device rd;
        uniform_real_distribution<> dist(a,b);
        return dist(gen);
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
    
    //逆行列を計算

};

#endif
