#ifndef _UNDX_H_
#define _UNDX_H_

#include"config.h"
#include"indiv.h"
#include"constraint.h"
#include"nsga2.h"

class UNDX{
    public:
    
    vector<Indiv> population; //母集団
    vector<Indiv> parent;     //親集団
    vector<Indiv> children;   //子集団
    FILE *file;               //ファイルポインタ

    vector<int> permutation;

    //コンストラクタ
    UNDX(vector<Indiv> a,FILE *f){
        population.resize(a.size());
        for(int i=0;i<a.size();i++){
            population[i]=a[i];
        }
        children.resize(param.c_size);
        file=f;        
    }

    void execute(){
        selection();
        crossover();
        //mutation();
        evaluate();
    }

    void selection(){
        permutation.resize(param.pop_size);
        for(int i=0;i<param.pop_size;i++){
            permutation[i]=i;
        }

        for(int i=0;i<param.pop_size;i++){
            int temp1=rand()%param.pop_size;
            int temp2=rand()%param.pop_size;
            swap(permutation[temp1],permutation[temp2]);
        }

        parent.resize(param.p_size);
        for(int i=0;i<param.p_size;i++){
            parent[i]=population[permutation[i]];
        }
    }
    
    void crossover(){
        vector<double> g(param.dimension); //重心ベクトル
        for(int i=0;i<param.dimension;i++){
            double sum=0.0;
            for(int j=0;j<param.p_size;j++){
                sum+=parent[j].x[i];
            }
            g[i]=sum/(param.p_size);
        }
        

        vector<vector<double>> v; //重心との差ベクトル
        for(int i=0;i<param.p_size;i++){
            v.push_back(func::cal_dis(g,parent[i].x,0));
        }

        vector<vector<double>> d; //正規化したベクトルが入る
        d.push_back(func::cal_constmul(1/func::cal_norm(v[0]),v[0]));
        for(int i=1;i<g.size();i++){
            vector<double> sum(param.dimension,0.0);
            double temp=0.0;
            for(int j=0;j<i;j++){
                temp=func::cal_mul(v[i],d[j]);
                sum=func::cal_sum(sum,func::cal_constmul(temp,d[j]));
            }
            d.push_back(func::cal_dis(v[i],sum,0));
            d[i]=func::cal_constmul(1.0/func::cal_norm(d[i]),d[i]); //正規化
        }

        //子個体生成
        vector<double> child_temp(param.dimension,0.0);
        for(int i=0;i<param.c_size;i++){
            //境界を越えた場合は作り直す
            // do{
            // vector<double> sum(param.dimension,0.0);
            // for(int j=0;j<v.size();j++){
            //     sum=func::cal_sum(sum,func::cal_constmul(func::generateRandomNomal(0.0,1.0/sqrt(param.dimension+1)),v[j]));
            // }
            // child_temp=func::cal_sum(g,sum);
            // Indiv c(child_temp);
            // children[i]=move(c);
            // }while(!constraint(child_temp));

            
            vector<double> sum(param.dimension,0.0);
            for(int j=0;j<v.size();j++){
                sum=func::cal_sum(sum,func::cal_constmul(func::generateRandomNomal(0.0,1.0/sqrt(param.dimension+1)),v[j]));
            }
            child_temp=func::cal_sum(g,sum);

            //境界を越えた場合は丸める
            for(int j=0;j<child_temp.size();j++){
                if(child_temp[j]<param.min_value[j]) child_temp[j]=param.min_value[j];
                else if(param.max_value[j]<child_temp[j]) child_temp[j]=param.max_value[j];
            }
            Indiv c(child_temp);
            children[i]=move(c);
        }    
 
            


        parent.clear();
        g.clear();
        v.clear();
        d.clear();

    }

    void mutation(){
        double judge=func::generateRandomDouble(0.0,1.0);
        if(judge<param.mutationrate){
            Indiv c;
            int mut_num=rand()%param.c_size;
            children[mut_num]=move(c);
        }

    }

    void evaluate(){
        //もとの母集団と子を混ぜて評価
        vector<Indiv> P=population;
        P.insert(P.end(),children.begin(),children.end());
        NSGA2 nsga2(P);
        nsga2.exe();
        vector<Indiv> next_gen=move(nsga2.next);
        sort(next_gen.begin(),next_gen.end());


        //母集団更新
        for(int i=0;i<param.pop_size;i++){
            population[i]=move(next_gen[i]);
        }
        sort(population.begin(),population.end());

    }
};

    bool rank_ck(vector<Indiv> a){
        for(int i=0;i<a.size();i++){
            if(a[i].rank>1||a[i].rank==0) return false;
        }
        return true;
    }
#endif