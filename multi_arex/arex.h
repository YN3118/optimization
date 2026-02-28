#ifndef _AREX_H_
#define _AREX_H_

#include"config.h"
#include"indiv.h"
#include"constraint.h"
#include"nsga2.h"

class AREX{
    public:
    
    vector<Indiv> population; //母集団
    vector<Indiv> parent;     //親集団
    vector<Indiv> children;   //子集団
    double alpha=1.0;         //拡張率
    FILE *file;               //ファイルポインタ

    vector<int> permutation;

    //コンストラクタ
    AREX(vector<Indiv> a,FILE *f){
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
        mutation();
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
        vector<double> g(param.dimension);
        for(int i=0;i<param.dimension;i++){
            double sum=0.0;
            for(int j=0;j<param.p_size;j++){
                sum+=parent[j].x[i];
            }
            g[i]=sum/(param.p_size);
        }
        
        vector<Indiv> p_copy(param.p_size);
        p_copy=parent;
        sort(p_copy.begin(),p_copy.end());
        vector<double> new_g(param.dimension,0.0);
        for(int i=0;i<p_copy.size();i++){
            double tmp=(2.0*(param.dimension+1-i))/((param.dimension+1)*(param.dimension+2));
            new_g=func::cal_sum(new_g,func::cal_constmul(tmp,p_copy[i].x));
        }

        vector<vector<double>> v; 
        for(int i=0;i<param.p_size;i++){
            v.push_back(func::cal_dis(g,parent[i].x,0));
        }

        vector<double> child_temp(param.dimension,0.0);
        vector<double> eps(param.p_size);

        for(int i=0;i<param.c_size;i++){
            // do{
            //     vector<double> sum(param.dimension,0.0);
            //     for(int j=0;j<param.p_size;j++){
            //         double tmp=func::generateRandomNomal(0.0,sqrt(1.0/(param.dimension)));
            //         eps[j]=tmp;
            //         sum=func::cal_sum(sum,func::cal_constmul(tmp,v[j]));
            //     }

            //     child_temp=func::cal_sum(new_g,func::cal_constmul(alpha,sum));
            // }while(!(constraint(child_temp)));

                vector<double> sum(param.dimension,0.0);
                for(int j=0;j<param.p_size;j++){
                    double tmp=func::generateRandomNomal(0.0,sqrt(1.0/param.dimension+6));
                    eps[j]=tmp;
                    sum=func::cal_sum(sum,func::cal_constmul(tmp,v[j]));
                }

                child_temp=func::cal_sum(new_g,func::cal_constmul(alpha,sum));

                //境界を越えた場合は丸める(丸めたときに分布が変わるので，epsも変化する．←この対応どうするの？)
                for(int j=0;j<param.dimension;j++){
                    if(child_temp[j]<param.min_value[j]){
                        child_temp[j]=param.min_value[j];
                    }
                    else if(param.max_value[j]<child_temp[j]){
                        child_temp[j]=param.max_value[j];
                    }
                }
            
            Indiv c(child_temp,i);
            
            children[i]=move(c);
            children[i].eps=move(eps);
        }

        v.clear();
    }

    void mutation(){
        double judge=func::generateRandomDouble(0.0,1.0);
        if(judge<param.mutationrate){
            int temp=rand()%children.size();
            vector<double> mut=children[temp].x;
            int mut_num=rand()%param.dimension;
            mut[mut_num]=func::generateRandomDouble(param.min_value[mut_num],param.max_value[mut_num]);
            Indiv c(mut,0);
        children[temp]=move(c);
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

        //alpha更新
        double L_avg;
        double L_cdp=0.0;
        double sum1=0.0;
        double sum2=0.0;
        for(int i=0;i<param.dimension+1;i++){
            double e=0.0;
            for(int j=0;j<param.dimension+1;j++){
                e+=children[i].eps[j]/(param.dimension+1);
            }
            sum1+=pow(e,2);
            sum2+=e;
        }
        sum2=pow(sum2,2)/(param.dimension+1);        
        L_cdp=pow(alpha,2)*(param.dimension)*(sum1-sum2);
        L_avg=pow(alpha,2)*(param.dimension)/(param.dimension+1);
        double c=1.0/(20*param.dimension);//学習率
        double next_alpha=alpha*sqrt((1.0-c)+(c*L_cdp/L_avg));
        printf("next_alpha=%f\n",next_alpha);
        if(next_alpha<1.0) alpha=1.0;
        else alpha=next_alpha;
        printf("alpha=%f\n",alpha);

        //母集団更新
        for(int i=0;i<param.pop_size;i++){
            population[i]=move(next_gen[i]);
        }
        sort(population.begin(),population.end());

        // printf("best\n");
        // population[0].echo();
        // printf("worst\n");
        // population[population.size()-1].echo();

        // vector<double> avg(param.dimension,0.0);
        // vector<double> avg2(param.dimension,0.0);
        // vector<double> var(param.dimension,0.0);
        // vector<double> pop_g(param.dimension,0.0);
        // for(int i=0;i<param.dimension;i++){
        //     double temp=0.0;
        //     for(int j=0;j<population.size();j++){
        //         temp+=population[j].x[i];
        //     }
        //     pop_g[i]=temp/population.size();
        // }

        // for(int i=0;i<param.dimension;i++){
        //     for(int j=0;j<population.size();j++){
        //         avg[i]+=population[j].x[i];
        //         avg2[i]+=pow(population[j].x[i],2);
        //     }
        //     avg[i]=avg[i]/population.size();
        //     avg2[i]=avg2[i]/population.size();
        //     var[i]=avg2[i]-pow(avg[i],2);
        // }


        // fprintf(file,"%f,%f,%f,",population[0].f,population[population.size()-1].f,alpha);

        // for(int i=0;i<param.dimension;i++){
        //     fprintf(file,",%lf",var[i]);
        // }
        // fprintf(file,",");
        // for(int i=0;i<param.dimension;i++){
        //     fprintf(file,",%lf",population[0].x[i]);
        // }

    }


};

    bool rank_ck(vector<Indiv> a){
        for(int i=0;i<a.size();i++){
            if(a[i].rank>1||a[i].rank==0) return false;
        }
        return true;
    }
#endif