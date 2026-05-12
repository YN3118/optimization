#ifndef _AREX_H_
#define _AREX_H_

#include"config.h"
#include"indiv.h"
#include"constraint.h"
#include"nsga2.h"

class AREX{
    public:
    
    vector<Indiv> population; //��W�c
    vector<Indiv> parent;     //�e�W�c
    vector<Indiv> children;   //�q�W�c
    double alpha=1.0;         //�g����
    FILE *file;               //�t�@�C���|�C���^

    vector<int> permutation;

    //�R���X�g���N�^
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
        vector<double> eps(param.p_size,0.0);

        for(int i=0;i<param.c_size;i++){
            do{
                vector<double> sum(param.dimension,0.0);
                for(int j=0;j<param.p_size;j++){
                    double tmp=func::generateRandomNomal(0.0,sqrt(1.0/(param.dimension)));
                    eps[j]=tmp;
                    sum=func::cal_sum(sum,func::cal_constmul(tmp,v[j]));
                }

                child_temp=func::cal_sum(new_g,func::cal_constmul(alpha,sum));
            }while(!(constraint(child_temp)));


            Indiv c(child_temp,i);
            
            children[i]=move(c);
            children[i].eps=eps;
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
        //���Ƃ̕�W�c�Ǝq�������ĕ]��
        vector<Indiv> P=population;
        P.insert(P.end(),children.begin(),children.end());
        NSGA2 nsga2(P);
        // NSGA2 nsga2(children);
        nsga2.exe();
        vector<Indiv> next_gen=move(nsga2.next);
        sort(next_gen.begin(),next_gen.end());

        //alpha�X�V
        double L_avg;
        double L_cdp=0.0;
        double sum1=0.0;
        double sum2=0.0;
        for(int j=0;j<param.p_size;j++){
            double e=0.0;
            for(int i=0;i<param.p_size;i++){
                e+=children[i].eps[j]/(param.dimension+1);
            }
            sum1+=pow(e,2);
            sum2+=e;
        }
        sum2=pow(sum2,2)/(param.dimension+1);        
        L_cdp=pow(alpha,2)*(param.dimension)*(sum1-sum2);
        L_avg=pow(alpha,2)*(param.dimension)/(param.dimension+1);
        double c=param.learning_rate;//�w�K��
        double next_alpha=alpha*sqrt((1.0-c)+(c*L_cdp/L_avg));
        if(next_alpha<1.0) alpha=1.0;
        else alpha=next_alpha;
        printf("alpha=%f\n",alpha);

        //��W�c�X�V(�I�������e�̂Ɠ����������ւ�)
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