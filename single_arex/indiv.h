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
    vector<double> x;          //染色体
    double f;                  //関数値
    int indiv_num;             //AREX用の個体識別番号

    vector<double> eps;        //AREX用のベクトル


    //デフォルトコンストラクタ
    Indiv(){
        x.resize(param.dimension);
        double sum=0.0;
        for(int i=0;i<x.size();i++){
            x[i]=func::generateRandomDouble(param.min_value,param.max_value);
            //if(i==2) x[i]=0.0;
            sum+=x[i];
        }


        // //設計変数を5個選んで0にする
        // if(param.dimension>5){
        //     sum=0.0;
        //     for(int i=0;i<5;i++){
        //         x[i]=0.0;
        //     }
        //     for(int i=5;i<param.dimension;i++){
        //         sum+=x[i];
        //     }
        //     if(param.orconstraint==1){
        //     //Rosenbrock使用時は(和=次元数)になるように
        //     if(param.f_num==0||param.f_num==5){
        //         for(int i=5;i<x.size();i++){
        //             x[i]=x[i]+((param.dimension-sum)/(x.size()-5));
        //         }
        //     }
        //     else{
        //         //設計変数の和が0になるように調整(不要なときは消す)
        //         for(int i=5;i<x.size();i++){
        //             x[i]=x[i]-(sum/(x.size()-5));
        //         }
        //     }
        // }
        // }

        if(param.orconstraint==1){
            //Rosenbrock使用時は(和=次元数)になるように
            if(param.f_num==0||param.f_num==5){
                for(int i=0;i<x.size();i++){
                    x[i]=x[i]+((param.dimension-sum)/x.size());
                }
            }
            else{
                //設計変数の和が0になるように調整(不要なときは消す)
                for(int i=0;i<x.size();i++){
                    x[i]=x[i]-(sum/x.size());
                }
            }
        }

        f=f_value(param.f_num,x);
        indiv_num=0;

        eps.resize(param.p_size,0.0);
    }

    Indiv(vector<double> a,int i){
        x.resize(a.size());
        x=a;
        f=f_value(param.f_num,x);
        indiv_num=i;
        eps.resize(param.p_size,0.0);
    }

    void echo(){
        for(int i=0;i<param.dimension;i++){
            printf("x[%d]:%f\t",i,x[i]);
        }
        printf("f(x):%6f\t",f);
        //確認用
        double sum=0.0;
        for(int i=0;i<param.dimension;i++){
            sum+=x[i];
        }
        // printf("sum:%6f\t",sum);
        // printf("indiv_num:%d\t",indiv_num);
        // printf("\n");
        // for(int i=0;i<eps.size();i++){
        //     printf("eps[%d]:%f\t",i,eps[i]);
        // }
        printf("\n");
        
    }

    //各種オペレータ
    Indiv& operator=(const Indiv& s){
        x=s.x;
        f=s.f;
        indiv_num=s.indiv_num;
        eps=s.eps;
        return *this;
    }

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

    bool operator>(const Indiv& s)const{
        if(f>s.f) return true;
        return false;
    }

    bool operator<(const Indiv& s)const{
        //return (!operator>(s));
        if(f<s.f) return true;
        return false;
    }

};



#endif