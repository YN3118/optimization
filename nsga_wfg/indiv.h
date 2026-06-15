#ifndef _INDIV_H_
#define _INDIV_H_

#include<vector>
#include"config.h"
#include"function.h"
#include"benchmark.h"
#include"constraint.h"
#include"parameter.h"

using namespace std;
namespace func=Function;

class Indiv{
    public:
    vector<double> x;          //設計変数ベクトル
    vector<double> eps;        //AREXの拡張率計算用

    vector<double> f;          //関数値（適合度）
    double crowding_distance;  //混雑距離
    int rank;                  //ランク
    int dominant;              //支配数


    //コンストラクタ
    Indiv(){
        x.resize(param.dimension);
        double sum=0.0;

        for(int i=0;i<x.size();i++){
            x[i]=func::generateRandomDouble(param.min_value[i],param.max_value[i]);
            sum+=x[i];
        }

        if(param.orconstraint==1){
            //Rosenbrock�g�p����(�a=������)�ɂȂ�悤��
            if(param.f_num==0||param.f_num==5){
                for(int i=0;i<x.size();i++){
                    x[i]=x[i]+((param.dimension-sum)/x.size());
                }
            }
            else{
                //�݌v�ϐ��̘a��0�ɂȂ�悤�ɒ���(�s�v�ȂƂ��͏���)
                for(int i=0;i<x.size();i++){
                    x[i]=x[i]-(sum/x.size());
                }
            }
        }
        f=moga_fvalue(param.f_num,x);
        eps.resize(param.p_size,0.0);

        crowding_distance=0.0;
        rank=0;
        dominant=0;
    }

    Indiv(vector<double> a,int i){
        x.resize(a.size());
        x=a;
        f=moga_fvalue(param.f_num,x);
        eps.resize(param.p_size,0.0);
        crowding_distance=0.0;
        dominant=0;
        rank=0;
    }

    void echo(){
        for(int i=0;i<param.dimension;i++){
            printf("x[%d]:%f\t",i,x[i]);
        }
        printf("\n");
        printf("f1(x):%6f\t",f[0]);
        printf("f2(x):%6f\t",f[1]);        
        printf("\n\n");
        
    }

    //�e��I�y���[�^

    // std::move�ɑΉ������邽�߁C�폜
    // Indiv& operator=(const Indiv& s){
    //     x=s.x;
    //     f=s.f;
    //     eps=s.eps;
    //     crowding_distance=s.crowding_distance;
    //     rank=s.rank;
    //     dominant=s.dominant;
    //     return *this;
    // }

    bool operator==(const Indiv& s)const{
        if(f!=s.f) return false;
        for(int i=0;i<param.dimension;i++){
            if(x[i]!=s.x[i]) return false;
        }
        return true;
    }

    bool operator!=(const Indiv& s)const{
        return (!operator==(s));
    }

    //rank�������������ǂ���
    //rank�������ł����crowding_distance���傫�������ǂ���
    bool operator<(const Indiv& s)const{
        if(rank!=s.rank) return rank<s.rank;
        return crowding_distance>s.crowding_distance;
    }

    bool operator>(const Indiv& s)const{
        return (!operator<(s));
    }

};



#endif